/* Sophie Pelton
  2370862
  spelton@chapman.edu
  CPSC350-01
  Assignemnt 6
    Simulation.cpp
*/

#include "Simulation.h"

// constructor
Simulation::Simulation(){
  masterStudent = new PersonBST<Student>();
  masterFaculty = new PersonBST<Faculty>();
  r = new Rollback();
}

// destructor
Simulation::~Simulation(){
  delete masterStudent;
  delete masterFaculty;
  delete r;
}

// runs the simulation
void Simulation::runSimulation(){
  // checks for existence of the two files in the directory
  FileProcessor *fp = new FileProcessor();
  fp->processFileStudent(masterStudent);
  fp->processFileFaculty(masterFaculty);
  // prompts the user for input
  cout<< "Welcome to the database! You will be given a menu that allows you to manipulate the database. Please enter the number associated with the command you want to execute." << endl;
  promptUserForInput();
}

// asks the user for input
void Simulation::promptUserForInput(){
  bool run = true;
  // runs and asks for user input until exit
  while(run){
    int numRollback;
    int inputNum = 0;
    string c;
    string f_id = "";
    Student oldStudent(-1,"N/A","N/A","N/A",0.0);
    Student newStudent(-1,"N/A","N/A","N/A",0.0);

    checkStudentsHaveAdvisors(); // checks that students always have an advisor

    cout << endl;
    cout << "1. Print all students and their information (sorted by ascending id #) " << endl;
    cout << "2. Print all faculty and their information (sorted by ascending id #) " << endl;
    cout << "3. Find and display student information given the students id " << endl;
    cout << "4. Find and display faculty information given the faculty id " << endl;
    cout << "5. Given a students id, print the name and info of their faculty advisor " << endl;
    cout << "6. Given a faculty id, print ALL the names and info of his/her advisees. " << endl;
    cout << "7. Add a new student " << endl;
    cout << "8. Delete a student given the id " << endl;
    cout << "9. Add a new faculty member " << endl;
    cout << "10. Delete a faculty member given the id. " << endl;
    cout << "11. Change a students advisor given the student id and the new faculty id. " << endl;
    cout << "12. Remove an advisee from a faculty member given the ids " << endl;
    cout << "13. Rollback " << endl;
    cout << "14. Exit " << endl;

    cin >> c;
    std::istringstream iss(c);

    if(!(iss>>inputNum).fail()){
      // if the user gives improper input, the user is asked again
      if(inputNum < 1 || inputNum > 14){
        cout << "Input must be between 1 and 14" << endl;
        promptUserForInput();
      }

      string faculID = "";
      int factID = -1;

      switch(inputNum){
        case 1:
          //print in ascending order - students
          numRollback = 0;
          masterStudent->printNodes();
          continue;
        case 2:
          //print in ascending order - faculty
          numRollback = 0;
          masterFaculty->printNodes();
          continue;
        case 3:
          //find and print student
          numRollback = 0;
          findStudent();
          continue;
        case 4:
          //find and print faculty
          numRollback = 0;
          cout << "Please enter the ID of the faculty you wish to find: " << endl;
          cin >> faculID;
          factID = stoi(faculID);
          while(checkInputValidity(factID) == false){
            cout << "Please enter the ID of the faculty you wish to find: " << endl;
            cin >> faculID;
            factID = stoi(faculID);
          }
          findFaculty(factID);
          continue;
        case 5:
          numRollback = 0;
          //get student (have id num)
          printFacultyInfoOfStudent();
          continue;
        case 6:
          numRollback = 0;
          //print list of advisees
          printAdviseesInfo();
          continue;
        case 7:
          numRollback = 0;
          //insert/add - student
          if(addStudent() == true){
            cout << "Student was successfully added!" << endl;
          }
          else{
            cout << "Error: Student failed to be added!" << endl;
          }
          continue;
        case 8:
          numRollback = 0;
          //delete / remove - student
          if(deleteStudent() == true){
            cout << "Student was successfully deleted!" << endl;
          }
          else{
            cout << "Error: Student failed to be deleted!" << endl;
          }
          continue;
        case 9:
          numRollback = 0;
          //insert/add - faculty
          if(insertFaculty() == true){
            cout << "Faculty was successfully added!" << endl;
          }
          else{
            cout << "Error: Faculty failed to be added!" << endl;
          }
          continue;
        case 10:
          numRollback = 0;
          //delete/remove - faculty
          if(deleteFaculty() == true){
            cout << "Faculty was successfully deleted!" << endl;
          }
          else{
            cout << "Error: Faculty failed to be deleted!" << endl;
          }
          continue;
        case 11:
          numRollback = 0;
          // changes the student advisor given student id and faculty id
          newStudent = changeStudentAdvisor();
          oldStudent = masterStudent->findNodes(newStudent.getID());
          masterStudent->deleteNode(oldStudent);
          masterStudent->insert(newStudent);
          continue;
        case 12:
          numRollback = 0;
          //remove student from faculty advisee list
          if(removeStudentFromAdviseeList() == true){
            cout << "Student was successfully changed!" << endl;
          }
          else{
            cout << "Error: Student failed to be changed!" << endl;
          }
          continue;
        case 13:
          if(numRollback < 5){
            //keep track of last 5 DB and go to previous one if the command previously executed changed DB
            rollbackCommand();
            ++numRollback ;
          }else{
            cout << "you have called rollback 5 times in a row, you cannot rollback anymore" << endl;
          }

          continue;
        case 14:
          //exit
          PrintCSVFaculty();
          PrintCSVStudent();
          cout << "Goodbye!" << endl;
          run = false;
          break;
        default:
          exit(0);
      }
    }else{
      cout << "Incorrect input. Please enter a number" << endl;
      }
    }
  exit(0);
}

