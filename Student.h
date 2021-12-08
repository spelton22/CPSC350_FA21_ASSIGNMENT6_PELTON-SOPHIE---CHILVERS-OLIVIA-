/* Sophie Pelton
  2370862
  spelton@chapman.edu
  CPSC350-01
  Assignemnt 6
    Student.h
*/

#ifndef STUDENT_H
#define STUDENT_H

#include <iostream>
#include <exception>
#include <string>
#include "LinkedList.h"

using namespace std;

#include "Person.h"

class Student : public Person{
  public:
    // constructor
    Student();
    // overloaded constructor
    Student(int s_ID, string s_Name, string s_Level, string s_Major, double s_GPA); // may not need to be passed in advisor id
    // destructor
    ~Student();
    // mutators
    void setMajor(string s_Major);
    void setGPA(double s_GPA);
    void setAdvisor(int s_Advisor);
    // accessors
    string getMajor();
    double getGPA();
    int getAdvisor();
    void printStudent();
    friend ostream& operator<<(ostream& os, const Student& s);
    int randomSID();
    void writeStudentFile();
    void printToFileStudent(ostream &studentOutput);
  private:
    // student major
    string m_Major;
    // student gpa
    double m_GPA;
    // student advisor
    int m_Advisor;
    // student ids
    DoublyLinkedList<int> *idNums;
};

#endif
