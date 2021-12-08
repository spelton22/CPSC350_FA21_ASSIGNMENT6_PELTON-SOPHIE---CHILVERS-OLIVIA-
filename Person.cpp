
#include "Person.h"

Person::Person(){ //default constructor
  m_ID = -1;
  m_Name = "";
  m_Level = "";
}

Person::Person(int numID, string name, string level){ //overloaded constructor
  m_ID = numID;
  m_Name = name;
  m_Level = level;
}

Person::~Person(){ //default destructor
}

// sets the person id
void Person::setID(int numID){
  m_ID = numID;
}
// sets the Person name
void Person::setName(string name){
  m_Name = name;
}
// sets the Person level
void Person::setLevel(string level){
  m_Level = level;
}
// returns the Person id
int Person::getID(){
  return m_ID;
}
// returns the Person name
string Person::getName(){
  return m_Name;
}
// returns the Person level
string Person::getLevel(){
  return m_Level;
}

// overloaded operators
bool Person::operator <(const Person& s){ //returns true if the passed in Person is greater than the Person member the operartion is called on
  if(m_ID < s.m_ID){
    return true;
  }
  return false;
}
bool Person::operator >(const Person& s){ //returns true if the passed in Person is less than the Person member the operartion is called on
  if(m_ID < s.m_ID){
    return true;
  }
  return false;
}
bool Person::operator ==(const Person& s){ //returns true if the passed in Person is equal to the Person member the operartion is called on
  if(m_ID < s.m_ID){
    return true;
  }
  return false;
}
bool Person::operator !=(const Person& s){ //returns true if the passed in Person is not equal to the Person member the operartion is called on
  if(m_ID == s.m_ID){
    return false;
  }
  return true;
}
