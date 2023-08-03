#include <stdexcept>
#include <iomanip>
#include "Directory.h"


sdds::Directory::Directory(std::string dirname)  {
    this->m_name = dirname;
}

std::string sdds::Directory::path() const {
    return m_parent_path + m_name;
}

std::string sdds::Directory::name() const {
    return m_name;
}

sdds::NodeType sdds::Directory::type() const {
    return NodeType::DIR;
}

int sdds::Directory::count() const {
    return m_contents.size();
}

void sdds::Directory::update_parent_path(const std::string& newpath) {
    m_parent_path = newpath;

    for (auto it = m_contents.begin(); it != m_contents.end(); it++) {
        (*it)->update_parent_path(path());
    }
}

sdds::Directory& sdds::Directory::operator+=(Resource* r) {
    bool exists = false;
    for (auto it = m_contents.begin(); it != m_contents.end(); it++) {
        if ((*it)->name() == r->name()) {
            exists = true;
            break;
        }
    }

    if (exists) {
        throw std::invalid_argument("Resource already exists!");
    } else {
        r->update_parent_path(path());
        m_contents.emplace_back(r);
    }

    return *this;
}

sdds::Resource* sdds::Directory::find(const std::string& filename, const std::vector<OpFlags>& flags) {
    Resource* foundResource = nullptr;

    bool isRecursive = false;

    for (auto it = flags.begin(); it != flags.end(); it++) {
        if ((*it) == OpFlags::RECURSIVE) {
            isRecursive = true;
            break;
        }
    }

    for (auto it = m_contents.begin(); it != m_contents.end(); it++) {
        if ((*it)->name() == filename) {
            foundResource = (*it);
            break;
        } else if (isRecursive && (*it)->type() == NodeType::DIR) {
            Directory* temp = dynamic_cast<Directory*>(*it);
            foundResource = temp->find(filename, flags);
        }
    }
    return foundResource;
}

size_t sdds::Directory::size() const {
    size_t sum = 0;

    for (auto it = m_contents.begin(); it != m_contents.end(); it++) {
        sum += (*it)->size();
    }
    return sum;
}

sdds::Directory::~Directory() {
    for (auto it = m_contents.begin(); it != m_contents.end(); it++) {
        delete *it;
    }
}

void sdds::Directory::display(std::ostream& os, const std::vector<FormatFlags>& flags) const {
    bool isLong = false;

    for (auto it = flags.begin(); it != flags.end(); it++) {
        if ((*it) == FormatFlags::LONG) {
            isLong = true;
            break;
        }
    }

    os << "Total size: " << size() << " bytes" << std::endl;

    for (auto it = m_contents.begin(); it != m_contents.end(); it++) {
        if ((*it)->type() == NodeType::FILE) {
            os << "F | ";
        } else {
            os << "D | ";
        }

        os << std::setw(15) << std::left << (*it)->name() << " |";

        if (isLong) {
            os << " ";
            if ((*it)->count() >= 0) {
                os << std::setw(2) << std::right << std::to_string((*it)->count());
            } else {
                os << std::setw(2) << std::right << "";
            }
            
            

            os << " | ";

            os << std::right << std::setw(10) << (std::to_string((*it)->size()) + std::string(" bytes"));
            os << " | ";
        }
        
        os << std::endl;

    }
}


void sdds::Directory::remove(const std::string& path, const std::vector<OpFlags>& flags) {
    bool isRecursive = false;

    for (auto it = flags.begin(); it != flags.end(); it++) {
        if ((*it) == OpFlags::RECURSIVE) {
            isRecursive = true;
            break;
        }
    }

    Resource* r = find(path);
    if (r == nullptr) {
        throw std::string(path + "does not exist in " + name());
    } else if (r->type() == NodeType::DIR) {
        if (isRecursive) {
            for (unsigned int i = 0; i < m_contents.size(); i++) {
                if (m_contents[i]->name() == path) {
                    Resource* temp = m_contents[i];
                    m_contents.erase(m_contents.begin() + i);
                    delete temp;
                    break;
                }
            }
        } else {
            throw std::invalid_argument(path + "is a directory. Pass the recursive flag to delete directories.");
        }
    } else {
        for (unsigned int i = 0; i < m_contents.size(); i++) {
            if (m_contents[i]->name() == path) {
                Resource* temp = m_contents[i];
                m_contents.erase(m_contents.begin() + i);
                delete temp;
                break;
            }
        }
    }
}
