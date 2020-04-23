
// DO NOT modify this file.

#include "IndexNodeData.h"

// Constructors
IndexNodeData::IndexNodeData()
	: letter('_'){}

IndexNodeData::IndexNodeData(char _letter)
    : letter(_letter){}

IndexNodeData::IndexNodeData(char _letter, BinarySearchTree<TermTreeNodeData>& t)
	: letter(_letter), tree(t){}

// Destructor
IndexNodeData::~IndexNodeData(){}

// Copy constructor
IndexNodeData::IndexNodeData(const IndexNodeData & _IndexNodeData)
{
    this->letter = _IndexNodeData.letter;
    tree = _IndexNodeData.tree;
}

// = operator overloading
IndexNodeData& IndexNodeData::operator=(const IndexNodeData& _IndexNodeData)
{
	if (this != &_IndexNodeData)
    {
		this->letter = _IndexNodeData.letter;
        tree = _IndexNodeData.tree;
	}
	return *this;
}

// == operator overloading
bool IndexNodeData::operator==(const IndexNodeData& _IndexNodeData)
{
    return this->letter == _IndexNodeData.letter;
}

// < operator overloading
bool IndexNodeData::operator<(const IndexNodeData& _IndexNodeData)
{
	return this->letter < _IndexNodeData.letter;
}

// > operator overloading
bool IndexNodeData::operator>(const IndexNodeData& _IndexNodeData)
{
	return this->letter > _IndexNodeData.letter;
}

// << operator overloading
ostream& operator<<(ostream& os, const IndexNodeData& _IndexNodeData)
{
	return os << _IndexNodeData.letter;
}

// gets letter member
char IndexNodeData::getLetter()
{
	return letter;
}

// sets letter member
void IndexNodeData::setLetter(char _letter)
{
	letter = _letter;
}

// gets tree member
BinarySearchTree<TermTreeNodeData> &IndexNodeData::getTree()
{
	return tree;
}

// sets tree member
void IndexNodeData::setTree(BinarySearchTree<TermTreeNodeData> &t)
{
	tree = t;
}

// prints letter and tree elements
void IndexNodeData::print(){
    cout << letter << ":" << endl;
    tree.printVal();
}



