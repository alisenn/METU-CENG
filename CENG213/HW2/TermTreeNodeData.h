
// DO NOT modify this file.

#ifndef __termtreenodedata_h__
#define __termtreenodedata_h__

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Pair{
    
public:
    
    int start;
    int end;
    
    // Constructors
    Pair(){}
    
    Pair(int s) {
        start = s;
        end = s;
    }
    
    Pair(int s, int e){
        start = s;
        end = e;
    }
    
    // returns string representaion of Pair
    string toString(){
        if (start == end)
            return to_string(start);
        return to_string(start) + "-" + to_string(end);
    }
};

class TermTreeNodeData {
    
public:
    
    TermTreeNodeData();
    TermTreeNodeData(string& _term);
    TermTreeNodeData(string& _term, Pair p);
    
    TermTreeNodeData(const TermTreeNodeData & _TermTreeNodeData);
    
    ~TermTreeNodeData();
    
    TermTreeNodeData& operator=(const TermTreeNodeData& _S);
    bool operator==(const TermTreeNodeData& _S);
    bool operator<(const TermTreeNodeData& _S);
    bool operator>(const TermTreeNodeData& _S);
    friend ostream& operator<<(ostream& os, const TermTreeNodeData& _S);
    
    TermTreeNodeData& addPage(Pair p);
    string& getTerm();
    void setTerm(string t);
    
    void print();
    
private:
    
    string term;
    vector<Pair> pagelist;
    
};

#endif
