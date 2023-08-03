//Name: Daryl Alex
//Student ID: 143691202
//email: dalex4@myseneca.ca
//Professor: Jeevan  Pant
#ifndef SDDS_DIRECTORY_H
#define SDDS_DIRECTORY_H

#include <string>
#include <vector>
#include "Resource.h"
#include "Flags.h"


namespace sdds {
    class Directory : public Resource {
        std::vector<Resource*> m_contents;

        public:
        Directory(std::string dirname);
        void update_parent_path(const std::string&) override;
        NodeType type() const override;
        std::string path() const override;
        std::string name() const override;
        int count() const override;
        size_t size() const override;
        Directory& operator+=(Resource*);
        Resource* find(const std::string&, const std::vector<OpFlags>& flags = {});
        ~Directory();
        Directory& operator=(const Directory&) = delete;
        Directory& operator=(Directory&&) = delete;
        void remove(const std::string& path, const std::vector<OpFlags>& flags = {});
        void display(std::ostream&, const std::vector<FormatFlags>& flags = {}) const;
    };
};

#endif
