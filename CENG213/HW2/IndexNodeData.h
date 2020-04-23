
// DO NOT modify this file.

#ifndef __indexnodedata_h__
#define __indexnodedata_h__

#include <iostream>
#include <string>

#include "BinarySearchTree.h"
#include "TermTreeNodeData.h"

using namespace std;

class IndexNodeData{

	public:

		IndexNodeData();
		IndexNodeData(char _letter);
		IndexNodeData(char _letter, BinarySearchTree<TermTreeNodeData>& t);

		~IndexNodeData();
    
        IndexNodeData(const IndexNodeData & _IndexNodeData);

		IndexNodeData& operator=(const IndexNodeData& _L);
		bool operator==(const IndexNodeData& _L);
		bool operator<(const IndexNodeData& _L);
		bool operator>(const IndexNodeData& _L);
		friend ostream& operator<<(ostream& os, const IndexNodeData& _L);

		char getLetter();
		void setLetter(char _letter);
		BinarySearchTree<TermTreeNodeData>& getTree();
		void setTree(BinarySearchTree<TermTreeNodeData>& t);
    
        void print();

	private:

		char letter;
		BinarySearchTree<TermTreeNodeData> tree;

};

		



#endif
