//Name: Daryl Alex
//Student ID: 143691202
//email: dalex4@myseneca.ca
//Professor: Jeevan  Pant
#include <iomanip>
#include <exception>
#include "Job.h"

sdds::Job::Job() : desc{""}, worker{0}, pending{0}, status{false} {

}

sdds::Job::Job(std::string desc) : desc{desc} {
    worker = desc.length() % 10 + 1;
    pending = worker;
    status = true;
}

bool sdds::Job::is_active() const {
    return status;
}

bool sdds::Job::is_complete() const {
    return pending == 0;
}

std::string sdds::Job::name() const {
    return desc;
}

void sdds::Job::display(std::ostream& output) const {
    output << "`" << desc << "` ";
    output << "[" << std::setfill('0') << std::setw(2) << pending << "/";
    output << std::setfill('0') << std::setw(2) << worker << " remaining]";
}

std::ostream& sdds::operator<<(std::ostream& output, Job& job) {
    job.display(output);
    return output;
}

void sdds::Job::operator()(unsigned int worker) {
    if (worker > pending) {
        pending = 0;
        status = false;
        throw std::underflow_error("The handled work [" + std::to_string(worker) + "], is more than the remaining work [" + std::to_string(pending) + "].");
    } else {
        pending -= worker;

        if (pending == 0) {
            status = false;
        }
    }
}
