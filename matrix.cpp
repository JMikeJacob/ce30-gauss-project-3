#include "matrix.h"

double Matrix::absv(double value)
{
  return value*((value > 0) - (value < 0)); 
}

void Matrix::emptyMatrix()
{
  for(int i = 0; i < rows; i++)
  {
    for(int j = 0; j < cols; j++)
    {
       cell[i][j] = 0;   
    }
    solutions[i] = 0; 
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
  solutions = new double[rows];
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

int Matrix::identifyPivot(int midRow, int pivotCol)
{
  int pivotPosition = midRow;
  double pivot = cell[midRow][pivotCol];
  
  for(int i = midRow + 1; i < rows; i++)
  {
   // if(cell[i][pivotCol] == 0) continue;
    if(absv(cell[i][pivotCol]) > pivot)
    {
      pivot = absv(cell[i][pivotCol]);
      pivotPosition = i;
    }
  }
  return pivotPosition;
}

int Matrix::checkZeroRows(int midRow)
{
  int countZeroes = 0;
  for(int i = midRow; i < rows; i++)
  {
    countZeroes = 0;
    for(int j = midRow; j < cols; j++)
    {
      if(cell[i][j] == 0)
      {
        countZeroes++; 
      } 
    }
    if(countZeroes == cols - midRow)
    { // 0 = 0 
      return 1; 
    }
    else if(countZeroes == cols - midRow - 1)
    { //k = 0, k =/= 0
      return 2; 
    }   
  }
  return 0;
}

int Matrix::gaussElim()
{ //special cases: duplicate eqns, 0 = 0 (inf), k = 0 (none)
  int pivotRow = 0, zeroCase = 0;
  double factorToZero = 0;
  double epsilon = 1.00e-6;
  for(int i = 0; i < rows - 1; i++)
  {
    zeroCase = checkZeroRows(i);
    if(zeroCase == 1)
    {
      return 1; 
    }
    else if(zeroCase == 2)
    {
      return 2; 
    }
    pivotRow = identifyPivot(i, i);
    if(pivotRow != i)
    {
      switchRows(i, pivotRow); 
    }
    cout << "Iteration " << i + 1 << ": " << endl;
    cout << "Pivot Row " << pivotRow + 1 << endl;
    printMatrix();
    for(int j = i + 1; j < rows; j++)
    {
      if(cell[j][i] == 0)
      {
        continue;
      }
      factorToZero = cell[j][i] / cell[i][i];
      for(int k = i; k < cols; k++)
      {
        cell[j][k] -= factorToZero*cell[i][k]; 
        if(absv(cell[j][k]) < epsilon)
        {
          cell[j][k] = 0; 
        } 
      }
    }
    cout << "\nReduce Column " << i << " to Zero: " << endl;
    printMatrix();
    cout << endl;
  }
  zeroCase = checkZeroRows(rows-1);
  if(zeroCase == 1)
  {
    return 1; 
  }
  else if(zeroCase == 2)
  {
    return 2; 
  }
  return 0; 
}

void Matrix::solveSystem()
{
  //back substition
  for(int i = rows - 1; i >= 0; i--)
  {
    solutions[i] = cell[i][cols-1] / cell[i][i];
    for(int j = i+1; j < cols - 1; j++)
    {
      solutions[i] -= cell[i][j]*solutions[j] / cell[i][i]; 
    } 
  }
  printSolutions(); 
}

void Matrix::printMatrix()
{
  for(int i = 0; i < rows; i++)
  {
    for(int j = 0; j < cols; j++)
    {
      cout << cell[i][j] << " "; 
    }
    cout << endl; 
  } 
}

void Matrix::printSolutions()
{
  for(int i = 0; i < rows; i++)
  {
    cout << "x" << rows - i << " = ";
    cout << solutions[i] << endl;; 
  } 
}

void Matrix::deleteArrays()
{
  for(int i = 0; i < rows; i++)
  {
    delete [] cell[i]; 
  } 
  delete [] cell;
  delete [] solutions;
}
