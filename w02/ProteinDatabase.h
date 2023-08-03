//Name: Daryl Alex
//Student ID: 143691202
//Email: dalex4@myseneca.ca
//Subject Code: ZAA

#include <iostream>
#ifndef SDDS_PROTEINDATABASE_H_
#define SDDS_PROTEINDATABASE_H_
namespace sdds
{
	class ProteinDatabase
	{
	public:
		unsigned int s_length = 0;
		std::string* arr = nullptr;
		ProteinDatabase();
		ProteinDatabase(char*);
		ProteinDatabase(ProteinDatabase&&);
		ProteinDatabase(const ProteinDatabase& old);
		size_t size();
		std::string operator[](size_t);
		ProteinDatabase& operator=(const ProteinDatabase&);
		ProteinDatabase& operator=(ProteinDatabase&&);
		~ProteinDatabase();
	private:
	};
}
#endif