#include <iostream>
#include <string>
#include "LogIn.h"

namespace Records{

LogIn::LogIn(const std::string& userName,
             const std::string& password,
             bool employeeLevel)
            {
                mapLogIn.insert({userName, password});
                mapUserStatus.insert({userName, employeeLevel});
            }

bool LogIn::validate(const std::string& user, const std::string& pass) const {
    auto it = mapLogIn.find(user);
    if (it != mapLogIn.end() && it->second == pass) {
        std::cout << "Access granted" << std::endl;
        return true;
    } else {
        std::cout << "Access denied" << std::endl;
        return false;
    }
}


bool LogIn::checkStatus(const std::string& user) const
{
     for (auto itr = mapUserStatus.begin(); itr != mapUserStatus.end(); ++itr) {
        if (itr->first == user && itr->second == true)
            {
                std::cout << "You have Manager status" << std::endl;
                return true;
                break;
            }
    }
    std::cout << "You only have employee status" << std::endl;
    return false;
}

void LogIn::display() const
{
    std::cout << "USER\tPASSWORD\n"; 
    for (auto itr = mapLogIn.begin(); itr != mapLogIn.end(); ++itr) { 
        std::cout << itr->first << '\t' << itr->second << '\n'; 
    }
}

}