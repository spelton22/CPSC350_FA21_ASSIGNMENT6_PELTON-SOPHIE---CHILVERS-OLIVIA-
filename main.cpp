/* Sophie Pelton
  2370862
  spelton@chapman.edu
  CPSC350-01
  Assignemnt 6
    main.cpp
*/

#include <iostream>
#include "Simulation.h"
#include "FileProcessor.h"
#include "Student.h"
#include "Faculty.h"
#include "bst.h"


using namespace std;

int main(int argc, const char *argv[]){
  try{
    // creates an instance of simulation
    Simulation *s = new Simulation();
    // runs the simulation
    s->runSimulation();
    delete s;
  }
  catch(runtime_error &except){
    cerr << except.what() << endl;
  }
  return 0;
}
