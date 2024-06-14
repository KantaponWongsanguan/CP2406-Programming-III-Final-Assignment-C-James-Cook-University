#include <iostream>
#include <string>
#include <map>
#include <vector>
#include "LogInDataBase.h"

namespace Records {

LogIn& LogInDataBase::addNewUser(const std::string& userName,
                                 const std::string& password,
                                 bool employeeLevel)
    {
        LogIn newUser(userName, password, employeeLevel);
        mLogInDB.push_back(newUser);
        return mLogInDB[mLogInDB.size() - 1];
    }

void LogInDataBase::displayAll() const
    {
        for (const auto& user : mLogInDB) {
            user.display();
        }
    }

LogIn& LogInDataBase::getUser(const std::string& userName, const std::string& password) {
    for (auto& user : mLogInDB) {
        if (user.validate(userName, password)) {
            std::cout << "Access granted" << std::endl;
            return user;
        }
    }
    std::cout << "Access denied" << std::endl;
    // You might want to handle the case when the user is not found or validation fails.
    // Here, returning a reference to the first user in the database.
    // Consider throwing an exception or handling this case according to your requirements.
    return mLogInDB[0];
}


}