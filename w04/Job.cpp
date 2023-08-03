#include <iomanip>
#include <exception>
#include "Job.h"

sdds::Job::Job() : title{""}, work{0}, remaining{0}, isActive{false} {

}

sdds::Job::Job(std::string title) : title{title} {
    work = title.length() % 10 + 1;
    remaining = work;
    isActive = true;
}

bool sdds::Job::is_active() const {
    return isActive;
}

bool sdds::Job::is_complete() const {
    return remaining == 0;
}

std::string sdds::Job::name() const {
    return title;
}

void sdds::Job::display(std::ostream& output) const {
    output << "`" << title << "` ";
    output << "[" << std::setfill('0') << std::setw(2) << remaining << "/";
    output << std::setfill('0') << std::setw(2) << work << " remaining]";
}

std::ostream& sdds::operator<<(std::ostream& output, Job& job) {
    job.display(output);
    return output;
}

void sdds::Job::operator()(unsigned int work) {
    if (work > remaining) {
        remaining = 0;
        isActive = false;
        throw std::underflow_error("The handled work [" + std::to_string(work) + "], is more than the remaining work [" + std::to_string(remaining) + "].");
    } else {
        remaining -= work;

        if (remaining == 0) {
            isActive = false;
        }
    }
}