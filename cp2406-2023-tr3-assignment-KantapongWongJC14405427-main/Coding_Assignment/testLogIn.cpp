// testLogIn.cpp

#include <iostream>
#include "LogIn.h"
#include "LogInDataBase.h"

using namespace std;
using namespace Records;

int main() {
    LogInDataBase loginDB;

    // Add Manager and Employee accounts
    loginDB.addNewUser("manager", "manager_password", true); // Manager role
    loginDB.addNewUser("employee", "employee_password", false); // Employee role

    LogIn& managerLogin = loginDB.getUser("manager", "manager_password");
    LogIn& employeeLogin = loginDB.getUser("employee", "employee_password");

    // Validate and demonstrate Manager's access
    if (managerLogin.validate("manager", "manager_password")) {
        cout << "Manager login successful! All options available." << endl;
    } else {
        cout << "Manager login failed! Access denied." << endl;
    }

    // Validate and demonstrate Employee's access
    if (employeeLogin.validate("employee", "employee_password")) {
        cout << "Employee login successful! Restricted options available." << endl;
    } else {
        cout << "Employee login failed! Access denied." << endl;
    }

    return 0;
}
