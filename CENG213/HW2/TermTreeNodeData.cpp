
// DO NOT modify this file.

#include "TermTreeNodeData.h"

// Constructors
TermTreeNodeData::TermTreeNodeData()
: term(""){}

TermTreeNodeData::TermTreeNodeData(string& _term)
: term(_term){}

TermTreeNodeData::TermTreeNodeData(string& _term, Pair p){
    term = _term;
    pagelist.push_back(p);
}

// Destructor
TermTreeNodeData::~TermTreeNodeData(){}

// Copy constructor
TermTreeNodeData::TermTreeNodeData(const TermTreeNodeData & _TermTreeNodeData){
    this->term = _TermTreeNodeData.term;
    pagelist = _TermTreeNodeData.pagelist;
}

// = operator overloading
TermTreeNodeData& TermTreeNodeData::operator=(const TermTreeNodeData& _TermTreeNodeData){
    if (this != &_TermTreeNodeData)
    {
        this->term = _TermTreeNodeData.term;
        
        if (!pagelist.empty())
            pagelist.clear();
        
        pagelist = _TermTreeNodeData.pagelist;
    }
    return *this;
}

// == operator overloading
bool TermTreeNodeData::operator==(const TermTreeNodeData& _TermTreeNodeData){
    return this->term == _TermTreeNodeData.term;
}

// < operator overloading
bool TermTreeNodeData::operator<(const TermTreeNodeData& _TermTreeNodeData){
    return this->term < _TermTreeNodeData.term;
}

// > operator overloading
bool TermTreeNodeData::operator>(const TermTreeNodeData& _TermTreeNodeData){
    return this->term > _TermTreeNodeData.term;
}

// << operator overloading
ostream& operator<<(ostream& os, const TermTreeNodeData& _TermTreeNodeData){
    os << _TermTreeNodeData.term;
    return os;
}

// adds given page pair to pagelist vector
TermTreeNodeData& TermTreeNodeData::addPage(Pair p){
    Pair indInt(p.start, p.end);
    
    if (pagelist.size() == 0){
        pagelist.push_back(indInt);
    }
    else
    {
        vector<Pair> tmp_pagelist;
        
        for (unsigned int i=0; i<pagelist.size(); i++) {
            tmp_pagelist.push_back(pagelist[i]);
        }
        
        pagelist.clear();
        
        bool isAdded = false;
        
        for (unsigned int i=0; i<tmp_pagelist.size() ; i++) {
            if (indInt.start > tmp_pagelist[i].start ) {
                if (indInt.start > tmp_pagelist[i].end+1 ) {
                    pagelist.push_back(tmp_pagelist[i]);
                }
                else{
                    indInt.start = tmp_pagelist[i].start;
                }
            }
            if (indInt.end < tmp_pagelist[i].end ) {
                if (indInt.end < tmp_pagelist[i].start-1 ) {
                    if(!isAdded){
                        pagelist.push_back(indInt);
                        isAdded = true;
                    }
                    pagelist.push_back(tmp_pagelist[i]);
                }
                else{
                    indInt.end = tmp_pagelist[i].end;
                }
            }
            if (!isAdded && i==tmp_pagelist.size()-1) {
                pagelist.push_back(indInt);
                isAdded = true;
            }
        }
        tmp_pagelist.clear();
        
    }
    
    return *this;
}

// returns term member
string& TermTreeNodeData::getTerm(){
    return term;
}

// sets term member
void TermTreeNodeData::setTerm(string _term){
    term = _term;
}

// prints term and pagelist
void TermTreeNodeData::print(){
    cout << term;
    for (unsigned int i=0; i<pagelist.size(); i++){
        cout << " " << pagelist[i].toString();
    }
    cout << endl;
}


