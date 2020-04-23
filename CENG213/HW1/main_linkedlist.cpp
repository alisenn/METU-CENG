#include <iostream>

#include "LinkedList.hpp"

int main() {

    LinkedList<int> llist;

    llist.printAllNodes();



    for(int i=1; i< 10;i++){
      llist.insertAtTheEnd(i);
    }
    for (int i=0;i<10;i++){
      for(int j=0;j<10;j++){
          llist.swapNodes(llist.findNode(i),llist.findNode(j));

      }
    }

    for (int i=0;i<10;i++){
      for(int j=0;j<10;j++){
          llist.swapNodes(llist.findNode(j),llist.findNode(i));
/*          std:: cout <<i<<"ile"<<j<<"yi degistirdim sonuc "<<"bu\n";
          llist.printAllNodes();
          std:: cout <<"\n";*/
      }
    }

    llist.removeAllNodes();
    llist.insertAtTheFront(33);
    llist.insertAtTheFront(34);
    llist.insertAtTheFront(35);
    llist.insertAtTheFront(336);
    llist.removeNode(llist.findNode(336));




    llist.insertAfterGivenNode(22,llist.findNode(336));
    llist.removeAllNodes();

    llist.printAllNodes();
/*s
    std:: cout <<llist.isEmpty()<<std::endl;
*/
    /*
    llist.swapNodes(llist.findNode(1),llist.findNode(2));
    llist.swapNodes(llist.findNode(2),llist.findNode(3));
    llist.swapNodes(llist.findNode(3),llist.findNode(5));
    llist.swapNodes(llist.findNode(4),llist.findNode(7));


llist.printAllNodes();

    llist.removeNode(llist.findNode(9));
llist.printAllNodes();
*/

    return 0;
}
