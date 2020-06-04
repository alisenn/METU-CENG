#include "Bank.h"

Bank::Bank(){
	_bank_name = "not_defined";
	_users = nullptr;
	_user_count = 0;
}

Bank::Bank(std::string bank_name, Account* const users, int user_count){
	_bank_name = bank_name;
	_user_count = user_count;
	_users = new Account[user_count];
	for(int i=0; i<user_count; i++){
		_users[i] = users[i];
	}
}

Bank::~Bank(){
	if(_users != nullptr){
		delete[] _users;
	}
	_users = nullptr;
}

Bank::Bank(const Bank& rhs){
	_users = new Account[rhs._user_count];
	for(int i=0; i<rhs._user_count; i++){
		_users[i] = rhs._users[i];
	}
	_bank_name = rhs._bank_name;
	_user_count = rhs._user_count;
}

Bank& Bank::operator+=(const Bank& rhs){
	int allocNum = rhs._user_count + _user_count;
	Account *acs = new Account[allocNum];
	int l=0, k=_user_count;
	for(int i=0; i<_user_count; i++){
		acs[i] = _users[i];
	}

	for(int i=0; i<rhs._user_count; i++){
		if(acs[i] == rhs._users[i]){
			acs[i] += rhs._users[i];
			allocNum--;
		}
		else{
			acs[k] = rhs._users[i];
			k++;
		}
	}
	if(_users != nullptr)
		delete[] _users;
	_users = nullptr;

	_users = new Account[allocNum];

	_user_count = allocNum;
	for(int i=0; i<allocNum; i++){
		_users[i] = acs[i];
	}

	if(acs != nullptr)
		delete [] acs;
	acs = nullptr;
		
	return *this;
}

Bank& Bank::operator+=(const Account& new_acc){

	for(int i=0; i<_user_count; i++){
		if(new_acc == _users[i]){
			_users[i] += new_acc;
		}
	}
	_user_count += 1;
	Account *acs = new Account[_user_count];
	int j;
	for(j=0; j<_user_count-1; j++){
		acs[j] = _users[j];
	}

	if(_users != nullptr)
		delete[] _users;
	_users = nullptr;

	acs[j] = new_acc;
	_users = new Account[_user_count];
	for(j=0; j<_user_count; j++){
		_users[j] = acs[j];
	}

	if(acs != nullptr)
		delete[] acs;
	acs = nullptr;

	return *this;

}

Account& Bank::operator[](int account_id){
	for(int i=0; i<_user_count; i++){
		if(_users[i] == account_id){
			return _users[i];
		}
	}
	return _users[0];

}


std::ostream& operator<<(std::ostream& os, const Bank& bank){
	int numberOfUsersEligibleForLoan = bank._user_count;
	double totalBalance=0;
	int consecutive[12];
	//make time
	time_t startDate[12];
	time_t endDate[12];
	for(int i=0; i<12; i++){
		struct tm start_date = {0};
	    start_date.tm_hour = 0;   start_date.tm_min = 0; start_date.tm_sec = 0;
	    start_date.tm_year = 119; start_date.tm_mon = i; start_date.tm_mday = 1;
	    time_t start_date_time = mktime(&start_date);
	    startDate[i] = start_date_time;
	}
	int endday = 0;
	for(int i=0; i<12; i++){
		endday = 30;
		struct tm end_date = {0};
	    end_date.tm_hour = 23;   end_date.tm_min = 59; end_date.tm_sec = 59;
	    if(i==1) endday =28;
	    if(i ==0 || i== 2 || i==4 || i== 6 || i==7 || i== 9 || i==11) endday =31;
	    end_date.tm_year = 119; end_date.tm_mon = i; end_date.tm_mday = endday;
	    time_t end_date_time = mktime(&end_date);
	    endDate[i] = end_date_time;
	}
	

	for(int i=0; i<12; i++){
		consecutive[i] = 0;
	}
	if(bank._users != nullptr)
		for(int i=0; i<bank._user_count; i++){
			totalBalance += bank._users[i].balance();
			for(int j=0; j<12; j++){
				if(bank._users[i].balance(startDate[j],endDate[j])<0){
					consecutive[j] = 1;
				}
				if( j!=0 && consecutive[j-1] && consecutive[j]){--numberOfUsersEligibleForLoan; break;} 
			}
			for(int k=0; k<12; k++){
				consecutive[k] = 0;
			}
				
			
		}
	
	os<<bank._bank_name<<"	"<<numberOfUsersEligibleForLoan<<"	"<<totalBalance<<std::endl;

}





















