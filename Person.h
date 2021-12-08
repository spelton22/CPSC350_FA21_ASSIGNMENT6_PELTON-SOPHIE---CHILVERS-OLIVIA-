

#ifndef PERSON_H
#define PERSON_H

#include <iostream>
#include <exception>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

using namespace std;

class Person{
  public:
    Person();//default constructor
    Person(int numID, string name, string level); //overloaded constructor
    ~Person(); //default destructor
    // person id
    int m_ID;
    // person name
    string m_Name;
    // person level
    string m_Level;
    void setID(int numID);
    void setName(string name);
    void setLevel(string level);
    int getID();
    string getName();
    string getLevel();
    // if Person is greater than current Person
    bool operator <(const Person& s);
    // if Person is less than current Person
    bool operator >(const Person& s);
    // if Person is equal to current Person
    bool operator ==(const Person& s);
    // if Person is not equal to current Person
    bool operator !=(const Person& s);
};

#endif
