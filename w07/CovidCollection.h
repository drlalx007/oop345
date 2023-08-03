//Name: Daryl Alex
//Student ID: 143691202
//Email: dalex4@myseneca.ca
//Professor: Jeevan Pant

#ifndef SDDS_COVIDCOLLECTION_H_
#define SDDS_COVIDCOLLECTION_H_
#include <iostream>
#include <istream>
#include <cstring>
#include <string>
#include <list>
#include <iterator>
#include <iomanip>
#include <algorithm>  
#include <vector>
#include <sstream>
#include <string>
#include <utility>
#include <fstream>
#include <stdexcept>

namespace sdds
{
	struct Covid
	{
        std::string m_country{};
		std::string m_city{};
		std::string m_variant{};
		size_t m_num_of_cases=0;
		size_t m_year = 0;
		size_t m_deaths = 0;
	};
	class CovidCollection
	{
	private:
		std::vector<Covid> m_Covid; 
		void trim_space(std::string& word); 
		void extract_data_string(std::istream& str, std::string& data, size_t size);
		void extract_data_other(std::istream& str, size_t& data, size_t size);
	public:
		CovidCollection(char* filename); 
		void display(std::ostream& out) const;
		void sort(const std::string& fieldName); 
		void cleanList();
		bool inCollection(const std::string& variantName) const;
		std::list<Covid> getListForCountry(const std::string& countryName) const;
		std::list<Covid> getListForVariant(const std::string& variantName) const;	
	};
	std::ostream& operator<<(std::ostream& out, const Covid& theCovid);
}
#endif // !SDDS_COVIDCOLLECTION_H_
