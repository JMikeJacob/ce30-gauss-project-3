#include <cstdlib>
#include <iostream>
#include "matrix.h"

using namespace std;

int readFromFile(Matrix&);

int readFromFile(Matrix& GaussMatrix)
{
  int rows = 3;
  int cols = 4;
  double test[3][4] = {{1,-1,2,-3},
                       {4,4,-2,1},
                       {-2,2,-4,6}};
  GaussMatrix.initMatrix(3,4);
  for(int i = 0; i < 3; i++)
  {
    for(int j = 0; j < 4; j++)
    {
      GaussMatrix.insertElement(i, j, test[i][j]);
    } 
  }
  if(rows < cols - 1) return 1;
  else if (rows > cols - 1) return 2;
  return 0;
}
int main(int argc, char *argv[])
{
  int systemCase = 0;
  Matrix GaussMatrix;
  systemCase = readFromFile(GaussMatrix);
  GaussMatrix.printMatrix();
  if(systemCase == 1)
  {
    cout << "Infinite solutions!" << endl;
    cout << "Less equations than variables detected." << endl;
    return 0;
  }
  else if(systemCase == 2)
  {
    cout << "No possible solution!" << endl;
    cout << "More equations than variables detected." << endl; 
    return 0; 
  }
  systemCase = GaussMatrix.gaussElim();
  switch(systemCase)
  {
    case 0:
      GaussMatrix.solveSystem();
      break;
    case 1:
      cout << "Infinite solutions!" << endl;
      cout << "0 = 0 detected." << endl;
      break;
    case 2:
      cout << "No possible solution!" << endl;
      cout << "Contradictory equation detected." << endl;
      break;
    default:
      cout << "Error occurred." << endl;
      break; 
  }
  
  GaussMatrix.deleteArrays();
  return 0;
  
}