ostream& operator<<(ostream& os, const Faculty& f)
{
  os << "\nFaculty ID: " << f.m_ID << "\nFaculty Name: " << f.m_Name << "\nFaculty Level: " << f.m_Level << "\nFaculty Department: " << f.facultyDepartment ; //print the advisses

  return os;
}

ostream& operator<<(ostream& os, const Student& s)
{
  os << "\nStudent ID: " << s.m_ID << "\nStudent Name: " << s.m_Name << "\nStudent Level: " << s.m_Level << "\nStudent Major: " << s.m_Major << "\nStudent GPA: " << s.m_GPA << "\nStudent's Advisor: " << s.m_Advisor;

  return os;
}

// finds a student and prints their info based on the id
void Simulation::findStudent(){
  cout << endl;
  string studID = "";
  int studentID = -1;
  Student tempStudent(-1,"N/A","N/A","N/A",0.0);
  cout << "Please enter the ID of the student you wish to find: " << endl;
  cin >> studID;
  studentID = stoi(studID);
  // checks that input is valid and asks until it is valid
  while(checkInputValidity(studentID) == false){
    cout << "Please enter the ID of the student you wish to find: " << endl;
    cin >> studID;
    studentID = stoi(studID);
  }
  tempStudent.setID(studentID);
  // checks if the database does not contain the student
  if(masterStudent->contains(tempStudent) == false){
    cout << "Error! No student contains this ID" << endl;
    return;
  }
  else{
    // finds the student with that id
    tempStudent = masterStudent->findNodes(studentID);
    // prints out the information of the student
    tempStudent.printStudent();
  }
}

// finds a faculty member and prints their info based on their id
void Simulation::findFaculty(int facultyID){
  cout << endl;
  DoublyLinkedList<int> *test = new DoublyLinkedList<int>();
  Faculty tempFaculty(-1,"N/A","N/A","N/A",test);
  tempFaculty.setID(facultyID);
  // checks if the database does not contain the faculty
  if(masterFaculty->contains(tempFaculty) == false){
    cout << "Error! No faculty contains this ID" << endl;
    return;
  }
  else{
    // finds the faculty with that id
    tempFaculty = masterFaculty->findNodes(facultyID);
    // prints out the information of the faculty
    tempFaculty.printFaculty();
  }
}

// prints the faculty info the student's advisor
void Simulation::printFacultyInfoOfStudent(){
  cout << endl;
  string studID = "";
  int studentID = -1;
  Student tempStudent(-1,"N/A","N/A","N/A",0.0);
  int facultyToFindID = -1;
  cout << "Please enter the ID of the student you wish to find their faculty info: " << endl;
  cin >> studID;
  studentID = stoi(studID);
  tempStudent.setID(studentID);
  // checks that input is valid and asks until it is valid
  while(checkInputValidity(studentID) == false){
    cout << "Please enter the ID of the student you wish to find their faculty info: " << endl;
    cin >> studID;
    studentID = stoi(studID);
    tempStudent.setID(studentID);
  }
  // checks if the database does not contain the student
  if(masterStudent->contains(tempStudent) == false){
    cout << "Error! No student contains this ID" << endl;
    return;
  }
  else{
    // finds the student with that id
    tempStudent = masterStudent->findNodes(studentID);
    // gets the advisor of the student
    facultyToFindID = tempStudent.getAdvisor();
    // finds the faculty member of the student advisor
    findFaculty(facultyToFindID);
  }
}

