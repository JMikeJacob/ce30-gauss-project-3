#include "matrix.h"

void Matrix::emptyMatrix()
{
  for(int i = 0; i < rows; i++)
  {
    for(int j = 0; j < cols; j++)
    {
       cell[i][j] = 0;   
    }
  } 
}

void Matrix::initMatrix(int rowS, int colS)
{
  rows = rowS;
  cols = colS;
  cell = new double*[rows];
  for(int i = 0; i < rows; i++)
  {
    cell[i] = new double[cols];
  }
  emptyMatrix();
}

void Matrix::insertElement(int rowE, int colE, double value)
{
  cell[rowE][colE] = value;
}

void Matrix::switchRows(int row1, int row2)
{
  double tmp = 0;
  for(int i = 0; i < cols; i++)
  {
    tmp = cell[row1][i];
    cell[row1][i] = cell[row2][i];
    cell[row2][i] = tmp; 
  }
}

void Matrix::printMatrix()
{
  cout << rows << " x " << cols << " Matrix:" << endl;
  for(int i = 0; i < rows; i++)
  {
    for(int j = 0; j < cols; j++)
    {
      cout << cell[i][j] << " "; 
    }
    cout << endl; 
  } 
}

void Matrix::deleteArrays()
{
  for(int i = 0; i < rows; i++)
  {
    delete [] cell[i]; 
  } 
  delete [] cell;
}
