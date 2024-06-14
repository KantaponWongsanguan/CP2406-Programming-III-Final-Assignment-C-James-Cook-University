#pragma once

#include <string>
#include <map>

namespace Records{
	class LogIn
	{
	public:
        LogIn() = default;
        LogIn(const std::string& userName,
              const std::string& password,
              bool employeeLevel);
        // Validate UserName and Password
        bool validate(const std::string& user,
                      const std::string& pass) const;
        bool checkStatus(const std::string& user) const;
        void display() const;

    private:
        std::map<std::string, std::string> mapLogIn;
        std::map<std::string, bool> mapUserStatus;
    };
}