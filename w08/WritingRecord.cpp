
#include "GeneratingList.h"
#include "EmpProfile.h"
#include "WritingRecord.h"

using namespace std;

namespace sdds
{
	GeneratingList<EmployeeWage> writeRaw(const GeneratingList<Employee>& emp, const GeneratingList<Salary>& sal) {
		GeneratingList<EmployeeWage> activeEmp;
		// TODO: Add your code here to build a list of employees
		//         using raw pointers
		for (size_t i = 0u; i < emp.size(); i++)
		{
			std::string emp_Id = emp[i].id;
			for (size_t j = 0u; j < sal.size(); j++)
			{
				if (emp_Id == sal[j].id)
				{
					if (!activeEmp.isValidSIN(emp_Id))
					{
						throw "*** Employees SIN is not valid";
					}
					EmployeeWage* wage = new EmployeeWage(emp[i].name, sal[j].salary);

					try {
						wage->rangeValidator();
						activeEmp += wage;
						delete wage;
					}
					catch (const string err_msg) {
						delete wage;
						throw std::string(err_msg);
					}
				}
			}
		}

		return activeEmp;
	}

	GeneratingList<EmployeeWage> writeSmart(const GeneratingList<Employee>& emp, const GeneratingList<Salary>& sal) {
		GeneratingList<EmployeeWage> activeEmp;
		// TODO: Add your code here to build a list of employees
		//         using smart pointers
		for (size_t i = 0u; i < emp.size(); i++)
		{
			std::string emp_Id = emp[i].id;
			for (size_t j = 0u; j < sal.size(); j++)
			{
				if (emp_Id == sal[j].id)
				{
					if (!activeEmp.isValidSIN(emp_Id))
					{
						throw "*** Employees SIN is not valid";
					}
					//EmployeeWage* wage = new EmployeeWage(emp[i].name, sal[j].salary);
					std::unique_ptr<EmployeeWage> wage(new EmployeeWage(emp[i].name, sal[j].salary));
					
					wage->rangeValidator();
					activeEmp += std::move(wage);
					
				}
			}
		}
		return activeEmp;
	}
}
