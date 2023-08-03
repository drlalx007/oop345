//Name: Daryl Alex
//Student ID: 143691202
//Email: dalex4@myseneca.ca
//Subject Code: ZAA
#define _CRT_SECURE_NO_WARNINGS
#include <cstring>
#include <iomanip>
#include <iostream>
using namespace std;
#include "TimedTask.h"
namespace sdds {
	void TimedTask::startClock()
	{
		startTime = std::chrono::steady_clock::now();
	}
	void TimedTask::stopClock()
	{
		endTime = std::chrono::steady_clock::now();
	}
	ostream& operator<<(std::ostream& os, const TimedTask& tasks) {
		os << "--------------------------\n" << "Execution Times:\n--------------------------\n";
		for (int i = 0; i < tasks.m_rec; i++) {
			os << std::setw(21) << std::left << tasks.m_task[i].task_name << " ";
			os << std::setw(13) << std::right << tasks.m_task[i].duration.count() << " " << tasks.m_task[i].unit << "\n";
		}
		return os << "--------------------------\n";
	}
	void TimedTask::addTask(std::string name){

		m_task[m_rec].task_name = name;
		m_task[m_rec].duration = std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime);
		m_task[m_rec].unit = "nanoseconds";
		m_rec += 1;
	}
}