// prints all the student's information under a certain faculty member
void Simulation::printAdviseesInfo(){
  cout << endl;
  string facID = "";
  int facultyID = -1;
  int size = 0;
  DoublyLinkedList<int> *test = new DoublyLinkedList<int>();
  Faculty tempFaculty(-1,"N/A","N/A","N/A",test);
  cout << "Please enter the ID of the faculty you wish to find their advisees info: " << endl;
  cin >> facID;
  facultyID = stoi(facID);
  tempFaculty.setID(facultyID);
  // checks that input is valid and asks until it is valid
  while(checkInputValidity(facultyID) == false){
    cout << "Please enter the ID of the faculty you wish to find their advisees info: " << endl;
    cin >> facID;
    facultyID = stoi(facID);
    tempFaculty.setID(facultyID);
  }
  // checks if the database does not contain the faculty
  if(masterFaculty->contains(tempFaculty) == false){
    cout << "Error! No faculty contains this ID" << endl;
    return;
  }
  else{
    // finds the faculty wiht that id
    tempFaculty = masterFaculty->findNodes(facultyID);
    // gets the size of the advisee list
    size = tempFaculty.advisses->getSize();
    // checks if advisee list is empty
    if(size == 0){
      cout << "Faculty has no advisees" << endl;
      return;
    }
    // prints the information of all of the advisees under this faculty member
    PrintAdvisees(tempFaculty);
  }
}

// adds a student to the database
bool Simulation::addStudent(){
  cout << endl;
  Student s(-1,"N/A","N/A","N/A",0.0);
  string name;
  int id;
  string level;
  string major;
  string t_gpa;
  double gpa;

  cin.ignore();
  cout << "Please enter the following info for the student:" << endl;
  cout << "Name: " << endl;
  std::getline(std::cin,name);
  cout << "Level: " << endl;
  std::getline(std::cin,level);
  cout << "Major: " << endl;
  std::getline(std::cin,major);
  cout << "GPA: " << endl;
  cin >> t_gpa;

  bool validGPA = false;

  while(!validGPA){
    cin.ignore();
    try{
      gpa = stod(t_gpa);
      validGPA = true;
    }catch(...){
      cout << "invalid argument for student gpa. please enter a valid gpa number" << endl;
      cin >> t_gpa;
    }
  }

  // produces a random student ID
  id = s.randomSID();
  s.setName(name);
  s.setLevel(level);
  s.setMajor(major);
  s.setGPA(gpa);
  s.setID(id);
  // assigns a student to an advisor
  int facultyID = assignStudentToAdvisor(s);
  // sets the student's advisor
  s.setAdvisor(facultyID);
  r->pushCommand(7);
  r->pushStudent(s);
  // inserts the student into the database
  masterStudent->insert(s);
  return true;
}

// deletes a student from the database
bool Simulation::deleteStudent(){
  cout << endl;
  string studID = "";
  int studentID = -1;
  int facultyID = -1;
  DoublyLinkedList<int> *test = new DoublyLinkedList<int>();
  Faculty f(-1,"N/A","N/A","N/A",test);
  Student tempStudent(-1,"N/A","N/A","N/A",0.0);
  cout << "Please enter the ID of the student you wish to delete: " << endl;
  cin >> studID;
  studentID = stoi(studID);
  tempStudent.setID(studentID);
  // checks that input is valid and asks until it is valid
  while(checkInputValidity(studentID) == false){
    cout << "Please enter the ID of the student you wish to delete: " << endl;
    cin >> studID;
    studentID = stoi(studID);
    tempStudent.setID(studentID);
  }
  // checks if the database does not contain the student
  if(masterStudent->contains(tempStudent) == false){
    cout << "Error! No student contains this ID" << endl;
    return false;
  }
  else{
    // finds the student with that id
    tempStudent = masterStudent->findNodes(studentID);
    // removes the student from faculty's advisee list
    facultyID = tempStudent.getAdvisor();// id of the faculty advisor
    f = masterFaculty->findNodes(facultyID); // the faculty advisor
    f.removeAdvisee(studentID); // removes the advisee from the faculty
    // deletes the student from the database
    r->pushCommand(8);
    r->pushStudent(tempStudent);
    tempStudent.printStudent();
    masterStudent->deleteNode(tempStudent);
    return true;
  }
}

