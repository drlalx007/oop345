//Name: Daryl Alex
//Student ID: 143691202
//email: dalex4@myseneca.ca
//Professor: Jeevan  Pant
#ifndef SDDS_JOB_H
#define SDDS_JOB_H

#include <string>
#include <iostream>
#include <iomanip>

namespace sdds {
    class Job {
        std::string desc;
        unsigned int worker;
        unsigned int pending;
        bool status;

        public:
        Job();
        Job(std::string);
        bool is_active() const;
        bool is_complete() const;
        std::string name() const;
        void display(std::ostream&) const;
        void operator()(unsigned int);
    };
    std::ostream& operator<<(std::ostream&, Job&);
};

#endif
