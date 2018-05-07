#include <cstdlib>
#include <iostream>
#include "matrix.h"

using namespace std;

int main(int argc, char *argv[])
{
  int systemCase = 0;
  bool onCmd = (argc == 1);
  string filename;
  Matrix GaussMatrix;
  if(onCmd)
  {
    cout << "Filename: ";
    cin >> filename;
    cin.clear();
    cin.sync(); 
  }
  else
  {
    filename = argv[1]; 
  }
  systemCase = GaussMatrix.readFromFile(filename);
  GaussMatrix.printMatrix();
  if(systemCase == 1)
  {
    cout << "No unique solution!" << endl;
    cout << "Less equations than variables detected." << endl;
    return 0;
  }
  else if(systemCase == -1)
  {
    cout << "Error opening file!" << endl;
    return 0; 
  }
  GaussMatrix.displaySteps = onCmd;
  systemCase = GaussMatrix.gaussElim();
  switch(systemCase)
  {
    case 0:
      GaussMatrix.solveSystem();
      break;
    case 1:
      cout << "No unique solution!" << endl;
      break;
    case 2:
      cout << "System is inconsistent." << endl;
      break;
    default:
      cout << "Error occurred." << endl;
      break; 
  }
  int loopSave = -1;
  while(loopSave == -1)
  {
    loopSave = GaussMatrix.saveToFile(systemCase);
  }
  GaussMatrix.deleteArrays();
   return 0;
}
