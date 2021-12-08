/* Sophie Pelton
  2370862
  spelton@chapman.edu
  CPSC350-01
  Assignemnt 6
    Simulation.h
*/

#ifndef SIMULATION_H
#define SIMULATION_H

#include <iostream>
#include <exception>
#include <fstream>
//#include <sstream>
#include <string>

#include "Student.h"
#include "Faculty.h"
#include "bst.h"
#include "ctype.h"
#include "Rollback.h"
#include "PersonBST.h"
#include "FileProcessor.h"
#include "limits.h"

using namespace std;

class Simulation{
  public:
    // constructor
    Simulation();
    // destructor
    ~Simulation();
    // runs the simulation
    void runSimulation();
    // asks the user for inputs
    void promptUserForInput();
    // BST instance of students
    PersonBST<Student> *masterStudent;
    // BST instance of faculty
    PersonBST<Faculty> *masterFaculty;
    // finds student based on their id
    void findStudent();
    // finds faculty based on their id
    void findFaculty(int facultyID);
    // prints the faculty info for the advisor of the student
    void printFacultyInfoOfStudent();
    // prints all the advisees infomation under the advisor
    void printAdviseesInfo();
    // adds a student to the database
    bool addStudent();
    // deletes a student from the database
    bool deleteStudent();
    // inserts a faculty into the database
    bool insertFaculty();
    // deletes a faculty from the database
    bool deleteFaculty();
    // changes the advisor of the student
    Student changeStudentAdvisor();
    // removes a student from advisee list
    bool removeStudentFromAdviseeList();
    // assigns student to an advisor
    int assignStudentToAdvisor(Student stud);
    // reassigns student to a new advisor
    void reassignStudentToAdvisor(int studID, int facultyID);
    // checks what command was used
    void rollbackCommand();
    // prints the advisees of the faculty
    void PrintAdvisees(Faculty f);
    // finds the faculty with the least amount of advisees
    Faculty findperson();
    // checks if input is positive
    bool checkInputValidity(int input);
    // checks that all students have an advisor
    void checkStudentsHaveAdvisors();
    // checks if there is only one faculty member left
    bool checkIfLastFaculty(Faculty f);
    // instance of rollback
    Rollback *r; //instance of the rollback class
    void assignStudentAdvisor(Faculty f, int s_id); //assigns the student an advisor and inserts the student ID into the faculty list of advisees

    void recPrintCSVFaculty(ofstream &facultyOutput, TreeNode<Faculty> *node); //recursively prints each node of the tree to the CSV file
    void PrintCSVFaculty(); //opens the file and calls recPrintCSVFaculty()

    void recPrintCSVStudent(ofstream &studentOutput, TreeNode<Student> *root);//recursively prints each node of the tree to the CSV file
    void PrintCSVStudent();//opens the file and calls recPrintCSVStudent() 
};

#endif
