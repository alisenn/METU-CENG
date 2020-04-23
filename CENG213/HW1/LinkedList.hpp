#ifndef LINKED_LIST_HPP
#define LINKED_LIST_HPP

#include <iostream>

#include "Node.hpp"

template <class T>
class LinkedList {
public: // DO NOT CHANGE THIS PART.
    LinkedList();
    LinkedList(const LinkedList &obj);

    ~LinkedList();

    Node<T> *getFirstNode() const;
    int getNumberOfNodes();
    bool isEmpty();

    void insertAtTheFront(const T &data);
    void insertAtTheEnd(const T &data);
    void insertAfterGivenNode(const T &data, Node<T> *prev);

    void removeNode(Node<T> *node);
    void removeAllNodes();

    Node<T> *findNode(const T &data);

    void swapNodes(Node<T> *node1, Node<T> *node2);

    void printAllNodes();

    LinkedList &operator=(const LinkedList &rhs);

private: // YOU MAY ADD YOUR OWN UTILITY MEMBER FUNCTIONS HERE.

private: // DO NOT CHANGE THIS PART.
    Node<T> *head;
    Node<T> *tail;
};

template<class T>
LinkedList<T>::LinkedList() {

  head = tail = NULL;

    /* TODO */
}

template<class T>
LinkedList<T>::LinkedList(const LinkedList &obj) {
  head  = NULL;
  *this = obj;
  /*
  Node<T> *n = obj.getFirstNode();
  cpylink = n;
  while (n) {
    insertAtTheEnd(n->element);
    n = n->next;
  }
  delete n;
  n=NULL;*/
    /* TODO */
}

template<class T>
LinkedList<T>::~LinkedList() {


  removeAllNodes();
/*
  Node<T>* current = head;
  while( current != 0 ) {
      Node<T>* next = current->next;
      delete current;
      current = next;
  }
  head = 0;
  tail=0;*/


    /* TODO */
}

template<class T>
Node<T> * LinkedList<T>::getFirstNode() const {

  return head;
    /* TODO */
}

template<class T>
int LinkedList<T>::getNumberOfNodes() {

  Node <T> *count = head;
  int i=0;
  if(isEmpty()){
    return 0;
  }
  else{
    while(count){
      i++;
      count = count->next;
    }
  }
  delete count; /*count pointerini sil*/
  count= NULL;
  return i;
    /* TODO */
}

template<class T>
bool LinkedList<T>::isEmpty() {

  if(head==NULL && tail == NULL){
    return true;
  }
  else{
    return false;
  }
    /* TODO */
}

template<class T>
void LinkedList<T>::insertAtTheFront(const T &data) {


  Node<T> *hold = head;

  Node<T> *temp = new Node<T>(data,NULL,hold);
  /*temp->element = data;
  temp->next = hold;
  hold->prev = temp;
  temp->prev = NULL;*/
  head = temp;
  if(hold == NULL){
    tail = temp;
  }

    /* TODO */
}

template<class T>
void LinkedList<T>::insertAtTheEnd(const T &data) {


  if(tail == NULL){
    insertAtTheFront(data);
    tail=head;
  }
  else{
    Node<T> *temp = new Node<T>(data,tail,NULL);
    tail->next = temp;
    tail = temp;
  }
    /* TODO */
}

template<class T>
void LinkedList<T>::insertAfterGivenNode(const T &data, Node<T> *prev) {

  Node <T> *tmp = head;
  Node <T> *tmp1 = head;

  if(prev == tail){
    insertAtTheEnd(data);
  }
  else{
  while (tmp) {

if(prev != NULL){
    if(tmp->element == prev->element){

      Node<T> *temp = new Node<T>(data,prev,prev->next);
      prev->next = temp;
      prev->next->next->prev = temp;

      break;
    }
    }

    tmp = tmp->next;

  }
  }
    /* TODO */
}

template<class T>
void LinkedList<T>::removeNode(Node<T> *node) {
  Node<T> *go = head;
  if (go == node ){ // remove the first element
    if(head->next == NULL){
      head = NULL;
      tail = NULL;
    }
    else{
    head = head ->next;
    head->prev = NULL;
    go->next = NULL;
    delete go;
    go = NULL;
    }
  }
  else{
    while(go && go->next){
      if (go->next == node){
        Node<T> *tmp = go->next;
        go->next =tmp->next;
        if(tmp->next){
          tmp->next->prev = go;
        }
        else if(tmp->next == NULL){
          tail = go;
          tail->next = NULL;
        }
        delete tmp;
        tmp = NULL;
      }
      go = go ->next;
    }
  }
    /* TODO */
}

template<class T>
void LinkedList<T>::removeAllNodes() {

  while (head) {
    Node<T> * temp = head;
    head = head->next;
    delete temp;
    temp = NULL;
    if(head)head->prev = NULL;
  }
  delete head;

  head = NULL;
  tail = NULL;

    /* TODO */
}

template<class T>
Node<T> * LinkedList<T>::findNode(const T &data) {


  Node<T> * temp = head;
  while (temp) {
    if(temp->element == data){
      return temp;
    }
    temp = temp->next;
  }

  return NULL;

    /* TODO */
}

