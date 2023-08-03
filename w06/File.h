//Name: Daryl Alex
//Student ID: 143691202
//email: dalex4@myseneca.ca
//Professor: Jeevan  Pant

#ifndef SDDS_FILE_H
#define SDDS_FILE_H

#include <string>
#include "Resource.h"
#include "Flags.h"

namespace sdds {
    class File : public Resource {
        std::string m_contents;

        public:
        File(std::string filename, std::string contents = "");
        void update_parent_path(const std::string&) override;
        NodeType type() const override;
        std::string path() const override;
        std::string name() const override;
        int count() const override;
        size_t size() const override;
    };
};

#endif
