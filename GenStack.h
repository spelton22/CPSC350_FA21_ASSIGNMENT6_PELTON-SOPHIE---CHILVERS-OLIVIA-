/* Sophie Pelton
  2370862
  spelton@chapman.edu
  CPSC350-01
  Assignemnt 6
    GenStack.h
*/

#ifndef GENSTACK_H
#define GENSTACK_H

#include "LinkedList.h"

using namespace std;

template <class T>
class GenStack{
  public:
    GenStack();
    GenStack(int maxSize);
    ~GenStack();
    void push(T d);
    T pop();
    T peek();
    bool isEmpty();
    int getSize();
    void print();
  private:
    ListNode<T> *top;
    int mSize;
    DoublyLinkedList<T> *myLinkedList;
};

template <class T>
void GenStack<T>::print(){
  myLinkedList->printList();
}

// constructor
template <class T>
GenStack<T>::GenStack(){
  mSize = 128;
  top = NULL;
  myLinkedList = new DoublyLinkedList<T>();
}

// overloaded constructor
template <class T>
GenStack<T>::GenStack(int maxSize){
  mSize = maxSize;
  top = NULL;
  myLinkedList = new DoublyLinkedList<T>();
}

// destructor
template <class T>
GenStack<T>::~GenStack(){
  delete myLinkedList;
}

// pushes data onto the stack
template <class T>
void GenStack<T>::push(T d){
  myLinkedList->insertFront(d);
}

// returns and removes data from the stack
template <class T>
T GenStack<T>::pop(){
  if(isEmpty()){ // checks if stack is empty
    throw runtime_error("Error: Empty - Can not pop");
  }
  return myLinkedList->removeFront();
}

// returns the top of the stack without removing
template <class T>
T GenStack<T>::peek(){
  if(isEmpty()){
    throw runtime_error("Error: Empty - Can not peek");
  }
  top = myLinkedList->firstNode(); // gets the first node of the linked list
  return top->data;
}

// checks if the stack is empty
template <class T>
bool GenStack<T>::isEmpty(){
  return (myLinkedList->isEmpty());
}

// returns the size of the stack
template <class T>
int GenStack<T>::getSize(){
  return (myLinkedList->getSize());
}

#endif
