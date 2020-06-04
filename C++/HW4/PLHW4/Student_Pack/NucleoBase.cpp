#include "NucleoBase.h"

NucleoBase::NucleoBase(string rna, NucleoBase* nb){
	next = stringToLL(rna);
	//cout<<"fsdfsfdsfdsfsdfdsfsdfsdfsdfsd*f*sdf*s*df*sd*f*dsf*sd*fs*"<<*next<<endl;
	head = next;
	prev = nb;
	stringrna = rna;
}

NucleoBase::NucleoBase(const NucleoBase& rhs){

     //tail->setNext(newNode);
       // newNode->setPrevious(tail);
        //tail = tail->next();
    if(rhs.head == NULL)
    	head = tail = NULL; 
    else{
    	head = new NucleoBase;
    	head = rhs.head;
    	NucleoBase* temprhs = rhs.head->next;
    	NucleoBase* temp = head;
    	while(temprhs){
    		temp->next = new NucleoBase;
    		temp->next = temprhs;
    		temp->next->prev = temp;
    		temp= temp->next;
    		temprhs = temprhs->next;
    	}
    	tail = temp;
    	stringrna = rhs.stringrna;
    	/*
    	NucleoBase* nb = new NucleoBase;
		nb = rhs.head;
	    while (nb != NULL){
	     	next = add(nb->data);
	        nb = nb->next;
	    }
	    head = rhs.head;
	    delete nb;*/
    }

}

NucleoBase::~NucleoBase(){

	NucleoBase* n = this->head, *current = NULL;
	while( n ) {
	    current = n;
	    n = n->next;
	    delete (current);
	}
	head = NULL;
	tail = NULL;

}

NucleoBase* NucleoBase::GetLast(){
	return tail;
}

ostream& operator<<(ostream& os, const NucleoBase& rhs){
	NucleoBase* nb = new NucleoBase;
	*nb = rhs;
	while(nb != NULL){
		os<<nb->data;
		nb=nb->next;
	}
	delete nb;
	return os;
}
