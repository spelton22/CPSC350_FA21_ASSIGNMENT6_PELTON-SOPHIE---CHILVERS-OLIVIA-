/* Sophie Pelton
  2370862
  spelton@chapman.edu
  CPSC350-01
  Assignemnt 6
    FileProcessor.h
*/

#ifndef FILEPROCESSOR_H
#define FILEPROCESSOR_H

#include <iostream>
#include <string>
#include <fstream>
#include "bst.h"
#include "LinkedList.h"
#include "Student.h"
#include "Faculty.h"
#include <vector>
#include <sstream>
#include "Simulation.h"

using namespace std;

class FileProcessor{
  public:
    FileProcessor(); //default constructor
    ~FileProcessor(); //default destructor
    void processFileStudent(BST<Student> *masterStudent); //processes the file, pass in the input file to read for student
    void processFileFaculty(BST<Faculty> *masterFaculty); //processes the file, pass in the input file to read for faculty
    Student parseStudent(string given_str);
    Faculty parseFaculty(string given_str);
    void initializeStudentAdvisor(BST<Student> *masterStudent, BST<Faculty> *masterFaculty);
};

#endif