// inerts a faculty member into the database
bool Simulation::insertFaculty(){
  cout << endl;
  string name;
  string level;
  string department;
  int id;
  DoublyLinkedList<int> *test = new DoublyLinkedList<int>();
  Faculty f(-1,"N/A","N/A","N/A",test);
  cin.ignore();
  cout << "Please enter the following info for the faculty:" << endl;
  cout << "Name: " << endl;
  std::getline(std::cin,name);
  cout << "Level: " << endl;
  std::getline(std::cin,level);
  cout << "Department: " << endl;
  std::getline(std::cin,department);
  // produces a random faculty ID
  id = f.randomFID();
  f.setName(name);
  f.setLevel(level);
  f.setDepartment(department);
  f.setID(id);

  r->pushCommand(9);
  r->pushFaculty(f);
  // inserts the faculty into the database
  masterFaculty->insert(f);
  return true;
}

// removes a faculty member from the database
bool Simulation::deleteFaculty(){
  cout << endl;
  string facID = "";
  int facultyID = -1;
  int tempStudentID = -1;
  DoublyLinkedList<int> *test = new DoublyLinkedList<int>();
  Faculty tempFaculty(-1,"N/A","N/A","N/A",test);
  Student tempStudent(-1,"N/A","N/A","N/A",0.0);
  Student newStudent(-1,"N/A","N/A","N/A",0.0);
  cout << "Please enter the ID of the faculty you delete: " << endl;
  cin >> facID;
  facultyID = stoi(facID);
  tempFaculty.setID(facultyID);
  // checks that input is valid and asks until it is valid
  while(checkInputValidity(facultyID) == false){
    cout << "Please enter the ID of the faculty you delete: " << endl;
    cin >> facID;
    facultyID = stoi(facID);
    tempFaculty.setID(facultyID);
  }
  // checks if the database does not contain the faculty
  if(masterFaculty->contains(tempFaculty) == false){
    cout << "Error! No faculty contains this ID" << endl;
    return false;
  }
  else{
    // finds the faculty with that id
    tempFaculty = masterFaculty->findNodes(facultyID);
    // checks if this is the last faculty
    if(checkIfLastFaculty(tempFaculty)){
      cout << "Error: This is the last faculty member" << endl;
      return false;
    }
    r->pushCommand(10);
    r->pushFaculty(tempFaculty);
    // deletes the faculty member from the database
    masterFaculty->deleteNode(tempFaculty);
    // assigns their advisees new advisors
    while(!(tempFaculty.advisses->isEmpty())){
      tempStudentID = tempFaculty.advisses->removeFront(); // removes the student from the list
      tempStudent = masterStudent->findNodes(tempStudentID); // finds the student with that id
      facultyID = assignStudentToAdvisor(tempStudent); // finds a new advisor for the student
      newStudent = tempStudent; // sets new student to temp student
      masterStudent->deleteNode(tempStudent); // removes temp student from the tree
      newStudent.setAdvisor(facultyID); // updates the student's advisor
      masterStudent->insert(newStudent); // inserts the student into the tree
    }
    return true;
  }
}

