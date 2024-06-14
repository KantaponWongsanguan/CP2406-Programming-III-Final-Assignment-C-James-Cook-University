#pragma once

#include <iostream>
#include <vector>
#include "Employee.h"
#include <string>

namespace Records {
	const int kFirstEmployeeNumber = 1000;

	class Database
	{
	public:
		// editted middlename & address into the method
		Employee& addEmployee(const std::string& firstName,
							  const std::string& middleName,
							  const std::string& lastName,
							  const std::string& address);
		Employee& getEmployee(int employeeNumber);
		Employee& getEmployee(const std::string& firstName,
							  const std::string& lastName);

		void displayAll() const;
		void displayCurrent() const;
		void displayFormer() const;

		// added method definitions
		Employee& loadEmployee(const std::string& firstName,
						const std::string& middleName,
						const std::string& lastName,
						const std::string& address,
						const std::string& isHired,
						const std::string& empNumber,
						const std::string& salary);
		void clearDatabase();
		void saveDBtoFile(std::string filename) const;
		void searchEmployee(const int searchType,
						const std::string& searchTerm) const;

	private:
		std::vector<Employee> mEmployees;
		int mNextEmployeeNumber = kFirstEmployeeNumber;
	};
}
