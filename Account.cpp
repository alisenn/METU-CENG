#include "Account.h"

Account::Account(){
	_id = -1;
	_activity = nullptr;
	_monthly_activity_frequency = nullptr;
}

Account::Account(int id, Transaction** const activity, int* monthly_activity_frequency){
   
    for (int i = 0; i < 12; i++) { 
        for (int j = 0; j < monthly_activity_frequency[i]; j++) { 
            for (int k = 0; k < monthly_activity_frequency[i]- j - 1; k++) { 
                if (activity[i][k] > activity[i][k + 1]) {
                    Transaction t = activity[i][k]; 
                    activity[i][k] = activity[i][k + 1]; 
                    activity[i][k + 1] = t; 
                } 
            } 
        } 
    }

    _id = id; 
	_activity = new Transaction*[12];

	for (int i = 0; i < 12; i++)
		_activity[i] = new Transaction[monthly_activity_frequency[i]];

	for (int i = 0; i < 12; i++)
		for (int j = 0; j < monthly_activity_frequency[i]; j++)
			_activity[i][j] = activity[i][j];

    _monthly_activity_frequency = new int[12];
    for(int i=0; i<12;i++){
    	_monthly_activity_frequency[i] = monthly_activity_frequency[i];
    }
 
}

Account::~Account(){
	for (int i = 0; i < 12; i++)
		if((_activity!= nullptr) &&  _activity[i]!= nullptr )
				delete[] _activity[i];

	if(_activity!= nullptr)
		delete[] _activity;

	_activity = nullptr;

	if(_monthly_activity_frequency != nullptr)
		delete[] _monthly_activity_frequency;

	_monthly_activity_frequency = nullptr;
}


Account::Account(const Account& rhs){
	
	_id = rhs._id;
	_activity = new Transaction*[12];

	for (int i = 0; i < 12; i++)
		_activity[i] = new Transaction[rhs._monthly_activity_frequency[i]];

	for (int i = 0; i < 12; i++)
		for (int j = 0; j < rhs._monthly_activity_frequency[i]; j++)
			_activity[i][j] = rhs._activity[i][j];

    _monthly_activity_frequency = new int[12];
    for(int i=0; i<12;i++){
    	_monthly_activity_frequency[i] = rhs._monthly_activity_frequency[i];
    }

}

Account::Account(const Account& rhs, time_t start_date, time_t end_date){
	_id = rhs._id;
	_monthly_activity_frequency = new int[12];
	for(int i=0; i<12; i++){
		_monthly_activity_frequency[i]=0;
	}
	for(int i=0; i<12; i++){
		for(int j=0; j<rhs._monthly_activity_frequency[i]; j++){
			if( (rhs._activity[i][j]> start_date) && (rhs._activity[i][j] < end_date) ){
				_monthly_activity_frequency[i]++; // in that month how many transaction there is
			}
		}
	}
	int l;
	_activity = new Transaction*[12];
	for(int i=0; i<12; i++){
		_activity[i] = new Transaction[_monthly_activity_frequency[i]];
		l=0;
		for(int j=0; j<rhs._monthly_activity_frequency[i]; j++){
			if(  _monthly_activity_frequency[i] && (rhs._activity[i][j]> start_date) && (rhs._activity[i][j] < end_date) ){
				_activity[i][l] = rhs._activity[i][j];
				l++;
				if(_monthly_activity_frequency[i] == l)  l=0;
			}
		}
	}
}

Account::Account(Account&& rhs) 
	:_id(rhs._id), _activity(rhs._activity), _monthly_activity_frequency(rhs._monthly_activity_frequency)
{
	_id = rhs._id;
   	_activity = rhs._activity;
   	_monthly_activity_frequency = rhs._monthly_activity_frequency;

	rhs._activity = nullptr;
	rhs._id = -1;
	rhs._monthly_activity_frequency = nullptr;
}


Account& Account::operator=(Account&& rhs){
	 if (this != &rhs)
    {
		// Free the existing resource. there coul be a problem check later
		if(_monthly_activity_frequency!=nullptr)
			delete[] _monthly_activity_frequency;
		_monthly_activity_frequency= nullptr;

		for (int i = 0; i < 12; i++)
			if( _activity!= nullptr && _activity[i]!=nullptr)
				delete[] _activity[i];

		if(_activity != nullptr)
			delete[] _activity;
		_activity = nullptr;

		_id = rhs._id;
		_activity = rhs._activity;
		_monthly_activity_frequency = rhs._monthly_activity_frequency;

		rhs._id = 0;
		rhs._activity = nullptr;
		rhs._monthly_activity_frequency = nullptr;

    }

   return *this;
}

