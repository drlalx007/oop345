//Name: Daryl Alex
//Student ID: 143691202
//Email: dalex4@myseneca.ca
//Professor: Jevan Pant 

#ifndef SDDS_CUSTOMERORDER_H
#define SDDS_CUSTOMERORDER_H
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <string>
#include <sstream>
#include <stdexcept>
#include <vector>
#include <iomanip>
#include <utility>
#include <fstream>
#include<stddef.h>
#include <exception>
#include "Utilities.h"
#include "Station.h"
namespace sdds
{
	struct Item
	{
		std::string m_itemName;
		size_t m_serialNumber{ 0 };
		bool m_isFilled{ false };

		Item(const std::string& src) : m_itemName(src) {};
	};
	class CustomerOrder
	{
	private:
		std::string m_name;
		std::string m_product;
		size_t m_cntItem=0;
		Item** m_lstItem{ nullptr }; 
		static size_t m_widthField;
	public:
		CustomerOrder();
		CustomerOrder(const std::string& str); 
        CustomerOrder(CustomerOrder& copy);  
		CustomerOrder& operator=(CustomerOrder&) = delete;
		CustomerOrder(CustomerOrder&&)noexcept; 
		CustomerOrder& operator=(CustomerOrder&&)noexcept; 
		bool isOrderFilled() const; 
		bool isItemFilled(const std::string& itemName) const;
		void fillItem(Station& station, std::ostream& os);
		void display(std::ostream& os) const;
		~CustomerOrder(); 
	};
}
#endif // !SDDS_CUSTOMERORDER_H