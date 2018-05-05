#include "matrix.h"

double Matrix::absv(double value)
{
  return value*((value > 0) - (value < 0)); 
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
  if(pivot == 0.0)
  {
    return -1;
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
      else
      {
        break;
      } 
    }
    if(countZeroes == cols - midRow)
    { // 0 = 0
      if(rows - 1 < cols - 1)
      {
        return 1; 
      }
      else
      {
        switchRows(rows-1, i);
        rows--;
	cout << "0 = 0 detected. System can still have unique solution!" << endl;
	cout << "Remove 0 = 0 Row: " << endl;
	printMatrix();
      }
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
  int pivotRow = 0, zeroCase = 0, zeroPos = 0, pivotCol = 0;
  double factorToZero = 0.0;
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
    pivotCol = i;
    do
    {
      pivotRow = identifyPivot(i, pivotCol);
      if(pivotRow == -1)
      {
        pivotCol++;
        if(pivotCol == cols - 1)
        {
          return 1; 
        }
      }
    } while(pivotRow == -1);
    if(pivotRow != i)
    {
      switchRows(i, pivotRow); 
    }
    cout << "Iteration " << i + 1 << ": " << endl;
    cout << "Pivot Row " << pivotRow + 1 << endl;
    printMatrix();
    for(int j = i + 1; j < rows; j++)
    {
      if(cell[j][pivotCol] == 0)
      {
        continue;
      }
      factorToZero = cell[j][pivotCol] / cell[i][pivotCol];
      for(int k = pivotCol; k < cols; k++)
      {
        cell[j][k] -= factorToZero*cell[i][k]; 
        if(absv(cell[j][k]) < epsilon)
        {
          cell[j][k] = 0; 
        } 
      }
    }
    cout << "\nReduce Column " << pivotCol << " to Zero: " << endl;
    printMatrix();
    cout << endl;
  }
  zeroCase = checkZeroRows(rows-1);
  return zeroCase; 
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
    cout << "x" << rows - i << " = " << solutions[i] << endl; 
  }
  //printSolutions(); 
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

void Matrix::deleteArrays()
{
  for(int i = 0; i < rows; i++)
  {
    delete [] cell[i]; 
  } 
  delete [] cell;
  delete [] solutions;
}
