#include "Employee.h"

Employee::Employee() {
    this->name = "";
    this->experience = -1;
    this->city = "";
    this->ssn = "";
}

Employee::Employee(string name, int experience, string city, string ssn) {
    this->name = name;
    this->experience = experience;
    this->city = city;
    this->ssn = ssn;
}

string Employee::getName() {
    return this->name;
}

void Employee::setName(string name) {
    this->name = name;
}

int Employee::getExperience() {
    return this->experience;
}

void Employee::setExperience (int experience) {
    this->experience = experience;
}

string Employee::getCity() {
    return this->city;
}

void Employee::setCity(string city) {
    this->city = city;
}

string Employee::getSsn() {
    return this->ssn;
}

void Employee::setSsn(string ssn) {
    this->ssn = ssn;
}

bool Employee::compare(Employee employee) {
    if (this->name.compare(employee.getName()) == 0 &&
        this->experience == employee.getExperience() &&
        this->city.compare(employee.getCity()) == 0 &&
        this->ssn.compare(employee.getSsn()) == 0) {
      return true;
    }
    return false;
}
