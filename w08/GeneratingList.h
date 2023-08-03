

#ifndef SDDS_GENERATINGLIST_H
#define SDDS_GENERATINGLIST_H

#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <memory>
#include <utility>
#include <fstream>

namespace sdds
{
	template<typename T>
	class GeneratingList
	{

		std::vector<T> list;
	public:

		GeneratingList() {}
		GeneratingList(const char* f) {
			std::ifstream file(f);
			if (!file)
				throw std::string("*** Failed to open file ") + std::string(f) + std::string(" ***");

			while (file) {
				T t;
				if (t.load(file))
					list.push_back(T(t));
			}
		}

		size_t size() const {
			return list.size();
		}
		const T& operator[](size_t i) const {
			return list[i];
		}

		//TODO: Implement the Luhn Algorithm to check the 
		//      valadity of SIN No's
		bool isValidSIN(const std::string& sin)
		{
			int num_digits = sin.length();
			int sum = sin.at(num_digits - 1) - '0';
			int parity = (num_digits - 2) % 2;
			int digit;
			for (int i = 0; i <= num_digits - 2; i++)
			{
				digit = sin.at(i) - '0';
				if (i % 2 == parity)
				{
					digit *= 2;
				}
				if (digit > 9)
				{
					digit -= 9;
				}
				sum += digit;
			}
			return sum % 10 == 0;
		}

		//TODO: Overload the += operator with a smart pointer
		// as a second operand.
		void operator+=(std::unique_ptr<T> record)
		{
			list.push_back(std::move(*record));
		}


		//TODO: Overload the += operator with a raw pointer
		// as a second operand.
		void operator+=(T* record)
		{
			list.push_back(std::move(*record));
		}

		void print(std::ostream& os) const {
			os << std::fixed << std::setprecision(2);
			for (auto& e : list)
				e.print(os);
		}
	};

	template<typename T>
	std::ostream& operator<<(std::ostream& os, const GeneratingList<T>& rd) {
		rd.print(os);
		return os;
	}
}
#endif // !SDDS_GENERATINGLIST_H
