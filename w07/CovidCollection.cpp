//Name: Daryl Alex
//Student ID: 143691202
//Email: dalex4@myseneca.ca
//Professor: Jeevan Pant

#define _CRT_SECURE_NO_WARNINGS
#include "CovidCollection.h"
using namespace std;
namespace sdds
{
	void CovidCollection::display(std::ostream& out) const
	{
		size_t total_cases = 0;
		size_t total_deaths = 0;

        for_each(m_Covid.begin(), m_Covid.end(), [&total_cases,&total_deaths](const Covid& covid) {
            cout << covid << endl;
            total_cases = total_cases + covid.m_num_of_cases;
            total_deaths = total_deaths + covid.m_deaths;
        });
		out << "----------------------------------------------------------------------------------------\n";
		out << "|                                                 Total Cases Around the World:  "<< total_cases<<" |"<<endl;
		out << "|                                                Total Deaths Around the World:  " << total_deaths << " |" << endl;
	}
	
	CovidCollection::CovidCollection(char* filename)
	{
		std::ifstream file(filename);
		if (file.is_open())
		{
			std::string line;
			while (std::getline(file, line, '\n')) 
			{
				
				if (line != "")
				{
					Covid c;
					std::stringstream str(line);
                    extract_data_string(str, c.m_country, 25);
                    extract_data_string(str, c.m_city, 25);
                    extract_data_string(str, c.m_variant, 25);
                    extract_data_other(str, c.m_year, 5);
                    extract_data_other(str, c.m_num_of_cases, 5);
                    extract_data_other(str, c.m_deaths, 5);
					m_Covid.push_back(c);
				}

			}
			file.close();
		}
		else
		{
			throw std::invalid_argument("Invalid file name!");
		}
	}

    void CovidCollection::trim_space(std::string& word)
    {
        while (word.find(" ") == 0)
        {
            word.erase(0, 1);
        }
        word.erase(std::find_if(word.rbegin(), word.rend(), [](unsigned char ch) {
            return !std::isspace(ch);
            }).base(), word.end());
    }
	std::ostream& operator<<(std::ostream& out, const Covid& theCovid)
	{
		out << "| " << std::setw(20) << std::left << theCovid.m_country;
		out << "  | " << std::setw(15)  << theCovid.m_city;
		out << " | " << std::setw(20) << theCovid.m_variant;
		out << " | " << std::setw(6) << std::right;
		if (theCovid.m_year != 0)
		{
			out << theCovid.m_year;
		}
		else
		{
			out << "";
		}
		out << " | " << std::right << std::setw(4) << theCovid.m_num_of_cases;
		out << " | " << std::setw(3) << theCovid.m_deaths;
		out << " |";
		return out;
	}
	
	void CovidCollection::extract_data_string(std::istream& str, std::string& data, size_t size)
	{
		
		char arr[26]{ '\0' };
		for (size_t i = 0; i < size; i++)
		{
			str.get(arr[i]);
		}
		arr[size] = '\0';
		
		std::string temp1;
        temp1=arr;
        trim_space(temp1);
        data = temp1;
	}
                                   
	void CovidCollection::extract_data_other(std::istream& str, size_t& data, size_t size)
	{
		char arr[6]{'\0'};
		for (size_t i = 0; i < size; i++)
		{
			str.get(arr[i]);
		}
		arr[size] = '\0';
		std::string temp2;
        temp2=arr;
            trim_space(temp2);
			if (temp2.find('-') != std::string::npos) 
			{
				data = 0;
			}
			else
			{
				data = std::stoi(temp2);
			}
	}
	
	void CovidCollection::cleanList()
	{
		std::for_each(m_Covid.begin(), m_Covid.end(), [](Covid& covid) {
			if (covid.m_variant == "[None]")
			{
				covid.m_variant = "";
			}
			});
		
	}

void CovidCollection::sort(const std::string& fieldName)
{
    if (fieldName == "country")
    {
        std::sort(m_Covid.begin(),m_Covid.end(),[](Covid& covid1, Covid& covid2) {
            return covid1.m_country < covid2.m_country;
        });
    }
    else if (fieldName == "variant")
    {
        std::sort(m_Covid.begin(), m_Covid.end(), [](Covid& covid1,Covid& covid2) {
            return covid1.m_variant < covid2.m_variant;
        });
    }
    else if (fieldName == "cases")
    {
        std::sort(m_Covid.begin(), m_Covid.end(), []( Covid& covid1, Covid& covid2) {
            return covid1.m_num_of_cases < covid2.m_num_of_cases;
        });
    }
    else if(fieldName=="deaths")
    {
        std::sort(m_Covid.begin(), m_Covid.end(), []( Covid& covid1, Covid& covid2) {
            return covid1.m_deaths < covid2.m_deaths;
        });
    }
    else
    {
        cout << "Invalid choice-" << endl;
    }
}
	
	
	std::list<Covid> CovidCollection::getListForCountry(const std::string& countryName) const
	{
		std::list<Covid> l_Country;
		std::copy_if(m_Covid.begin(), m_Covid.end(), std::back_inserter(l_Country), [countryName](const Covid& covid) {
            return covid.m_country == countryName;
        });
		return l_Country;
	}
	
bool CovidCollection::inCollection(const std::string& variantName) const
{
    bool flag = false;
    flag=std::any_of(m_Covid.begin(), m_Covid.end(), [variantName](const Covid& covid) {
        return covid.m_variant == variantName;
    });
    return flag;
}

	
	std::list<Covid> CovidCollection::getListForVariant(const std::string& variantName) const
	{
		std::string	vname = variantName;
		std::list<Covid> l_Variant;

		std::copy_if(m_Covid.begin(), m_Covid.end(), std::back_inserter(l_Variant), [vname](const Covid& covid) {
            return covid.m_variant == vname;
        });
		return l_Variant;
		
	
	}
}
