#include <iostream>
#include "BinarySearchTree.h"
#include "IndexNodeData.h"
#include "TermTreeNodeData.h"
#include "Indexer.h"

using namespace std;

int main()
{
    Indexer IND;
    
    string terms[6] = {"DAGs", "Abstract data types", "AA-trees", "New line character", "Algorithm design", "Nested loops"};
    
    int pages[24] = {45, 45, 89, 89, 134, 134, 12, 12, 15, 15, 1, 5, 22, 25, 68, 68, 207, 207, 13, 13, 56, 56, 123, 126};
    
    Pair page_intervals[12];
    
    for (int i=0; i<12; i++) {
        page_intervals[i].start = pages[2*i];
        page_intervals[i].end = pages[2*i+1];
    }
    
    // "DAGs"
    IND.addTerm(terms[0], page_intervals[0]);
    IND.addTerm(terms[0], page_intervals[1]);
    
    // "Abstract data types"
    IND.addTerm(terms[1], page_intervals[2]);
    IND.addTerm(terms[1], page_intervals[3]);
    IND.addTerm(terms[1], page_intervals[4]);
    
    // "AA-trees"
    IND.addTerm(terms[2], page_intervals[5]);
    
    // "New line character"
    IND.addTerm(terms[3], page_intervals[6]);
    IND.addTerm(terms[3], page_intervals[7]);
    IND.addTerm(terms[3], page_intervals[8]);
    
    // "Algorithm design"
    IND.addTerm(terms[4], page_intervals[9]);
    
    // "Nested loops"
    IND.addTerm(terms[5], page_intervals[10]);
    IND.addTerm(terms[5], page_intervals[11]);
    
    
    cout << "Index Output:" << endl;
    IND.printAllIndex();
    
    cout << endl;
    cout << "Letter BST:" << endl;
    IND.printIndexSideways();
    
    cout << endl;
    cout << "Letter 'A' BST:" << endl;
    IND.printLetterSideways('A');
    
    cout << endl;
    cout << "Letter 'D' BST:" << endl;
    IND.printLetterSideways('D');
    
    cout << endl;
    cout << "Letter 'N' BST:" << endl;
    IND.printLetterSideways('N');
    
    cout << endl;
    
    return 0;
}