Account& Account::operator=(const Account& rhs){
	
	_id = rhs._id;

	_activity = new Transaction*[12];

	for (int i = 0; i < 12; i++)
		_activity[i] = new Transaction[rhs._monthly_activity_frequency[i]];

	for (int i = 0; i < 12; i++)
		for (int j = 0; j < rhs._monthly_activity_frequency[i]; j++)
			_activity[i][j] = rhs._activity[i][j];

    _monthly_activity_frequency = new int[12];
    for(int i=0; i<12;i++){
    	_monthly_activity_frequency[i] = rhs._monthly_activity_frequency[i];
    }

	return *this;
}

bool Account::operator==(const Account& rhs) const{
	if(_id==rhs._id){
		return true;
	}
	return false;
}

bool Account::operator==(int id) const{
	if(_id==id){
		return true;
	}
	return false;
}
    

Account& Account::operator+=(const Account& rhs){
	Transaction **new_activity = new Transaction*[12];
	
	for (int i = 0; i < 12; i++)
		new_activity[i] = new Transaction[rhs._monthly_activity_frequency[i] + _monthly_activity_frequency[i]];

	int *new_monthly_activity_frequency = new int[12];

	//update frequency array
	for(int i=0; i<12; i++){
		new_monthly_activity_frequency[i] = rhs._monthly_activity_frequency[i] + _monthly_activity_frequency[i];
	}
	int k=0;
	int l=0;

	//put everything in new_activity array
	for(int i=0; i<12; i++){
		l=0;
		k=0;
		for(int j=0; j< new_monthly_activity_frequency[i] ; j++){
			if(k < _monthly_activity_frequency[i]){
				new_activity[i][j] = _activity[i][k];
				k++;
			}
			else{
				if(l< rhs._monthly_activity_frequency[i]){
					new_activity[i][j] = rhs._activity[i][l];
					l++;
				}
			}
		}
	}
	//allocate memory for this activity array
	for (int i = 0; i < 12; i++)
		if((_activity!= nullptr) &&  _activity[i]!= nullptr )
				delete[] _activity[i];

	if(_activity!= nullptr)
		delete[] _activity;
	_activity = nullptr;

	_activity = new Transaction*[12];
	
	for (int i = 0; i < 12; i++)
		_activity[i] = new Transaction[rhs._monthly_activity_frequency[i] + _monthly_activity_frequency[i]];

	
	for(int i=0; i<12; i++){
		for(int j=0; j<new_monthly_activity_frequency[i] ; j++){
			_activity[i][j] = new_activity[i][j];
		}
	}
	if(_monthly_activity_frequency!= nullptr)
		delete [] _monthly_activity_frequency;
	_monthly_activity_frequency = nullptr;


	_monthly_activity_frequency = new int[12];

	for(int i=0; i<12; i++){
		_monthly_activity_frequency[i] = new_monthly_activity_frequency[i];
	}

	for (int i = 0; i < 12; i++)
		if((new_activity!= nullptr) &&  new_activity[i]!= nullptr )
			delete[] new_activity[i];
	if(new_activity != nullptr)
		delete[] new_activity;
	new_activity = nullptr;
	if(new_monthly_activity_frequency != nullptr)
		delete[] new_monthly_activity_frequency;
	new_monthly_activity_frequency = nullptr;


	return *this;
}

double Account::balance(){
	double sum_amount = 0;

	for(int i=0; i<12; i++){
		if(_monthly_activity_frequency != nullptr)
			for(int j=0; j<_monthly_activity_frequency[i];j++){
				 sum_amount += _activity[i][j] + _activity[i][j] ;
			}
	}
	return sum_amount/2;
}


double Account::balance(time_t end_date){
	double sum_amount = 0;
	for(int i=0; i<12; i++){
		if(_monthly_activity_frequency != nullptr)
			for(int j=0; j<_monthly_activity_frequency[i];j++){
				if(_activity[i][j]<end_date)
					sum_amount += _activity[i][j] + _activity[i][j];
			}
	}
	return sum_amount/2;

}


double Account::balance(time_t start_date, time_t end_date){
	double sum_amount = 0;
	for(int i=0; i<12; i++){
		if(_monthly_activity_frequency != nullptr)
			for(int j=0; j<_monthly_activity_frequency[i];j++){
				if(_activity[i][j]>start_date && _activity[i][j]<end_date)
					sum_amount += _activity[i][j] + _activity[i][j];
			}
	}
	return sum_amount/2;
}

std::ostream& operator<<(std::ostream& os, const Account& account)
{
    Transaction tr ;
    os<<account._id<<std::endl;

    for(int i=0; i<12;i++){
        if(account._monthly_activity_frequency!= nullptr){
            for(int j=0; j<account._monthly_activity_frequency[i]; j++){
                tr = account._activity[i][j];
                os<<tr;
            }
        }

    }
    return os;
}



