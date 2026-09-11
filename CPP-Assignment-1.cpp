#include <iostream>
#include <string>

using namespace std;

class Employee {
private:
    int empID;
    string name;
    double salary;

public:
    // Constructor
    Employee() {
        cout << "\nConstructor called. Employee object created.\n" << endl;
    }

    // Destructor
    ~Employee() {
        cout << "\nDestructor called. Employee object destroyed.\n" << endl;
    }

    void inputData() {
        cout << "Enter Employee ID: ";
        cin >> empID;
        
        cin.ignore(); 
        
        cout << "Enter Employee Name: ";
        getline(cin, name);
        
        cout << "Enter Employee Salary: ";
        cin >> salary;
    }

    void displayData() {
        cout << "\n--- Employee Details ---" << endl;
        cout << "Employee ID: " << empID << endl;
        cout << "Name: " << name << endl;
        cout << "Salary: " << salary << endl;
    }
};

int main() {
    cout << "Welcome to the Employee Management System" << endl;
    
    Employee e1;
    
    e1.inputData();
    e1.displayData();
    
    return 0;
}