// changes the advisor of the student
Student Simulation::changeStudentAdvisor(){
  cout << endl;
  string studID = "";
  int studentID = -1;
  string facID = "";
  int facultyID = -1;
  DoublyLinkedList<int> *test = new DoublyLinkedList<int>();
  Faculty tempFaculty(-1,"N/A","N/A","N/A",test);
  Faculty oldFaculty(-1,"N/A","N/A","N/A",test);
  Student tempStudent(-1,"N/A","N/A","N/A",0.0);
  cout << "Please enter the ID of the student you wish to change their advisor: " << endl;
  cin >> studID;
  studentID = stoi(studID);
  tempStudent.setID(studentID);
  // checks that input is valid and asks until it is valid
  while(checkInputValidity(studentID) == false){
    cout << "Please enter the ID of the student you wish to change their advisor: " << endl;
    cin >> studID;
    studentID = stoi(studID);
    tempStudent.setID(studentID);
  }
  // checks if the database does not contain the student
  if(masterStudent->contains(tempStudent) == false){
    cout << "Error! No student contains this ID" << endl;
    return tempStudent;
  }
  else{
    // finds the student with that id
    tempStudent = masterStudent->findNodes(studentID);
    cout << "Please enter the ID of the faculty you wish to assign to this advisee: " << endl;
    cin >> facID;
    facultyID = stoi(facID);
    tempFaculty.setID(facultyID);
    // checks that input is valid and asks until it is valid
    while(checkInputValidity(facultyID) == false){
      cout << "Please enter the ID of the faculty you wish to assign to this advisee: " << endl;
      cin >> facID;
      facultyID = stoi(facID);
      tempFaculty.setID(facultyID);
    }
    // checks if the faculty member is in the tree
    if(masterFaculty->contains(tempFaculty) == false){
      cout << "Error! No faculty contains this ID" << endl;
    }else{
      // checks if the student is already assigned to the advisor
      if(tempStudent.getAdvisor() == facultyID){
        cout << "Error: Student already is assigned to this advisor" << endl;
      }
      else{
        tempFaculty = masterFaculty->findNodes(facultyID); // finds the faculty
        oldFaculty = masterFaculty->findNodes(tempStudent.getAdvisor()); // finds a new faculty
        if(oldFaculty.advisses->getSize() >= 1){ // checks if advisor has 1 or more advisees
          oldFaculty.advisses->removeNode(studentID); // removes student from old advisor's list
        }
        tempStudent.setAdvisor(facultyID); // sets the student with the advisor's id
        tempFaculty.advisses->insertFront(studentID); // assigns student to the advisor
        return tempStudent; // returns the student that has a changed advisor
      }
    }
  }
}

// removes the given student id from a certain faculty
bool Simulation::removeStudentFromAdviseeList(){
  cout << endl;
  string facID = "";
  int facultyID = -1;
  string studID = "";
  int studentID = -1;
  Student tempStudent(-1,"N/A","N/A","N/A",0.0);
  DoublyLinkedList<int> *test = new DoublyLinkedList<int>();
  Faculty tempFaculty(-1,"N/A","N/A","N/A",test);
  cout << "Please enter the ID of the faculty you wish to find their advisees info: " << endl;
  cin >> facID;
  facultyID = stoi(facID);
  tempFaculty.setID(facultyID);
  // checks that input is valid and asks until it is valid
  while(checkInputValidity(facultyID) == false){
    cout << "Please enter the ID of the faculty you wish to find their advisees info: " << endl;
    cin >> facID;
    facultyID = stoi(facID);
    tempFaculty.setID(facultyID);
  }
  // checks if the database does not contain the faculty
  if(masterFaculty->contains(tempFaculty) == false){
    cout << "Error! No faculty contains this ID" << endl;
    return false;
  }
  else{
    // finds the student with that id
    tempFaculty = masterFaculty->findNodes(facultyID);
    // prompts the user for the id of the student
    cout << "Please enter the ID of the student you wish to remove from list: " << endl;
    cin >> studID;
    studentID = stoi(studID);
    tempStudent.setID(studentID);
    // checks that input is valid and asks until it is valid
    while(checkInputValidity(studentID) == false){
      cout << "Please enter the ID of the student you wish to remove from list: " << endl;
      cin >> studID;
      studentID = stoi(studID);
      tempStudent.setID(studentID);
    }
    // checks if the database does not contain the student
    if(masterStudent->contains(tempStudent) == false){
      cout << "Error! No student contains this ID" << endl;
      return false;
    }
    else{
      // finds the student with that id
      tempStudent = masterStudent->findNodes(studentID);
      // checks if the student has that advisor
      if(tempStudent.getAdvisor() != facultyID){
        cout << "Error: This student does not exist in this list" << endl;
        return false;
      }
      else{
        // deletes the student from the advisee list
        tempFaculty.advisses->removeNode(studentID);
        // reassign student to new faculty or entirely remove student
        reassignStudentToAdvisor(studentID, facultyID);
        return true;
      }
    }
  }
}

