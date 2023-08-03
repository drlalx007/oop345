//Name: Daryl Alex
//Student ID: 143691202
//Email: dalex4@myseneca.ca
//Subject Code: ZAA
#include <iostream>
#include<chrono>
#ifndef SDDS_TIMEDTASK_H_
#define SDDS_TIMEDTASK_H_
namespace sdds{
	const int max = 10;
	class TimedTask{
	public:
		std::chrono::steady_clock::time_point startTime;
		std::chrono::steady_clock::time_point endTime;
		struct Task{
			std::string task_name;
			std::string unit;
			std::chrono::steady_clock::duration duration;
		};
		Task m_task[max];
		int m_rec = 0;
		
		friend std::ostream& operator<<(std::ostream& os, const TimedTask& tasks);
		void startClock();
		void stopClock();
		void addTask(std::string name);
	private:
	};
}
#endif