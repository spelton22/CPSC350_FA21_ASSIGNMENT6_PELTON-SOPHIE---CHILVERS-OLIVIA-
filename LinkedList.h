/* Sophie Pelton
  2370862
  spelton@chapman.edu
  CPSC350-01
  Assignemnt 6
    LinkedList.cpp
*/

#ifndef LINKEDLIST_H //header guards
#define LINKEDLIST_H

#include <iostream>
#include <exception>
using namespace std;

template <typename T>
class ListNode{ //template class for a single node in a doubly linked list
  public:
    ListNode(); //default constructor
    ListNode(T d); //overloaded constructor
    ~ListNode(); //default destructor
    ListNode *next; //pointer to the next node
    ListNode *prev; //pointer to the previous node
    T data; //variable for the data in the node
};

//implementation
template <typename T>
ListNode<T>::ListNode(){ //default construcor
  data = NULL;
  next = nullptr;
  prev = nullptr;
}

template <typename T>
ListNode<T>::ListNode(T d){ //overloaded construcor
  data = d;
  next = NULL;
  prev = NULL;
}

template <typename T>
ListNode<T>::~ListNode(){ //default destructor
}

//doubly linked list class
template <typename T>
class DoublyLinkedList{ //template class for a doubly linked list
  public:
    DoublyLinkedList();//default constructor
    ~DoublyLinkedList();//default destructor

    void insertFront(T d);//method to insert node to the front of the list
    void insertBack(T d);//method to insert node to the back of the list
    T removeFront();//method to remove node from the front of the list
    T removeBack();//method to remove node from the back of the list
    T removeNode(T value);//remove a node that has the value passed in
    int find(T value);//find a certain value in a linked list
    bool isEmpty();//check if the doubly linked listis empty
    unsigned int getSize();//get the size of the list
    void printList(); //print the doubly linked list
    void printListFile(ostream &myfileOUT); //print the doubly linked list
    T getFront();//get the front of the list
    ListNode<T>* firstNode();
    void deleteAtPos(int pos);
  private:
    ListNode<T> *front; //member varibale for the front of the doubly linked list
    ListNode<T> *back; //member variable for the back of the list
    unsigned int size; //size of the linked list
};

template <typename T>
DoublyLinkedList<T>::DoublyLinkedList(){ //default constructor
  front = NULL;
  back = NULL;
  size = 0;
}

template <typename T>
DoublyLinkedList<T>::~DoublyLinkedList(){//default destructor
}

template <typename T>
void DoublyLinkedList<T>::printList(){ //print the doubly linked list
  ListNode<T> *curr = front;
  while(curr != 0){
    cout << "[ "<< curr->data << " ]";
    curr = curr->next;
  }
  cout << endl;
}
template <typename T>
void DoublyLinkedList<T>::printListFile(ostream &facultyOutput){
  ListNode<T> *curr = front;
  while(curr != 0){
    facultyOutput << "," << curr->data;
    curr = curr->next;
  }
}

template <typename T>
T DoublyLinkedList<T>::getFront(){ //get the front of the list
  //handle if empty
  //throw exception
  if(isEmpty()){
    throw runtime_error("linked list is empty can not remove");
  }
  return front->data;
}

template <typename T>
bool DoublyLinkedList<T>::isEmpty(){ //check if doubly linked listis empty
  return (size == 0);
}

template <typename T>
void DoublyLinkedList<T>::insertFront(T d){ //instert d to the front of the list
  ListNode<T> *node = new ListNode<T>(d);

  if(isEmpty()){
    back = node;
  }else{
    //not an empty List
    node->next = front;
    front -> prev = node;
  }
  front = node;
  ++size;
}

template <typename T>
void DoublyLinkedList<T>::insertBack(T d){ //insert d to the back of the list
  ListNode<T> *node = new ListNode<T>(d);

  if(isEmpty()){
    front = node;
  }else{
    //not empty
    node -> prev = back;
    back -> next = node;
  }

  back = node;
  ++size;
}

template <typename T>
T DoublyLinkedList<T>::removeFront(){ //remove data from the front of the list
  if(isEmpty()){
    throw runtime_error("linked list is empty can not remove");
  }
  ListNode<T> *temp = front;

  if(front->next == NULL){
    back = NULL;
  } else {
    //we have more than 1 ListNode, doubly linked listsize > 1
    front->next->prev = NULL;
  }

  front = front->next;
  T data = temp->data;
  temp->next = NULL;
  --size;
  delete temp;

  return data;
}

template <typename T>
T DoublyLinkedList<T>::removeBack(){ //remove data from the back of the list
  if(isEmpty()){
    throw runtime_error("linked list is empty can not remove");
  }
  ListNode<T> *temp = back;

  if(back->prev == NULL){
    //only one node of list
    front = NULL;
  }else{
    //more than one node in the list
    back->prev->next = NULL;
  }

  back = back->prev;
  T data = temp->data;
  temp->prev = NULL;
  --size;
  delete temp;

  return data;
}

template <typename T>
int DoublyLinkedList<T>::find(T value){ //find a passed in value in the list
  //return the position
  int pos = -1;
  ListNode<T> *curr = front;

  while(curr != NULL){
    ++pos;
    if(curr->data == value){ //segfault from here
      break;
    }
    curr = curr->next;
  }
  if(curr == NULL){
    pos = -1;
  }
  return pos;
}

template <typename T>
T DoublyLinkedList<T>::removeNode(T value){ //remove a node in the doubly linked listwith the specified value
  if(isEmpty()){
    throw runtime_error("linked list is empty can not remove");
  }
  //we can leverage find method
  ListNode<T> *curr = front;

  while(curr->data != value){
    curr = curr->next;

    if(curr == NULL){
      return -1;
    }
  }
  //we found the node and now curr is in the correct position
  if((curr != front) && (curr != back)){
    //listnode is between front and back
    curr->prev->next = curr->next;
    curr->next->prev = curr->prev;
  }
  if(curr == front){
    front = curr->next;
    if(front != NULL ){
      front->prev = NULL;
    }
  }
  if(curr == back) {
    back = curr->prev;
    if (back != NULL){
      back->next = NULL;
    }
  }
  curr->next = NULL;
  curr->prev = NULL;

  T temp = curr->data;
  --size;
  delete curr;

  return temp;
}

template <typename T>
unsigned int DoublyLinkedList<T>::getSize(){ //returns the size of the doubly linked list
  return size;
}

// returns the front of the linked list
template <class T>
ListNode<T>* DoublyLinkedList<T>::firstNode(){
  return front;
}

// deletes node at position
template <class T>
void DoublyLinkedList<T>::deleteAtPos(int pos){
  if(isEmpty()){
    throw runtime_error("Error: Empty - Can not delete");
  }
  int nodePosition = 0;

  ListNode<T> *curr = front;
  ListNode<T> *prev = front;

  while(nodePosition != pos){
    prev = curr;
    curr = curr->next;
    ++nodePosition;
  }

  prev->next = curr->next;
  curr->next = NULL;
  T d = curr->data;
  --size;
  delete curr;
}

#endif
