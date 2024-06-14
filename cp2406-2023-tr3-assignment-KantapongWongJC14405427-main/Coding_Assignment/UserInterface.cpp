#include "Debugger.h"
#include <iostream>
#include <stdexcept>
#include <exception>
#include <fstream>
#include <sstream>
#include <string>
#include <filesystem>
#include <vector>
#include "Database.h"
#include "LogIn.h"
#include "LogInDataBase.h"

using namespace std;
using namespace Records;

// Declare login-related functions
bool authenticate(LogInDataBase& loginDB);
bool promptLogin(LogInDataBase& loginDB);

int displayMenu();
void doHire(Database& db);
void doFire(Database& db);
void doPromote(Database& db);
Database generateNewDB(Database& db);
Database loadDBfromFile();
const string checkFileName();
void editEmployee(Database& db);
void searchEmployee(Database& db);

int main() {
    log("entered");

    // Create a Login Database
    LogInDataBase loginDB;
    // Add users to the login database (with usernames, passwords, and roles)
    loginDB.addNewUser("manager", "manager_password", true);
    loginDB.addNewUser("employee", "employee_password", false);

    bool loggedIn = promptLogin(loginDB);

    if (loggedIn) {
        Database employeeDB;

        bool done = false;
        while (!done) {
            int selection = displayMenu();
            switch (selection) {
                case 0:
                    done = true;
                    break;
                case 1:
                    doHire(employeeDB);
                    break;
                case 2:
                    doFire(employeeDB);
                    break;
                case 3:
                    doPromote(employeeDB);
                    break;
                case 4:
                    employeeDB.displayAll();
                    break;
                case 5:
                    employeeDB.displayCurrent();
                    break;
                case 6:
                    employeeDB.displayFormer();
                    break;
                case 7:
                    employeeDB = generateNewDB(employeeDB);
                    break;
                case 8:
                    dbFileName = checkFileName();
                    employeeDB.saveDBtoFile(dbFileName);
                    break;
                case 9:
                    employeeDB = loadDBfromFile();
                    break;
                case 10:
                    editEmployee(employeeDB);
                    break;
                case 11:
                    searchEmployee(employeeDB);
                    break;
                default:
                    cerr << "Unknown command." << endl;
                    break;
            }
        }
    }

    log("exited");
    return 0;
}

int displayMenu()
{
	// Note:
	//		One important note is that this code assumes that the user will
	//		"play nice" and type a number when a number is requested.
	//		When you read about I/O in Chapter 13, you will learn how to
	//		protect against bad input.

    log("entered");
    int selection;

    // added new features display menu 
    cout << endl;
    cout << "Employee Database" << endl;
    cout << "-----------------" << endl;
    cout << "1) Hire a new employee" << endl;
    cout << "2) Fire an employee" << endl;
    cout << "3) Promote an employee" << endl;
    cout << "4) List all employees" << endl;
    cout << "5) List all current employees" << endl;
    cout << "6) List all former employees" << endl;
    cout << "7) Generate new database" << endl;
    cout << "8) Save database to file" << endl;
    cout << "9) Load database from file" << endl;
    cout << "10) Edit employee" << endl;
    cout << "11) Search employee" << endl;
    cout << "0) Quit" << endl;
    cout << endl;
    cout << "---> ";
    
	cin >> selection;
    
	return selection;
    log("exited");
}

void doHire(Database& db)
{
    // added midName & address & debugger log 
    log("entered");
    string firstName;
    string middleName;
    string lastName;
    string address;

    cout << "First name? ";
    cin >> firstName;
    cout << "Middle name? ";
    cin >> middleName;
    cout << "Last name? ";
    cin >> lastName;
    cout << "Address? ";
    getline(cin >> ws, address);  // Ignores ws within cin input

    db.addEmployee(firstName, middleName, lastName, address);
    log("exited"); 
}

void doFire(Database& db)
{
    log("entered");
    int employeeNumber;

    cout << "Employee number? ";
    cin >> employeeNumber;

    try {
        Employee& emp = db.getEmployee(employeeNumber);
        emp.fire();
        cout << "Employee " << employeeNumber << " terminated." << endl;
    } catch (const std::logic_error& exception) {
        cerr << "Unable to terminate employee: " << exception.what() << endl;
    }

    log("exited");
}

