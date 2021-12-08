/* Sophie Pelton
  2370862
  spelton@chapman.edu
  CPSC350-01
  Assignemnt 6
    Student.cpp
*/

#include "Student.h"

// constructor
Student::Student(){
  Person();
  m_Major = "";
  m_GPA = 0.0;
  m_Advisor = -1;
  idNums = new DoublyLinkedList<int>();}

// overloaded constructor
Student::Student(int s_ID, string s_Name, string s_Level, string s_Major, double s_GPA){ // may not need to be passed in advisor id
  Person(s_ID,s_Name,s_Level);
  m_Major = s_Major;
  m_GPA = s_GPA;
  m_Advisor = -1;
  idNums = new DoublyLinkedList<int>();
}

// destructor
Student::~Student(){
}

// mutators
// sets the student major
void Student::setMajor(string s_Major){
  m_Major = s_Major;
}
// sets the student gpa
void Student::setGPA(double s_GPA){
  m_GPA = s_GPA;
}
// sets the student advisor
void Student::setAdvisor(int s_Advisor){
  m_Advisor = s_Advisor;
}

// accessors
// returns the student major
string Student::getMajor(){
  return m_Major;
}
// returns the student gpa
double Student::getGPA(){
  return m_GPA;
}
// returns the student name
int Student::getAdvisor(){
  return m_Advisor;
}

void Student::printStudent(){
  cout << "Student Name: " << m_Name << endl;
  cout << "ID Number: " << m_ID << endl;
  cout << "Student Level: " << m_Level << endl;
  cout << "Major: " << m_Major << endl;
  cout << "GPA: " << m_GPA << endl;
  cout << "Advisor: " << m_Advisor << endl;
  cout << '\n';
}

int Student::randomSID(){
  int xRan;
  srand(time(0));
  int check = 1;
  if(check != -1){
    xRan = rand()%1000 + 2000;
    check = idNums->find(xRan);
  }
  idNums->insertFront(xRan); // adds the number to the list of existing numbers
  return xRan;
}

void Student::writeStudentFile(){
  //name, ID, major, level, gpa
  cout << m_Name << "," << m_ID << "," << m_Major << "," << m_Level << "," << m_GPA << m_Advisor << endl;
}

void Student::printToFileStudent(ostream &studentOutput){
  //name, ID, major, level, gpa, advisor ID #
  studentOutput << m_Name << "," << m_ID << "," << m_Major << "," << m_Level << "," << m_GPA << "," << m_Advisor;
  studentOutput << "\n";
}
