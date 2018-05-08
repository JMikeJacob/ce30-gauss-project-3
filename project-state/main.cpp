#include <iostream>
#include "matrix.h"

using namespace std;

int main(int argc, char *argv[])
{
  int systemCase = 0; //indicates state of system
  bool noCmd = (argc == 1); //true if file is not given on cmd line
  string filename;
  Matrix GaussMatrix; //object for matrix
  if(noCmd) //no file on cmd line (activates interactive mode)
  {
    cout << "Filename: ";
    cin >> filename;
    cin.clear();
    cin.sync(); 
  }
  else //file given on cmd line
  {
    filename = argv[1]; 
  }
  systemCase = GaussMatrix.readFromFile(filename); //reads file
  GaussMatrix.printMatrix(); //prints out matrix
  if(systemCase == 1)
  { //if underdetermined system (less equations than variables)
    cout << "No unique solution!" << endl;
    cout << "Less equations than variables detected." << endl;
    return 0;
  }
  else if(systemCase == -1)
  {
    cout << "Error opening file!" << endl;
    return 0; 
  }
  GaussMatrix.displaySteps = noCmd; //true if interactive mode
  systemCase = GaussMatrix.gaussElim(); //gauss elimination proper
  switch(systemCase) //based on value return by gaussElim()
  {
    case 0: //system has unique solution
      GaussMatrix.solveSystem();
      break;
    case 1: //underdetermined or overdetermined system
      cout << "No unique solution!" << endl;
      break;
    case 2: //contradiction e.g. 0 = 1
      cout << "System is inconsistent." << endl;
      break;
    default:
      cout << "Error occurred." << endl;
      break; 
  }
  int loopSave = -1;
  while(loopSave == -1) //loops until input is valid
  {
    loopSave = GaussMatrix.saveToFile(systemCase); //save results
  }
  GaussMatrix.deleteArrays();//deallocate arrays
  return 0;
}
