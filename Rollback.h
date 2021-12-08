/* Sophie Pelton
  2370862
  spelton@chapman.edu
  CPSC350-01
  Assignemnt 6
    Rollback.h
*/

#ifndef ROLLBACK_H
#define ROLLBACK_H
#include <iostream>
#include "GenStack.h"
#include <string>
#include "Student.h"
#include "bst.h"
#include "PersonBST.h"
#include "Faculty.h"

using namespace std;

class Rollback{
public:
  Rollback(); //default constructor
  ~Rollback(); //default destructor
  Student insertBackStudent(PersonBST<Student> *masterBST); //insert back last item that was deleted from BST
  Student deleteLastStudent(PersonBST<Student> *masterBST); //delete last item that was inserted to BST
  void insertBackFaculty(PersonBST<Faculty> *masterBST); //insert back last item that was deleted from BST
  void deleteLastFaculty(PersonBST<Faculty> *masterBST); //delete last item that was inserted to BST
  void pushCommand(int userCommand); //push last command from user
  int popCommand(); //get last last command from user at the top of the stack
  int peekCommand(); //see what command is at the top of the stack
  void pushStudent(Student changed); //push last person from that was changed on BST
  Student popStudent(); //get last person that was changed
  Student peekStudent(); //see which person is at the top of the stack
  void pushFaculty(Faculty changed); //push last person from that was changed on BST
  Faculty popFaculty(); //get last person that was changed
  Faculty peekFaculty(); //see which person is at the top of the stack
  bool isEmpty();
  void printStack();
private:
  GenStack<int> *command; //stack for set of last command
  GenStack<Student> *dataStudent; //stack for set of last people to be changed
  GenStack<Faculty> *dataFaculty; //stack for set of last people to be changed
};

#endif
