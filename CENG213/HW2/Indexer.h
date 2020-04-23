#ifndef __indexer_h__
#define __indexer_h__

#include <string>
#include "IndexNodeData.h"

#include "BinarySearchTree.h"

class Indexer{
    
public:
    
    // DO NOT modify this part.
    
    Indexer();
    
    ~Indexer();
    
    Indexer(const Indexer & _Indexer);
    
    Indexer& operator=(const Indexer& _Indexer);
    
    void addTerm(string term, Pair p);
    void removeTerm(string term);
    void removeLetter(char letter);
    
    void makeIndexBalanced();
    void makeLetterBalanced(char letter);
    
    bool isIndexBalanced();
    bool isLetterBalanced(char letter);
    
    void printIndex();
    void printLetter(char letter);
    
    void printIndexSideways();
    void printLetterSideways(char letter);
    
    void printAllIndex();
    
    
private:
    
    BinarySearchTree <IndexNodeData> Index;
    
    // You can add your utility functions here.
    
    
};


#endif /* Index_h */
