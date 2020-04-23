#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <iostream>
#include <string>

using namespace std;

class Employee{

private:
    string name; // name of the employee. Invalid: ""
    int experience; // experience of the employee in terms of months. Invalid: -1
    string city; // current working place of the employee. Invalid: ""
    string ssn; // ssn of the employee. Invalid: ""

public:
// Constructors
    Employee();
    Employee(string name, int experience, string city, string ssn);

// Getters and setters
    string getName();
    void setName(string name);
    int getExperience();
    void setExperience(int experience);
    string getCity();
    void setCity(string city);
    string getSsn();
    void setSsn(string ssn);

// checks whether given two Employees are same or not.
    bool compare(Employee employee);
};


#endif // EMPLOYEE_H