template<class T>
void LinkedList<T>::swapNodes(Node<T> *node1, Node<T> *node2) {

  if(node1!=NULL && node2!= NULL && node1!= node2){

    Node<T> * tempn1 = node1->next;
    Node<T> * tempn2 = node2->next;
    Node<T> * tempp1 = node1->prev;
    Node<T> * tempp2 = node2->prev;

  //if both nodes are in the middle and have space
  if(node1!=head && node2 != tail && node1 != tail && node2 != head && node1->next != node2 && node2->next != node1 ){

    node1 ->next = tempn2;
    node2->next = tempn1;
    tempn2->prev = node1;
    tempn1->prev = node2;
    tempp1->next = node2;
    node2->prev = tempp1;
    tempp2->next = node1;
    node1->prev = tempp2;
  }

  else if(((node1->next == node2) ) && ((head != node1 && node2 != tail) && (head != node2 && tail != node1 ))  && node1 != head){ //if both nodes are next to each other

    node1 ->next = node2->next;
    node2->next = node1;
    tempn2 ->prev = node1;
    node2->prev = tempp1 ;
    node1->prev = node2;
    tempp1->next = node2;
  }

  else if(((node2->next == node1) ) && ((head != node1 && node2 != tail) && (head != node2 && tail != node1 )) && node2 != head){ //if both nodes are next to each other

    node2 ->next = node1->next;
    node1->next = node2;
    tempn1 ->prev = node2;
    node1->prev = tempp2 ;
    node2->prev = node1;
    tempp2->next = node1;
  }

  else if((node1 == head) && (node2 != tail) && node1->next != node2){ //if node1 is head

    node1->next = tempn2;
    tempn2->prev = node1;
    tempn1->prev = node2;
    node2->next = tempn1;
    node2->prev = node1->prev;
    node1->prev = tempp2;
    tempp2 ->next = node1;
    head = node2;
  }

  else if(node1== head && node1->next == node2 && node2 != tail){ // node1 is the head and they are next to each other

    node1->next = node2->next;
    node1->prev = node2;
    node2->prev = NULL;
    node2->next = node1;
    tempn2->prev = node1;
    head = node2;

  }
  else if(node2== head && node2->next == node1  && node1 != tail){ // node2 is the head and they are next to each other

    node2->next = node1->next;
    node2->prev = node1;
    node1->prev = NULL;
    node1->next = node2;
    tempn1->prev = node2;
    head = node1;

  }

  else if((node2 == head) && (node1 != tail) && node2->next != node1){ //if node2 is head

    node2->next = tempn1;
    tempn1->prev = node2;
    tempn2->prev = node1;
    node1->next = tempn2;
    node1->prev = node2->prev;
    node2->prev = tempp1;
    tempp1 ->next = node2;
    head = node1;

  }

  else if(node1!= head && node2 == tail  && (node1->next != node2)){ // node2 is the tail

    node1 -> next = node2 ->next;
    node1->prev = tempp2;
    tempp2->next = node1;
    node2->next = tempn1;
    tempn1 ->prev = node2;
    node2->prev = tempp1;
    tempp1 ->next = node2 ;
    tail = node1;
  }

  else if((node1->next == node2) && node2 == tail && node1!= head){ // node2 is the tail and they are next to each other

    node2->next = node1;
    node1->next = NULL;
    node1->prev = node2;
    tempp1 ->next = node2;
    node2->prev = tempp1;
    tail = node1;

  }
  else if((node2->next == node1) && node1 == tail && node2 != head){ // node1 is the tail and they are next to each other

    node1->next = node2;
    node2->next = NULL;
    node2->prev = node1;
    tempp2 ->next = node1;
    node1->prev = tempp2;
    tail = node2;

  }
  else if(node2!= head && node1 == tail && node2->next != node1){ // node1 is the tail

    node2 -> next = node1 ->next;
    node2->prev = tempp1;
    tempp1->next = node2;
    node1->next = tempn2;
    tempn2 ->prev = node1;
    node1->prev = tempp2;
    tempp2 ->next = node1 ;
    tail = node2;

  }

  else if((node1 == head) && (node2 == tail) ){ // if node1 is head and node2 is the tail

    Node<T> *count = head;
    int i=0;
    while (count) {
      i++;
      count = count->next;
    }
      if(i==2){

        node1->next = NULL;
        node1->prev = node2;
        node2->next = node1;
        node2->prev = NULL;
        head = node2;
        tail = node1;
      }
      else if(i==1){
        head = tail = node1;
      }
      else{
        node1-> next = node2->next ;
        node1->prev = tempp2;
        tempp2->next  =  node1;
        node2->next = tempn1;
        node2 ->prev = NULL;
        tempn1 ->prev = node2;

        head = node2;
        tail = node1;
      }
  }

  else if(node2 == head && node1 == tail){ // if node2 is head and node1 is the tail
    Node<T> *count = head;
    int i=0;
    while (count) {
      i++;
      count = count->next;
    }
      if(i==2){
        node2->next = NULL;
        node2->prev = node1;
        node1->next = node2;
        node1->prev = NULL;
        head = node1;
        tail = node2;
      }
      else if(i==1){
        head = tail = node1;
      }
      else{
        node2-> next = node1->next ;
        node2->prev = tempp1;
        tempp1->next  =  node2;
        node1->next = tempn2;
        node1 ->prev = NULL;
        tempn2 ->prev = node1;

        head = node1;
        tail = node2;
      }
  }

}

    /* TODO */
}

template<class T>
void LinkedList<T>::printAllNodes() {

  Node<T> *tmp = head;
  if(tmp != NULL){
    while (tmp) {
      std::cout << *tmp<<"\n";
      tmp = tmp->next;
    }
  }
    /* TODO */
}

template<class T>
LinkedList<T> & LinkedList<T>::operator=(const LinkedList &rhs) {

  if (this != &rhs) {
    removeAllNodes();
    Node<T>* r = rhs.head;
    while (r) {
       insertAtTheEnd(r->element);
       r = r->next;
    }
  }
  return *this;
    /* TODO */
}

#endif //LINKED_LIST_HPP
