/* Sophie Pelton
  2370862
  spelton@chapman.edu
  CPSC350-01
  Assignemnt 6
    FileProcessor.cpp
*/

#include "FileProcessor.h"


FileProcessor::FileProcessor(){
  //default constructor
}

FileProcessor::~FileProcessor(){
  //default destructor
}

//each line will be a new student and all the information is separated by commas
void FileProcessor::processFileStudent(BST<Student> *masterStudent){
  //creates an input stream to read from a file
  std::string line; //string to hold each line of the file
  ifstream studentFile ("studentTable");

  if(studentFile.fail()){
    masterStudent = new BST<Student>();
  }

  //creates a student
  Student s(0, "", "", "", 0.0);

  //opens the input file for reading
  if(studentFile.is_open()){
    while(getline(studentFile, line)){ //gets every line in the file
      s = parseStudent(line); //sends the line from the file to parse file to create a student object
      masterStudent->insert(s); //inserts student to BST
    }
  }
  studentFile.close(); //closes file after reading
}

void FileProcessor::processFileFaculty(BST<Faculty> *masterFaculty){
  //creates an input stream to read from a file
  bool facultyTableExists = true; //
  std::string line;  //string to hold each line of the file
  ifstream facultyFile ("facultyTable");

  DoublyLinkedList<int> *advisses = new DoublyLinkedList<int>();
  Faculty f(-1,"N/A","N/A","N/A",advisses); //default faculty object

  if(facultyFile.fail()){ //checks if the file failed to open
    facultyTableExists = false;
    masterFaculty = new BST<Faculty>();
  }

  if(facultyTableExists){ //checks if the file could be opened
    //checks if the input and output file is open
    //opens the input file for reading
    if (facultyFile.is_open() ){
      //for loop to go through each line of the file
      for(std::string line; (std::getline(facultyFile, line, '\n')); ){
        f = parseFaculty(line); //sends the line from the file to parse file to create a student object
        masterFaculty->insert(f);//inserts faculty to BST
      }
    }
  }
  facultyFile.close(); //closes file after reading
}

Student FileProcessor::parseStudent(string given_str){
  //name, ID, major, level, gpa, advisor ID #
  Student s(-1,"N/A","N/A","N/A",0.0); //empty student object
  //student member variables
  int s_id = 0;
  string s_name = "";
  string s_level = "";
  string s_major  = "";
  double s_gpa = 0.0;
  int s_advisor = 0;

  int count = 0; //number of iterations
  size_t pos; //string index
  string delim = ","; //deliminator to parse on
  string token1; //holds the substring of the wanted element

  while((pos = given_str.find(delim)) != std::string::npos){ //while loop to parse through the passed in string
    ++count; //increases count each iterations
    token1 = given_str.substr(0, pos); //creates a substring to each deliminator

    switch(count){
      case 1://name
        s_name = token1;
        s.setName(s_name);
        break;
      case 2: //ID
        s_id = std::stoi(token1);
        s.setID(s_id);
        break;
      case 3://major
        s_major = token1;
        s.setMajor(s_major);
        break;
      case 4://level
        s_level = token1;
        s.setLevel(s_level);
        break;
      case 5: //gpa
        s_gpa = stod(token1);
        s.setGPA(s_gpa);
        break;
      default:
        break;
    }
    given_str.erase(0, pos + delim.length()); //resets the string to be the rest of the elements after the token
  }
  //advisor -- placed here since there is no "," after item in the file
  s_advisor = std::stoi(given_str);
  s.setAdvisor(s_advisor);

  return s; //returns the student
}

Faculty FileProcessor::parseFaculty(string given_str){
  //member variables of faculty -- name, ID, department, level, advisees
  int f_id= 0;
  int studentID = 0;
  string f_name = "";
  string f_level = "";
  string f_department = "";
  DoublyLinkedList<int> *advisses = new DoublyLinkedList<int>();
  Faculty f(-1,"N/A","N/A","N/A",advisses); //empty faculty object

  string delim = ",";//deliminator to parse on
  string token1 = ""; //holds the substring of the wanted element
  size_t pos = 0; //string index
  int count = 0; //number of iterations

  while((pos = given_str.find(delim)) != std::string::npos){ //while loop to parse through the passed in string
    ++count;
    token1 = given_str.substr(0, pos); //creates a substring to each deliminator

    switch(count){
    case 1: //name
      f_name = token1;
      f.setName(f_name);
      break;
    case 2: //id #
      f_id = stoi(token1);
      f.setID(f_id);
      break;
    case 3: //department
      f_department = token1;
      f.setDepartment(f_department);
      break;
    case 4: //level
      f_level = token1;
      f.setLevel(f_level);
      break;
    default:
      //place advisee ID number in list
      studentID = stoi(token1);
      f.advisses->insertFront(studentID); // assigns student to the advisor
      break;
    }
    given_str.erase(0, pos + delim.length()); //resets the string to be the rest of the elements after the token
  }
  //last advisee ID number  -- placed here since there is no "," after item in the file
  studentID = stoi(given_str);
  f.advisses->insertFront(studentID); // assigns student to the advisor
  return f;
}
