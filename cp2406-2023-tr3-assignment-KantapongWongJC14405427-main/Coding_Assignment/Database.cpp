#include <iostream>
#include <stdexcept>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>
#include <filesystem>
#include "Database.h"

using namespace std;

namespace Records {

	// added middlename & address
	Employee& Database::addEmployee(const string& firstName,
		const string& middleName, const string& lastName, const string& address)
	{
		Employee theEmployee(firstName, middleName, lastName, address);
		theEmployee.setEmployeeNumber(mNextEmployeeNumber++);
		theEmployee.hire();
		mEmployees.push_back(theEmployee);

		return mEmployees[mEmployees.size() - 1];
	}

	// load Employee
	Employee& Database::loadEmployee(const string& firstName,
		const string& middleName, const string& lastName, const string& address,
		const string& isHired, const string& empNumber, const string& salary)
	{
		Employee theEmployee(firstName, middleName, lastName, address);
		if (isHired == "Current Employee") {
			theEmployee.hire();
		} else {
			theEmployee.fire();
		}
		int empNumberInt = stoi(empNumber);
		int salaryInt = stoi(salary);
		theEmployee.setEmployeeNumber(empNumberInt);
		theEmployee.setSalary(salaryInt);
		mEmployees.push_back(theEmployee);

		return mEmployees[mEmployees.size() - 1];
	}

	Employee& Database::getEmployee(int employeeNumber)
	{
		for (auto& employee : mEmployees) {
			if (employee.getEmployeeNumber() == employeeNumber) {
				return employee;
			}
		}
		throw logic_error("No employee found.");
	}

	Employee& Database::getEmployee(const string& firstName, const string& lastName)
	{
		for (auto& employee : mEmployees) {
			if (employee.getFirstName() == firstName &&
				employee.getLastName() == lastName) {
					return employee;
			}
		}
		throw logic_error("No employee found.");
	}

	void Database::displayAll() const
	{
		for (const auto& employee : mEmployees) {
			employee.display();
		}
	}

	void Database::displayCurrent() const
	{
		for (const auto& employee : mEmployees) {
			if (employee.isHired())
				employee.display();
		}
	}

	void Database::displayFormer() const
	{
		for (const auto& employee : mEmployees) {
			if (!employee.isHired())
				employee.display();
		}
	}


	// Clear database
	void Database::clearDatabase()
	{
		mEmployees.clear();
	}

	// Save database to file
	void Database::saveDBtoFile(string filename) const
	{

		ofstream outFile{ filename, ios_base::trunc };
		if (!outFile.good())
			{
			cerr << "Cannot open file: " << filename << endl;
			return;
			}
		for (auto& employee : mEmployees)
			{
			// Save each employee to a line in a file with simple quoted format to include whitespace
			string employeeStatus = (employee.isHired() ? "Current Employee" : "Former Employee");
			int empNum = (employee.getEmployeeNumber());
			string empNumString = to_string(empNum);
			int salaryNum = (employee.getSalary());
			string salaryNumString = to_string(salaryNum);
			outFile << quoted(employee.getFirstName()) << quoted(employee.getMiddleName())
					<< quoted(employee.getLastName()) << quoted(employee.getAddress())
					<< quoted(employeeStatus) << quoted(empNumString)
					<< quoted(salaryNumString) << endl;
			}
	}

	// Search employee
	void Database::searchEmployee(const int searchType, const string& searchTerm) const
	{
		string firstName, middleName, lastName, address;
		
		switch(searchType)
		{
			case 1:
				for (auto& employee : mEmployees) {
					firstName = employee.getFirstName();
					size_t found = firstName.find(searchTerm);
            		if (found!=std::string::npos)
						{
							employee.display();
						}
				}	
				break;
			case 2:
				for (auto& employee : mEmployees) {
					middleName = employee.getMiddleName();
					size_t found = middleName.find(searchTerm);
            		if (found!=std::string::npos)
						{
							employee.display();
						}
				}	
				break;
			case 3:
				for (auto& employee : mEmployees) {
					lastName = employee.getLastName();
					size_t found = lastName.find(searchTerm);
            		if (found!=std::string::npos)
						{
							employee.display();
						}
				}	
				break;
			case 4:
				for (auto& employee : mEmployees) {
					address = employee.getAddress();
					size_t found = address.find(searchTerm);
            		if (found!=std::string::npos)
						{
							employee.display();
						}
				}	
				break;
			default:
				std::cerr << "Unknown command" << std::endl;
				break;
		}
	}

}