void doPromote(Database& db)
{
    log("entered");

    int employeeNumber;
    int raiseAmount;

    cout << "Employee number? ";
    cin >> employeeNumber;
    cout << "How much of a raise? ";
    cin >> raiseAmount;

    try {
        Employee& emp = db.getEmployee(employeeNumber);
        emp.promote(raiseAmount);
    } catch (const std::logic_error& exception) {
        cerr << "Unable to promote employee: " << exception.what() << endl;
    }

    log("exited");
}

// Generate a new database
Database generateNewDB(Database& db)
{
    log("entered");
    Database dbNew;

    // Read names from file into first, middle, last name vectors
    string filename = "TwentyNames.txt";
    vector<string> firstNameVec, middleNameVec, lastNameVec;
    
    // Open the file and check for failure.
	ifstream inputFile{ filename.data() };
	if (inputFile.fail())
    {
		throw invalid_argument{ "Unable to open file" };
    }
    
    while (!inputFile.eof())
    {
        string line;
		getline(inputFile, line);
        // Skip empty lines if found
		if (line.empty()) {
			continue;
		}
		// Make a string stream and parse it
		istringstream inLine { line };
		string firstName, middleName, lastName;
        // Names in the file are quoted so quoted() is needed to separate them
        inLine >> quoted(firstName) >> quoted(middleName) >> quoted(lastName);
		if (inLine.bad()) {
			cerr << "Error reading person. Ignoring." << endl;
			continue;
		}
        firstNameVec.push_back(firstName);
        middleNameVec.push_back(middleName);
        lastNameVec.push_back(lastName);
    }

    // Create 8000 random combinations of names and add to new database
    int count = 0;
    for (const string& firstName : firstNameVec){
        for (const string& middleName : middleNameVec){
            for (const string& lastName : lastNameVec){
                count++;
                // Addresses will all be unique by their street number
                string streetName {"Greenfield St"};
                string address = to_string(count) + " " + streetName;
                // Add as an Employee and put into the Database
                dbNew.addEmployee(firstName, middleName, lastName, address);
            }
        }
    }

    cout << "|-----------------------------------------------|" << endl;
    cout << "| ~ Your New 8000 Employee Database Is Ready ~  |" << endl;
    cout << "|-----------------------------------------------|" << endl;

    log("exited");

    // Return the new Database with 8000 employees 
    return dbNew;

}

// Check and return filename to be used
const string checkFileName() {
    log("entered");
    int selection;
    string filename;
    string ext {".txt"};
    cout << "Enter a filename: ";
    cin >> filename;
    filename+=ext;

    // Iterate through current directory to see if file exists
    filesystem::directory_iterator begin("."), end;
    for (auto iter = begin; iter != end; ++iter)

    // If it is not a directory
    if (iter->is_regular_file())
    {
        string entry {iter->path().filename().string()};
        string entryStem {iter->path().stem().string()};

        // Check full filename with extension and file stem
        if (filename == entry || filename == entryStem)
        {
            cout << "File: " << iter->path().filename() << " already exists." << endl;
            
            // Get user input
            cout << "Select from the following options:" << endl;
            cout << "1) Overwrite this file" << endl;
            cout << "2) Create new file" << endl;
            cout << endl;
            cout << "---> ";
            cin >> selection;

            switch (selection)
                {
                    case 1:
                        cout << "Database successfully saved to file." << endl;
                        return filename;
                        break;
                    case 2:
                        cout << "Enter a filename: ";
                        cin >> filename;
                        filename+=ext;
                        cout << "Database successfully saved to file." << endl;
                        return filename;
                        break;
                    default:
                        cerr << "Unknown command" << endl;
                        break;
                }
        }
    }
    
    // If the file did not exist, create and write to it
    cout << "Database successfully saved to file." << endl;
    
    log("exited");
    return filename;
}