void Simulation::reassignStudentToAdvisor(int studID, int facultyID){
  DoublyLinkedList<int> *test = new DoublyLinkedList<int>();
  Faculty tempFaculty(-1,"N/A","N/A","N/A",test);
  Faculty faculty(-1,"N/A","N/A","N/A",test);
  Student tempStudent(-1,"N/A","N/A","N/A",0.0);
  Student newStudent(-1,"N/A","N/A","N/A",0.0);
  tempFaculty = masterFaculty->findNodes(facultyID);
  // temporarily removes faculty
  masterFaculty->deleteNode(tempFaculty);
  // checks if there are any more advisors
  if(masterFaculty->isEmpty()){
    cout << "Error: Can not change advisor; No other advisors exist" << endl;
  }
  else{
    // finds the faculty with least number of advisors
    faculty = findperson();
    // assigns the student to that advisor
    faculty.advisses->insertFront(studID); // inserts the student into the advisee list
    tempStudent = masterStudent->findNodes(studID);// finds the student with that student id
    tempStudent.setAdvisor(faculty.getID()); // assigns the student with the faculty id
    newStudent = tempStudent; // sets the new student to the temp student
    masterStudent->deleteNode(tempStudent); // deletes the temp student
    masterStudent->insert(newStudent); // inserts the new student
    // reinserts faculty
    masterFaculty->insert(tempFaculty);
  }
}

int Simulation::assignStudentToAdvisor(Student stud){
  DoublyLinkedList<int> *test = new DoublyLinkedList<int>();
  Faculty faculty(-1,"N/A","N/A","N/A",test);
  faculty = findperson(); // finds faculty with least number of students
  int studID = stud.getID(); // gets the id of the student
  faculty.advisses->insertFront(studID); // adds the student to the advisee list
  return faculty.getID(); // gets the faculty id
}
//handles the rollback option
void Simulation::rollbackCommand(){
  Student s(-1,"N/A","N/A","N/A",0.0);
  DoublyLinkedList<int> *test = new DoublyLinkedList<int>();
  Faculty f(-1,"N/A","N/A","N/A",test);

  int f_id = 0;
  int s_id = 0;

  if(r->isEmpty()){
    cout << "Error: Nothing to rollback" << endl;
  }else{
    int stackNum = r->popCommand();
    //in the insert and delete functions push the command and person to the stack in rollback!!!!
    if(stackNum == 7){ //last command was insert student
      s = r->deleteLastStudent(masterStudent);
      s_id = s.getID();
      f_id = s.getAdvisor();
      f = masterFaculty->findFaculty(f_id);
      f.advisses->removeNode(s_id);
      cout << "Undo: Added student was removed" << endl;
    }else if(stackNum == 8){//last command was delete student
      s = r->insertBackStudent(masterStudent);

      f_id = s.getAdvisor();
      f = masterFaculty->findFaculty(f_id);
      s_id = s.getID();
      assignStudentAdvisor(f, s_id);

      cout << "Undo: Deleted student was readded" << endl;
    }else if(stackNum == 9){//last command was insert faculty
      r->deleteLastFaculty(masterFaculty);
      cout << "Undo: Added faculty was removed" << endl;
    }else if(stackNum == 10){ //last command was delete faculty
      r->insertBackFaculty(masterFaculty);
      cout << "Undo: Deleted faculty was readded" << endl;
    }else{
      cout << "invalid command for rollback" << endl;
    }
  }
}
//inserts the student into the faculty advisee list
void Simulation::assignStudentAdvisor(Faculty f, int s_id){
  f.advisses->insertFront(s_id);
}

void Simulation::PrintAdvisees(Faculty f){
  int studentID = 0;
  Student tempStudent(-1,"N/A","N/A","N/A",0.0);
  // iterates through all of the advisees
  for(int i = 0; i < f.advisses->getSize(); ++i){
    studentID = f.advisses->removeBack(); // temporarily removes the student from the advisee list
    tempStudent = masterStudent->findNodes(studentID);
    tempStudent.printStudent(); // prints the information of the students
    f.advisses->insertFront(studentID); // puts the student back into the advisee list
  }
}

