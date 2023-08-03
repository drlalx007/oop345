//Name: Daryl Alex
//Student ID: 143691202
//email: dalex4@myseneca.ca
//Professor: Jeevan  Pant
#include "File.h"

sdds::File::File(std::string filename, std::string contents) : m_contents{contents} {
    this->m_name = filename;
}

void sdds::File::update_parent_path(const std::string& path) {
    m_parent_path = path;
}

sdds::NodeType sdds::File::type() const {
    return NodeType::FILE;
}

std::string sdds::File::path() const {
    return m_parent_path + m_name;
}

std::string sdds::File::name() const {
    return m_name;
}

int sdds::File::count() const {
    return -1;
}

size_t sdds::File::size() const {
    return m_contents.length();
}

