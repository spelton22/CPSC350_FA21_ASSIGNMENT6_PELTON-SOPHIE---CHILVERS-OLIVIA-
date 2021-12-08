/* Sophie Pelton
  2370862
  spelton@chapman.edu
  CPSC350-01
  Assignemnt 6
    Faculty.h
*/

#ifndef FACULTY_H
#define FACULTY_H

#include <iostream>
#include <exception>
#include <string>
#include "LinkedList.h"
#include "Person.h"
using namespace std;

class Faculty : public Person{
private:
  string facultyDepartment;//member variable for faculty department
  // student ids
  //DoublyLinkedList<int> *idNums;

public:
  Faculty(); //default constructor
  Faculty(int id, string name, string level, string department, DoublyLinkedList<int> *ad); //overloaded constructor
  ~Faculty();//default destructor
  string getDepartment(); //returns the faculty Department
  void setDepartment(string department);//sets the faculty department to the passed in value
  int getNumStudents(); //returns the number of students
  void setNumStudents(int numAdvisees);//sets the number of students
  void printAdvisees(); //prints the list of advisses for the faculty
  void printFaculty(); //prints an individual faculty members information
  friend ostream& operator<<(ostream& os, const Faculty& f);
  int randomFID(); // produces a random ID
  DoublyLinkedList<int> *advisses; //member list for the advisses ID numbers
  int numStudents; // number of advisees
  void removeAdvisee(int studID); // removes advisee from adviser list
  void printToFileFaculty(ostream &myfileOUT);
};

#endif
