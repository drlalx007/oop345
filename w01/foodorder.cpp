// Name: Daryl Alex
// Student Number: 143691202
// Email: dalex4@myseneca.ca


#include<iostream>
#include<iomanip>
#include <string>
#include "foodorder.h"

using namespace std;
double g_taxrate = 0.0; 
double g_dailydiscount = 0.0;

namespace sdds
{
	FoodOrder::FoodOrder(const FoodOrder& A)
	{ 
		operator=(A);
	}

	FoodOrder& FoodOrder::operator=(const FoodOrder& A) 
	{
		if (this != &A) 
		{
			stringCopy(name, A.name);
			stringCopy(food_desc, A.food_desc);
			fp = A.fp;
			flag = A.flag;
		}
		return *this;
	}

	
	void FoodOrder::read(std::istream& in)
	{
		if (in) 
		{
			in.getline(name,10,','); 
			in.getline(food_desc, 25, ','); 
			in >> fp;
			char temp = 'N';
			in.ignore();
			in >> temp;
			temp == 'N' ? flag = false : flag = true;
		}
		else
		{
			
		}
		
	}
	
	void FoodOrder::display() const
	{
		static int orderNumber = 0;
		cout << left << setw(2) << ++orderNumber << ". "; 
														  

		if (std::char_traits<char>::length(name) > 0) 
		
		{
			cout << setw(10) << name << "|"; 
			cout << setw(25) << food_desc << "|"; 
			double finalPrice = fp + (fp * g_taxrate);
			cout << fixed << setw(12) << setprecision(2) << finalPrice << "|"; 
			double specialPrice=0.0;
			if (flag)
			{
				specialPrice = finalPrice - g_dailydiscount;
				cout << right << setprecision(2) << setw(13) << specialPrice;
			}
		}
		else 
		{
			
			cout << "No Order";
		}
		cout << endl;

	}
	
	void stringCopy(char* destination, const char* source)
	{
		std::string str(source);
		std::strcpy(destination, str.c_str()); 
	}

}
