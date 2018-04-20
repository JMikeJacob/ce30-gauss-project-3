#include <cstdlib>
#include <iostream>
#include "matrix.h"

using namespace std;

void readFromFile(Matrix&);

void readFromFile(Matrix& GaussMatrix)
{
  double count = 1;
  GaussMatrix.initMatrix(3,4);
  for(int i = 0; i < 3; i++)
  {
    for(int j = 0; j < 4; j++)
    {
      GaussMatrix.insertElement(i, j, count);
      count++; 
    } 
  }
}
int main(int argc, char *argv[])
{
  Matrix GaussMatrix;
  readFromFile(GaussMatrix);
  GaussMatrix.printMatrix();
  GaussMatrix.switchRows(0,2);
  GaussMatrix.printMatrix();
  GaussMatrix.deleteArrays();
  return 0;
  
}
