#pragma once

#include <iostream>
#include <vector>
#include <map>
#include "LogIn.h"
#include <string>


namespace Records {


class LogInDataBase
{
    public:
        LogIn& addNewUser(const std::string& userName,
                          const std::string& password,
                          bool employeeLevel);
        LogIn& getUser(const std::string& userName,
                       const std::string& password);
        void displayAll() const;
    private:
        std::vector<LogIn> mLogInDB;
};

}
