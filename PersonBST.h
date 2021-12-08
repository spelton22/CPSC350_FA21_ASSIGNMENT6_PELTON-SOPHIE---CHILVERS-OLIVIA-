

#ifndef PERSONBST_H
#define PERSONBST_H

#include <iostream>
#include "Person.h"
#include "bst.h"

using namespace std;

template <class T>
class PersonBST : public BST<T>{
public:
  PersonBST();
  virtual ~PersonBST();
  T findNodes(int id); //finds the node with the passed in value
  void recFind(TreeNode<T> *node, int id);//finds a node with the passed in id
  void recReturn(TreeNode<T> *node); // gets all of the sizes of the advisees lists
  void findSizes(); //finds a specific person in the BST
  void recStudent(TreeNode<T> *node); // gets which students dont have an advisor
  int findStudent(); //finds a specific student in the BST
  TreeNode<T>* getRoot(); // gets the root of the bst
  DoublyLinkedList<int> *sizes; // holds the sizes of the advisees lists
  T findFaculty(int size); // finds the faculty with the size that matches their advisee list size
  void recSearch(TreeNode<T> *node, int size); // finds which faculty has the same size advisee list as input
private:
  T foundPerson; //stores a person
  int number; //stores ID of a person
  TreeNode<T> *root; // the root of the tree
};

// constructor
template <class T>
PersonBST<T>::PersonBST(){
  BST<T>();
  root = NULL;
  sizes = new DoublyLinkedList<int>();
}

// destructor
template <class T>
PersonBST<T>::~PersonBST(){
  delete root;
  delete sizes;
}

template <class T>
void PersonBST<T>::recFind(TreeNode<T> *node, int id){ //finds a specific node with passed in id in the tree
  if(node == NULL){
    return;
  }
  recFind(node->left,id);
  int num = node->key.getID();
  if(num == id){ // checks if node has the same id as input
    foundPerson = node->key;
  }
  recFind(node->right,id);
}

template <class T>
T PersonBST<T>::findNodes(int id){ //finds a node in the tree
  root = getRoot();
  recFind(root, id);
  return foundPerson;
}

// finds the advisee list sizes
template <class T>
void PersonBST<T>::recReturn(TreeNode<T> *node){
  if(node == NULL){
    return;
  }
  recReturn(node->left);
  int num = node->key.advisses->getSize(); // creates the linked list with all the advisee list sizes
  sizes->insertFront(num);
  recReturn(node->right);
}

// finds all of the advisee list sizes
template <class T>
void PersonBST<T>::findSizes(){
  root = getRoot();
  recReturn(root);
}

// finds the students that don't have advisors
template <class T>
void PersonBST<T>::recStudent(TreeNode<T> *node){
  if(node == NULL){
    return;
  }
  recStudent(node->left);
  int num = node->key.getAdvisor();
  if(num == -1){ // checks if a student does not have an advisor
    number = node->key.getID();
  }
  else{
    number = 0;
  }
  recStudent(node->right);
}

// finds the students without advisors
template <class T>
int PersonBST<T>::findStudent(){
  root = getRoot();
  recStudent(root);
  return number;
}

// gets the root
template <class T>
TreeNode<T>* PersonBST<T>::getRoot(){
  return BST<T>::getRoot();
}

// finds which faculty has the same advisor list size as input
template <class T>
void PersonBST<T>::recSearch(TreeNode<T> *node, int size){
  //DoublyLinkedList<int> *sizes = new DoublyLinkedList<int>();
  if(node == NULL){
    return;
  }
  recSearch(node->left,size);
  int num = node->key.advisses->getSize();
  if(num == size){ // checks if size of advisee list is the same
    foundPerson = node->key;
  }
  recSearch(node->right,size);
}

// finds the faculty with the same advisor list size as input
template <class T>
T PersonBST<T>::findFaculty(int size){
  root = getRoot();
  recSearch(root,size);
  return foundPerson;
}

#endif
