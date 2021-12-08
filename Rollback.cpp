/* Sophie Pelton
  2370862
  spelton@chapman.edu
  CPSC350-01
  Assignemnt 6
    Rollback.cpp
*/

#include "Rollback.h"

Rollback::Rollback(){//default constructor
  command = new GenStack<int>();
  dataStudent = new GenStack<Student>();
  dataFaculty = new GenStack<Faculty>();
}

bool Rollback::isEmpty(){
  if(command->isEmpty()){
    return true;
  }
  return false;
}

Rollback::~Rollback(){ //deafult destructor
}


Student Rollback::insertBackStudent(PersonBST<Student> *masterBST){ //insert back last person that was deleted from BST
  Student s = popStudent(); //gets top of the
  int f_id = s.getAdvisor();
  masterBST->insert(s);
  return s;
}

Student Rollback::deleteLastStudent(PersonBST<Student> *masterBST){//delete last item that was inserted to BST
  Student s = popStudent();
  masterBST->deleteNode(s);
  return s;
}

void Rollback::insertBackFaculty(PersonBST<Faculty> *masterBST){ //insert back last person that was deleted from BST
  Faculty f = popFaculty(); //gets top of the
  masterBST->insert(f);
}

void Rollback::deleteLastFaculty(PersonBST<Faculty> *masterBST){//delete last item that was inserted to BST
  Faculty f = popFaculty();
  masterBST->deleteNode(f);
}

void Rollback::pushCommand(int userCommand){//push last command from user
  command->push(userCommand);
}

int Rollback::popCommand(){//get last last command from user at the top of the stack
  int lastCommand = command->pop();
  return lastCommand;
}

int Rollback::peekCommand(){//see what command is at the top of the stack
  int lastCommand = command->peek();
  return lastCommand;
}

void Rollback::pushStudent(Student s_changed){//push last person from that was changed on BST
  dataStudent->push(s_changed);
}

Student Rollback::popStudent(){//get last person that was changed
  Student s = dataStudent->pop();
  return s;
}

Student Rollback::peekStudent(){//see which person is at the top of the stack
  Student s = dataStudent->peek();
  return s;
}

void Rollback::pushFaculty(Faculty f_changed){//push last person from that was changed on BST
  dataFaculty->push(f_changed);
}

Faculty Rollback::popFaculty(){//get last person that was changed
  Faculty f = dataFaculty->pop();
  return f;
}

Faculty Rollback::peekFaculty(){//see which person is at the top of the stack
  cout << "peek faculty- function" << endl;
  Faculty f = dataFaculty->peek();
  return f;
}

void Rollback::printStack(){
  cout << "command stack" << endl;
  command->print();
  cout << "data faculty stack" << endl;
  dataFaculty->print();
  cout << "data student stack" << endl;
  dataStudent->print();
}
