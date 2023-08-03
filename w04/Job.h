#ifndef SDDS_JOB_H
#define SDDS_JOB_H

#include <string>
#include <iostream>
#include <iomanip>

namespace sdds {
    class Job {
        std::string title;
        unsigned int work;
        unsigned int remaining;
        bool isActive;

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