#include "Transaction.h"

Transaction::Transaction(){
    _amount = -1;
    _date = -1;
}

Transaction::Transaction(double amount, time_t date){
    _amount = amount;
    _date = date;
}

Transaction::Transaction(const Transaction& rhs){
    _amount = rhs._amount;
    _date = rhs._date;
}

bool Transaction::operator<(const Transaction& rhs) const{
    time_t rhs_time, lhs_time;
    rhs_time=rhs._date;
    lhs_time=_date;
    if(difftime(rhs_time,lhs_time)> 0){
        return true;
    }
    return false;
}

bool Transaction::operator>(const Transaction& rhs) const{
    time_t rhs_time, lhs_time;
    rhs_time=rhs._date;
    lhs_time=_date;
    if(difftime(lhs_time,rhs_time)> 0){
        return true;
    }
    return false;
}

bool Transaction::operator<(const time_t date) const{
    time_t current_time = _date;
    if(difftime(date,current_time)>0){
        return true;
    }
    return false;
}

bool Transaction::operator>(const time_t date) const{
    time_t current_time = _date;
    if(difftime(current_time,date)>0){
        return true;
    }
    return false;
}

double Transaction::operator+(const Transaction& rhs){
    double sum = 0;
    sum = _amount + rhs._amount;
    return sum;
}

double Transaction::operator+(const double add){
    double sum = 0;
    sum = add + _amount;
    return sum;
}


Transaction& Transaction::operator=(const Transaction& rhs){
    _amount = rhs._amount;
    _date = rhs._date;
    return *this;
}

std::ostream& operator<<(std::ostream& os, const Transaction& transaction){
    time_t t = transaction._date;
    struct tm *ltm = localtime(&t);
    int hour =  ltm->tm_hour ;
    int minute = ltm->tm_min;
    int second = ltm->tm_sec ;
    int day = ltm->tm_mday;
    int month = ltm->tm_mon +1 ;
    int year = 1900+ ltm->tm_year;

    os << transaction._amount <<"	-	"<<hour<<":"<<minute<<":"<<second<<"-"<<day<<"/"<<month<<"/"<<year<<std::endl;
    return os;

}