Faculty Simulation::findperson(){
  DoublyLinkedList<int> *test = new DoublyLinkedList<int>();
  Faculty faculty(-1,"N/A","N/A","N/A",test);
  int num = 0;
  int min = 0;
  masterFaculty->findSizes(); // finds the sizes of each facultys advisees list
  if(!(masterFaculty->isEmpty())){
    min = masterFaculty->sizes->removeFront(); // temporarily sets min to the first size value
    // iterate and find smallest!!!
    for(int i = 0; i < masterFaculty->sizes->getSize(); ++i){
      num = masterFaculty->sizes->removeFront(); // checks the sizes from the list
      if(num < min){ // if the num is less than min that it is min
        min = num;
      }
    }
    faculty = masterFaculty->findFaculty(min); // finds the faculty with the advisee list size
    return faculty;
  }
}
//checks if the integer input is a positive number
bool Simulation::checkInputValidity(int input){
  if(input < 0){ // checks if input is positive
    cout << "Error: Input must be a positive number" << endl;
    return false;
  }
  else{
    return true;
  }
}

// checks that students have advisors
void Simulation::checkStudentsHaveAdvisors(){
  int studentID;
  int facultyID;
  Student tempStudent(-1,"N/A","N/A","N/A",0.0);
  Student newStudent(-1,"N/A","N/A","N/A",0.0);
  Student student(-1,"N/A","N/A","N/A",0.0);
  DoublyLinkedList<Student> *studentsToAdd = new DoublyLinkedList<Student>();
  while(!(masterStudent->isEmpty())){ // while the bst is not empty
    studentID = masterStudent->findStudent(); // finds the id of the student without an advisor or 0 if they have advisor
    if(studentID != 0){
      tempStudent = masterStudent->findNodes(studentID); // finds a student with that id
      facultyID = assignStudentToAdvisor(tempStudent); // finds a faculty advisor for the student
      newStudent = tempStudent;
      masterStudent->deleteNode(tempStudent); // removes the student from the tree
      newStudent.setAdvisor(facultyID); // sets the advisor of the student
      studentsToAdd->insertFront(newStudent); // adds it to the students to be readded
    }
    else{
      break;
    }
    studentID = masterStudent->findStudent(); // finds next id
  }
  int size = studentsToAdd->getSize();
  for(int i = 0; i < size; ++i){
    student = studentsToAdd->removeBack();
    masterStudent->insert(student);
  }
}

// checks if there is only one faculty member left
bool Simulation::checkIfLastFaculty(Faculty f){
  masterFaculty->deleteNode(f);
  if(masterFaculty->isEmpty()){
    masterFaculty->insert(f);
    return true;
  }
  else{
    masterFaculty->insert(f);
    return false;
  }
}
//opens the file for writing and calls recPrintCSVFaculty()
void Simulation::PrintCSVFaculty(){
  std::ofstream facultyOutput;
  facultyOutput.open("facultyTable", ios::out | ios::trunc);
  // checks if there is a fail opening the file
  if(facultyOutput.fail()){
    cout << "bad file input" << endl;
    exit(-1);
  }
  if(facultyOutput.is_open()){
    TreeNode<Faculty> *root= masterFaculty->getRoot();
    recPrintCSVFaculty( facultyOutput, root );
  }
}
//recursively prints each node of the tree to the output stream/file
void Simulation::recPrintCSVFaculty(ofstream &facultyOutput, TreeNode<Faculty> *node){
  if(node != NULL){
    node->key.printToFileFaculty(facultyOutput);
    recPrintCSVFaculty( facultyOutput, node->left);
    recPrintCSVFaculty( facultyOutput, node->right);
  }
}
//opens the file for writing and calls recPrintCSVStudent()
void Simulation::PrintCSVStudent(){
  std::ofstream studentOutput;
  studentOutput.open("studentTable", ios::out | ios::trunc);
  // checks if there is a fail opening the file
  if(studentOutput.fail()){
    cout << "bad file input" << endl;
    exit(-1);
  }
  //checks if file is open
  if(studentOutput.is_open()){
    TreeNode<Student> *root= masterStudent->getRoot();
    recPrintCSVStudent( studentOutput, root );
  }
}
//recursively prints each node of the tree to the output stream/file
void Simulation::recPrintCSVStudent(ofstream &studentOutput, TreeNode<Student> *node){
  if(node != NULL){
    node->key.printToFileStudent(studentOutput);
    recPrintCSVStudent( studentOutput, node->left);
    recPrintCSVStudent( studentOutput, node->right);
  }
}
