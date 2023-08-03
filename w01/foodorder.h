// Name: Daryl Alex
// Student Number: 143691202
// Email: dalex4@myseneca.ca
#ifndef FOOD_ORDER_H
#define FOOD_ORDER_H
#include <iostream>
#include <iomanip>
#include <cstring>
#include <string>


 extern double g_taxrate; 
 extern double g_dailydiscount;

namespace sdds
{
	class FoodOrder
	{
		char name[10]{}; 
		char food_desc[25]{}; 
		double fp{}; 
		bool flag; 

	public:
		FoodOrder() {};
		FoodOrder(const FoodOrder& A);
		FoodOrder& operator=(const FoodOrder& A);
		void read(std::istream& is);
		void display() const;

		~FoodOrder() {};
	
	};
	void stringCopy(char* destination, const char* source);
}
#endif // FOOD_ORDER_H