// Load database from file
Database loadDBfromFile() {
    log("entered");
    Database dbNew;
    string filename;
    string ext {".txt"};
    cout << "Enter a filename: ";
    cin >> filename;
    filename+=ext;

    ifstream inputFile{ filename.data() };
	if (inputFile.fail())
    {
		throw invalid_argument{ "Unable to open file" };
    }
    
    while (!inputFile.eof())
    {
        string line;
		getline(inputFile, line);
        
        // Skip empty lines if found
		if (line.empty()) {
			continue;
		}
		
        // Make a string stream and parse it.
		istringstream inLine { line };
		string firstName, middleName, lastName, address, isHired, empNumber, salary;
        
        // Names in the file are quoted so quoted() is needed to separate them
        inLine >> quoted(firstName) >> quoted(middleName) >> quoted(lastName)
               >> quoted(address) >> quoted(isHired) >> quoted(empNumber) >> quoted(salary);
		if (inLine.bad()) {
			cerr << "Error reading person. Ignoring." << endl;
			continue;
		}
        
        // Load into the new database
        dbNew.loadEmployee(firstName, middleName, lastName, address,
                          isHired, empNumber, salary);
    }
    
    log("exited");
    return dbNew;
}

// Edit employee
void editEmployee(Database& db)
{
    log("entered");
    int employeeNumber, selection, newSalary;
    string newAddress, newStatus;

    // Search by employee number required
    // Use option 11) search by name first if needing to find employee number
    cout << "Employee number? ";
    cin >> employeeNumber;

    cout << "Select from the following options" << endl;
    cout << "1) Edit employee address" << endl;
    cout << "2) Edit employee salary" << endl;
    cout << "3) Edit employment status" << endl;
    cout << endl;
    cout << "---> ";
    cin >> selection;

    try {
        Employee& emp = db.getEmployee(employeeNumber);
        cout << "Current employee record: " << endl;
        emp.display();

        switch (selection)
            {
                case 1:
                    cout << "Enter the new address: ";
                    getline(cin >> ws, newAddress);  // Ignores ws within cin input
                    emp.setAddress(newAddress);
                    cout << "Updated address in employee record: " << endl;
                    emp.display();
                    break;
                case 2:
                    cout << "Enter new salary: ";
                    cin >> newSalary;
                    emp.promote(newSalary); // Use existing method to update new salary
                    cout << "Updated salary in employee record: " << endl;
                    emp.display();
                    break;
                case 3:
                    cout << "Enter 'true' for hired. Or 'false' for fired. (without the commas): ";
                    cin >> newStatus;
                    if (newStatus == "true") {
                        emp.hire();
                    } else {
                        emp.fire();
                    }
                    cout << "Updated hired status in employee record: " << endl;
                    emp.display();
                    break;
                default:
                    cerr << "Unknown command" << endl;
                    break;
            }
    } catch (const std::logic_error& exception) {
        cerr << "Unable to edit employee: " << exception.what() << endl;
    }
    
    log("exited");
}

// Search employee
void searchEmployee(Database& db)
{
    log("entered");
    int selection;
    string searchTerm;
    
    cout << "Select from the following search options" << endl;
    cout << "1) Search by first name" << endl;
    cout << "2) Search by middle name" << endl;
    cout << "3) Search by last name" << endl;
    cout << "4) Search by address" << endl;
    cout << endl;
    cout << "---> ";
    cin >> selection;
    cout << endl;
    cout << "Enter the name, address or fragment to search for: ";
    cin >> searchTerm;

    // Parse selection and search term to the method
    try {
        db.searchEmployee(selection, searchTerm);
    } catch (const std::logic_error& exception) {
        cerr << "Unable to search employee: " << exception.what() << endl;
    }
    
    log("exited");  
}

bool authenticate(LogInDataBase& loginDB) {
    string username, password;
    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;

    // Check credentials against the Login Database
    LogIn& user = loginDB.getUser(username, password);
    return user.validate(username, password);
}

bool promptLogin(LogInDataBase& loginDB) {
    const int MAX_ATTEMPTS = 3;
    int attempts = 0;
    bool loggedIn = false;

    while (!loggedIn && attempts < MAX_ATTEMPTS) {
        if (authenticate(loginDB)) {
            loggedIn = true;
            cout << "Logged in successfully!" << endl;
        } else {
            cout << "Invalid username or password. Please try again." << endl;
            attempts++;
        }
    }

    if (!loggedIn) {
        cout << "Maximum login attempts exceeded. Exiting..." << endl;
    }

    return loggedIn;
}