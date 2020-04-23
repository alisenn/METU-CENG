#include "EmployeeTable.h"
#include "ItemNotFoundException.h"

EmployeeTable::EmployeeTable() {
// TODO:
    this->BUCKET = 151 ;
    etable = new list<Employee>[BUCKET];
}

EmployeeTable::EmployeeTable(int numberOfBuckets) {
// TODO:
    this->BUCKET = numberOfBuckets ;
    etable = new list<Employee>[BUCKET];
}

EmployeeTable::EmployeeTable(const EmployeeTable& empTable) {
// TODO:
    BUCKET = empTable.BUCKET ;
    //etable = new list<Employee>();
    etable = empTable.etable ;
    /*list<Employee> :: iterator it ;
    for(int i = 0 ; i<=BUCKET ; i++)
    {
        for(it = empTable.etable[i].begin() ; it != empTable.etable[i].end() ; it++)
        {
            this->addEntry(*it);
        }
    }*/
}

EmployeeTable& EmployeeTable:: operator=(const EmployeeTable& rhs) {
// TODO:

    if(this != &rhs)
    {
        this->~EmployeeTable() ;
        BUCKET = rhs.BUCKET ;
        etable = rhs.etable ;
        /*list<Employee> :: iterator it ;
        for(int i = 0 ; i<=BUCKET ; i++)
        {
            for(it = rhs.etable[i].begin() ; it != rhs.etable[i].end() ; it++)
            {
                this->addEntry(*it);
            }
        } */
    }
    return *this ;
}

EmployeeTable::~EmployeeTable() {
// TODO:
    delete[] etable ;
}

int EmployeeTable::hashEmployee(string ssn) {
// TODO:
    if(ssn == "") { return -1 ; }
    long hvalue = 0 ;
    for(int i = 0 ; i < ssn.length() ; i++ )
    {
        hvalue = 31 * hvalue + ssn[i] ;
    }
    if (hvalue<0){ hvalue += BUCKET ; }
    return hvalue ;

}

void EmployeeTable::addEntry(Employee& employee) {
// TODO:
    if(employee.getName() =="" || employee.getExperience() < 0 || employee.getCity() == "" || employee.getSsn() == ""){ return ; }
    int index = hashEmployee(employee.getSsn()) % BUCKET ;
    etable[index].push_back(employee) ;
}

void EmployeeTable::removeEntry(Employee& employee) {
// TODO:
    if(employee.getName() =="" || employee.getExperience() < 0 || employee.getCity() == "" || employee.getSsn() == ""){ return ; }
    int index = hashEmployee(employee.getSsn()) % BUCKET ;
    list<Employee> :: iterator it ;
    for(it = etable[index].begin() ; it != etable[index].end() ; it++ )
    {
        if((*it).getSsn() == employee.getSsn()){ break ; }
    }
    if(it != etable[index].end())
    {
        it = etable[index].erase(it) ;
    }
}

int EmployeeTable::getNumberOfEmployeeInBucket(int bucket) {
// TODO:
    if(bucket < 0 || bucket > BUCKET) { return -1 ; }
    int count = 0 ;
    list<Employee> :: iterator it ;
    for(it = etable[bucket].begin() ; it != etable[bucket].end() ; it++ )
    {
        count ++ ;
    }
    return count ;
}

Employee EmployeeTable::findEmployee(string ssn) {
// TODO:
    if (ssn == ""){throw ItemNotFoundException() ;}
    int index = hashEmployee(ssn) % BUCKET ;
    list<Employee> :: iterator it ;
    for(it = etable[index].begin() ; it != etable[index].end() ; it++ )
    {
        if((*it).getSsn() == ssn){ return *it ; }
    }
    throw ItemNotFoundException();

}
