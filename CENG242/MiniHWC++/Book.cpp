#include "Book.h"
/* YOU MUST WRITE THE IMPLEMENTATIONS OF THE REQUESTED FUNCTIONS
IN THIS FILE. DO NOT MODIFY THE HEADER FILE AS IT WILL BE
REPLACED BY THE ORIGINAL HEADER DURING TESTING. THE REQUIRED
HEADER FILE IS ALREADY INCLUDED FOR YOU ABOVE THIS COMMENT BLOCK.
MOST OF THE METHODS ARE ALREADY IMPLEMENTED. ONLY THE OPERATOR
OVERLOAD ARE LEFT TO YOU. START YOUR IMPLEMENTATIONS BELOW THOSE. */

// DONE
Book::Book() {
	this->next = NULL;
}

// DONE
Book::Book(int ISBN, double price) {
	this->ISBN = ISBN;
	this->price = price;
	this->next = NULL;

}

// DONE
int Book::GetISBN() const {
	return ISBN;
}

// DONE
double Book::GetPrice() const {
	return price;
}

// DONE
Book* Book::GetNext() const {
	return next;
}

// DONE
void Book::SetNext(const Book& book) {
	this->next = book.Clone();
}

// DONE
void Book::SetNext() {
	this->next = NULL;
}

// DONE
Book::~Book() {
	this->next = NULL;	// we should not delete it
}


bool Book::operator<(const Book& book) const{
	if(ISBN<book.ISBN){
		return true;
	}
	return false;
}

bool Book::operator<(int ISBN) const{
	if(this->ISBN < ISBN){
		return true;
	}
	return false;
}

bool Book::operator>(int ISBN) const{
	if(this->ISBN > ISBN){
		return true;
	}
	return false;
}

//Book* Book::Clone() const{
//	return new Book(ISBN,price);
//}