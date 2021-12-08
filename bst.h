/* Sophie Pelton
  2370862
  spelton@chapman.edu
  CPSC350-01
  Assignemnt 6
    BST.h
*/

#ifndef BST_H
#define BST_H

#include <iostream>

using namespace std;

template <class T>
class TreeNode{
public:
  TreeNode(); //default constructor
  TreeNode(T k); //overloaded constructor
  virtual ~TreeNode(); //default destructor
  T key; //variable for what is stored in the node
  TreeNode<T> *left; //pointer to node to the left
  TreeNode<T> *right; //pointer to node to the right
};

template <class T>
TreeNode<T>::TreeNode(){ //default constructor
  left = NULL;
  right = NULL;
  key = NULL;
}

template <class T>
TreeNode<T>::TreeNode(T k){ //overloaded constructor
  left = NULL;
  right = NULL;
  key = k;
}

template <class T>
TreeNode<T>::~TreeNode(){ //default destructor
  left = NULL;
  right = NULL;
}

template <class T>
class BST{
  public:
    BST(); //default constructor
    virtual ~BST(); //default destructor
    void insert(T value); //inserts value into the BST
    bool contains(T value); //checks if value is in the BST
    bool deleteNode(T k); //deletes a node with value k from the BST
    bool isEmpty(); //checks if the BST is empty
    T* getMin(); //gets the minimum value of the BST
    T* getMax(); //gets the maximum value
    TreeNode<T> *getSuccessor(TreeNode<T> *d); //gets the successor of the node passed in
    void printNodes(); //prints all the nodes in the tree
    void recPrint(TreeNode<T> *node); //prints all the nodes in the tree
    TreeNode<T>* getRoot();

    TreeNode<T> *root; //pointer to the root/top of the tree
};

template <class T>
BST<T>::BST(){
  root = NULL;
}

template <class T>
BST<T>::~BST(){
}

template <class T>
void BST<T>::recPrint(TreeNode<T> *node){ //prints all the nodes in the tree
  if(node == NULL){
    return;
  }
  recPrint(node->left);
  cout << node->key << endl; // inorder traversal
  recPrint(node->right);
}

template <class T>
void BST<T>::printNodes(){  //prints all the nodes in the tree
  recPrint(root);
}


template <class T>
bool BST<T>::isEmpty(){ //checks if BST is empty
  return (root == NULL);
}

template <class T>
T* BST<T>::getMin(){ //gets node with lowest value in the BST
  TreeNode<T> *current = root;
  if(root == NULL){
    return NULL;
  }
  while(current->left != NULL){
    current = current->left;
  }
  return &(current->key);
}

template <class T>
T* BST<T>::getMax(){ //gets node with largest value in BST
  TreeNode<T> *current = root;
  if(root == NULL){
    return NULL;
  }
  while(current->right != NULL){
    current = current->right;
  }
  return &(current->key);
}

template <class T>
void BST<T>::insert(T value){ //inserts a node into the BST
  TreeNode<T> *node = new TreeNode<T>(value);
  if(isEmpty()){
    root = node;
  }
  else{
    TreeNode<T> *current = root;
    TreeNode<T> *parent = NULL;
    while(true){
      parent = current;
      if(value < current->key){
        current = current->left;
        if(current == NULL){
          parent->left = node;
          break;
        }
      }
      else{
        current = current->right;
        if(current == NULL){
          parent->right = node;
          break;
        }
      }
    }
  }
}

template <class T>
bool BST<T>::contains(T value){ //checks if the passed in value is in the BST
  if(isEmpty()){
    return false;
  }
  else{
    TreeNode<T> *current = root;
    while(current->key != value){
      if(value < current->key){
        current = current->left;
      }
      else{
        current = current->right;
      }
      if(current == NULL){
        return false;
      }
    }
  }
  return true;
}

template <class T>
bool BST<T>::deleteNode(T k){ //deletes a specific node from the tree
  if(isEmpty()){
    return false;
  }
  if(!contains(k)){
    cout << "Value does not exist - Unable to delete" << endl;
    return false;
  }
  TreeNode<T> *current = root;
  TreeNode<T> *parent = root;
  bool isLeft = true;
  while(current->key != k){
    parent = current;
    if(k < current->key){
      isLeft = true;
      current = current->left;
    }
    else{
      isLeft = false;
      current = current->right;
    }
    if(current == NULL){
      return false;
    }
  }
  if(current->left == NULL && current->right == NULL){
    if(current == root){
      root = NULL;
    }
    else if(isLeft){
      parent->left = NULL;
    }
    else{
      parent->right = NULL;
    }
  }
  else if(current->right == NULL){
    if(current == root){
      root = current->left;
    }
    else if(isLeft){
      parent->left = current->left;
    }
    else{
      parent->right = current->left;
    }
  }
  else if(current->left == NULL){
    if(current == root){
      root = current->right;
    }
    else if(isLeft){
      parent->left = current->right;
    }
    else{
      parent->right = current->right;
    }
  }
  else{
    TreeNode<T> *successor = getSuccessor(current);
    if(current == root){
      root = successor;
    }
    else if(isLeft){
      parent->left = successor;
    }
    else{
      parent->right = successor;
    }
    successor->left = current->left;
    current->left = NULL;
    current->right = NULL;
  }
  return true;
}

template <class T>
TreeNode<T>* BST<T>::getSuccessor(TreeNode<T> *d){ //gets the sucessor of the passed in node
  TreeNode<T> *sp = d;
  TreeNode<T> *successor = d;
  TreeNode<T> *current = d->right;

  while(current != NULL){
    sp = successor;
    successor = current;
    current = current->left;
  }
  if(successor != d->right){
    sp->left = successor->right;
    successor->right = d->right;
  }
  return successor;
}

template <class T>
TreeNode<T>* BST<T>::getRoot(){
  return root;
}

#endif
