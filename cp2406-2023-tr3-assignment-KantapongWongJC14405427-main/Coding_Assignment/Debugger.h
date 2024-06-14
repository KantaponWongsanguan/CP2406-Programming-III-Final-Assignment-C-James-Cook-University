// CP2406 Assignment 1 - SP53 23/24 - Kantapong Wongsanguan - 14405427
#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <exception>

#define DEBUG_MODE // Comment out this line if debugging is not needed
#ifdef DEBUG_MODE

class Debugger
{
    public:
    
        template<typename... Args>
		static void log(const Args&... args)
		{
			std::ofstream logfile(msDebugFileName, std::ios_base::app);
			if (logfile.fail()) {
				std::cerr << "Unable to open debug file" << std::endl;
				return;
			}
			// Write to file using a standard C++17 unary right fold
			((logfile << args), ...);
			logfile << std::endl;
			// Write debug log trace to screen
			((std::cout << args), ...);
			std::cout << "\n";
		}

    private:

        static const std::string msDebugFileName;
		
};

const std::string Debugger::msDebugFileName = "debugLogfile.txt";

	#define log(...) Debugger::log(__func__, "(): ", __VA_ARGS__)
#else
	#define log(...)
#endif