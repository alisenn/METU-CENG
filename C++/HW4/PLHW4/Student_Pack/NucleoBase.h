#ifndef NUCLEOBASE_H
#define NUCLEOBASE_H

#include <iostream>
class Triangular;
using namespace std;

class NucleoBase {
	/* This class represents a linked list to express RNA and will
		be used only by Triangular microorganisms */
	friend class Triangular;

	private:	// Add private members, methods and constructors here as you need
		char data;
		NucleoBase* prev;
		NucleoBase* next;
		NucleoBase* head;
		NucleoBase* tail;
		string stringrna;

		NucleoBase* add(char data) 
		{ 
		    NucleoBase* newNucleobase = new NucleoBase; 
		    newNucleobase->data = data; 
		    if(head==NULL)
		    {
		        head=newNucleobase;
		        newNucleobase->prev=NULL;
		        newNucleobase->next=NULL;
		        tail=newNucleobase;
		        tail->next = NULL;
		    }
		    else{

		    	newNucleobase->prev =tail;
			    if(tail) tail->next = newNucleobase; //tam burd seg fault var
			    newNucleobase->next = NULL; 
			    tail = newNucleobase;
		    }

		    return newNucleobase; 
		} 
		NucleoBase* stringToLL(string text) 
		{ 
			NucleoBase* head;
		    head = add(text[0]); 
		    NucleoBase* curr = head; 
		  
		    for (int i = 1; i < text.size(); i++) { 
		        curr->next = add(text[i]); 
		        //tail = curr;
		        curr = curr->next; 
		        //curr->prev = curr;
		    } 
		    return head; 
		} 

		void remove(NucleoBase *n){
			NucleoBase *temp = n;
			n=temp->next;
			temp->next->prev=temp->prev;
		    temp->prev->next=temp->next;
		    delete temp;
		}

		NucleoBase(){
			//data = '\0';
			//next = NULL;
			//prev = NULL;
			head = NULL;
			tail = NULL;
		}
		string getStringRna(){
			return stringrna;
		}


	public:		// Do NOT make any modifications below!

		/*********************************************************************
		*									Constructor
		*
		* The first @param is the whole RNA sequence
		* The second parameter is a NucleoBase pointer addressing the previous
		  NucleoBase object. For the initial nucleobase this is NULL.
		*/
		NucleoBase(string, NucleoBase*);
		/*********************************************************************
		*								Copy Constructor
		*
		* Deep copy
		*/
		NucleoBase(const NucleoBase&);
		/*********************************************************************
		*									Destructor
		*
		*/
		~NucleoBase();
		/*********************************************************************
		*									GetLast
		*
		* @return pointer to the last element of NucleoBase chain.
		*/
		NucleoBase* GetLast();
		/*********************************************************************
		*									Stream Operator
		* Prints the data in NucleoBase chain.
		* Prints the char data of each NucleoBase object starting from the
		  given NucleoBase in the @param upto the last element of the chain.
		* Do NOT add new line character "\n" to the end of the stream.
			*/
		friend ostream& operator<<(ostream&, const NucleoBase&);
		/********************************************************************/
};

#endif
