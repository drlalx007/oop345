//Name: Daryl Alex
//Student ID: 143691202
//email: dalex4@myseneca.ca
//Professor: Jeevan  Pant
#ifndef SDDS_FILESYSTEM_H
#define SDDS_FILESYSTEM_H

#include "Resource.h"
#include "Directory.h"

namespace sdds {
    class Filesystem {
        Directory* m_root;
        Directory* m_current;
        std::string readNextInput(std::string input, unsigned int& pos, bool spaces = false);
        std::vector<std::string> getFilePath(std::string);
        std::string getFileName(std::string);

        public:
        Filesystem(std::string filename, std::string root = "");
        Filesystem(const Filesystem&) = delete;
        Filesystem(Filesystem&&);
        Filesystem& operator=(const Filesystem&) = delete;
        Filesystem& operator=(Filesystem&&);
        Filesystem& operator+=(Resource*);
        Directory* change_directory(const std::string& path = "");
        Directory* get_current_directory() const;
        ~Filesystem();
    };
};

#endif
