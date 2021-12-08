/* Sophie Pelton
  2370862
  spelton@chapman.edu
  CPSC350-01
  Assignemnt 6
    Faculty.cpp
*/

#include "Faculty.h"

Faculty::Faculty(){ //default constructor
  advisses = new DoublyLinkedList<int>();
  Person();
  facultyDepartment = "";
  numStudents = -1;
}

Faculty::Faculty(int id, string name, string level, string department, DoublyLinkedList<int> *ad){//overloaded constructor
  advisses = ad;
  Person(id,name,level);
  facultyDepartment = department;
  numStudents = 0;
}

Faculty::~Faculty(){//default destructor
}

string Faculty::getDepartment(){//returns the faculty department
  return facultyDepartment;
}

void Faculty::setDepartment(string department){//sets the faculty department to the passed in value
  facultyDepartment = department;
}

int Faculty::getNumStudents(){//returns the number of students
  return numStudents;
}

void Faculty::setNumStudents(int numAdvisees){//sets the number of students
  numStudents = numAdvisees;
}

void Faculty::printAdvisees(){ //prints the list of advisses for the faculty
  advisses->printList();
}

void Faculty::removeAdvisee(int studID){ // removes advisee from advisee list
  int pos = advisses->find(studID);
  if (pos != -1 ){
    advisses->removeNode(studID);
    numStudents = numStudents-1;
  }
}

// prints the information of the faculty
void Faculty::printFaculty(){
  cout << "Faculty Name: " << m_Name << endl;
  cout << "ID Number: " << m_ID << endl;
  cout << "Faculty Level: " << m_Level << endl;
  cout << "Faculty Department: " << facultyDepartment << endl;
  cout << "Advisses: ";
  printAdvisees();
  cout << endl;
}

// produces a random ID
int Faculty::randomFID(){
  int xRan;
  srand(time(0));
  int check = 1;
  while(check != -1){
    xRan = rand()%1000 + 1000;
    check = advisses->find(xRan);
  }
  advisses->insertFront(xRan); // adds the number to the list of existing numbers
  return xRan;
}

void Faculty::printToFileFaculty(ostream &facultyOutput){
  //name, ID, department, level, advisees
  facultyOutput << m_Name << "," << m_ID << "," << facultyDepartment << "," << m_Level;
  advisses->printListFile(facultyOutput);
  facultyOutput << "\n";
}
