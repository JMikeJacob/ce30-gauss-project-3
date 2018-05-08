#include "matrix.h"
#include "sigfigs.h"

double Matrix::absv(double value)
{ //absolute value function
  return value*((value > 0) - (value < 0)); 
}

void Matrix::initMatrix(int rowS, int colS)
{  //initialize matrix
  rows = rowS; //specify number of rows
  cols = colS; //specify nubmer of columns
  origRows = rowS; //initial number of rows
  origCols = colS; //initial number of columns
  //cell contains matrix that will be manipulated
  //origMatrix contains the initial matrix from the input file
  cell = new double*[rows];
  origMatrix = new double*[rows];
  for(int i = 0; i < rows; i++)
  {
    cell[i] = new double[cols];
    origMatrix[i] = new double[cols];
  }
  solutions = new double[rows]; //contains the solutions
}

int Matrix::readFromFile(string filename)
{ //file reader function
  int rows = 0, cols = 0;
  double insert = 0.0;
    
  ifstream is;
  is.open(filename.c_str());
  if (!is) //file cannot be opened
  {
    return -1;
  }
  // Read the data
  is >> rows >> cols; //get rows and columns
  initMatrix(rows,cols); //initialize rows x cols matrix
  for (int i = 0; i < rows; i++)
  {
    for (int j = 0; j < cols; j++)
    {
      is >> cell[i][j]; //gets cell data
      origMatrix[i][j] = cell[i][j];
    }
  }
  
  if(rows < cols - 1) //if undetermined system (no solution)
  {
    return 1;
  }
  return 0;
}

void Matrix::switchRows(int row1, int row2)
{ //function for switching rows
  double tmp = 0;
  for(int i = 0; i < cols; i++)
  { //switches row1 and row2 by swapping their elements
    tmp = cell[row1][i];
    cell[row1][i] = cell[row2][i];
    cell[row2][i] = tmp; 
  }
}

int Matrix::identifyPivot(int midRow, int pivotCol)
{ //function for identifying the pivot point
  int pivotPosition = midRow; //current row in gauss elimination
  double pivot = cell[midRow][pivotCol]; //first cell as pivot
  
  for(int i = midRow + 1; i < rows; i++)
  {
    if(absv(cell[i][pivotCol]) > pivot)
    { //if the absolute value of the current cell is greater than
      //the current pivot point, that cell becomes the new pivot
      pivot = absv(cell[i][pivotCol]);
      pivotPosition = i;
    }
  }
  if(pivot == 0.0)
  { //if the entire column is 0, the system moves on to the next col
    return -1;
  }
  return pivotPosition;
}

int Matrix::checkZeroRows(int midRow)
{ //checks if any rows are either completely 0 or has contradiction
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
      if(displaySteps)
      { //0=0 may indicate duplicate linear equation
        cout << "Duplicate linear equation detected." << endl;
      }
      if(rows - 1 < cols - 1)
      { //eliminating row leads to underdetermined system
        return 1; 
      }
      else
      { //the system can still have a unique solution
        switchRows(rows-1, i);
        rows--;
        if(displaySteps)
        {
	        cout << "System can still have unique solution!" << endl;
	        cout << "Remove 0 = 0 Row: " << endl;
          printMatrix();
        }
      }
    }
    else if(countZeroes == cols - midRow - 1)
    { //k = 0, where k is a nonzero constant (contradiction)
      return 2; 
    }   
  }
  return 0;
}

int Matrix::gaussElim()
{ //special cases: duplicate eqns, 0 = 0 (inf), k = 0 (none)
  int pivotRow = 0, zeroCase = 0, zeroPos = 0, pivotCol = 0;
  double factorToZero = 0.0;
  double epsilon = 1.00e-6; //values below epsilon are treated as 0
  for(int i = 0; i < rows - 1; i++)
  {
    zeroCase = checkZeroRows(i);
    if(zeroCase == 1)
    { //underdetermined system
      return 1; 
    }
    else if(zeroCase == 2)
    { //contradiction
      return 2; 
    }
    pivotCol = i;
    do //column with pivot moves for every all-0 column
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
    { //switches top row if it is not the pivot row
      switchRows(i, pivotRow); 
    }
    if(displaySteps) //display current step
    {
      cout << "Iteration " << i + 1 << ": " << endl;
      cout << "Pivot Row " << pivotRow + 1 << endl;
      printMatrix();
    }
    for(int j = i + 1; j < rows; j++)
    { //reduce columns to 0
      if(cell[j][pivotCol] == 0)
      { //no need to calculate if element is already 0
        continue;
      }
      factorToZero = cell[j][pivotCol] / cell[i][pivotCol];
      //a_n / a_i (factor to multiply to pivot row to make column 0
      for(int k = pivotCol; k < cols; k++)
      { //subtract factorToZero*pivotRow from current row
        cell[j][k] -= factorToZero*cell[i][k]; 
        if(absv(cell[j][k]) < epsilon)
        { //treats numbers below |epsilon| as 0
          cell[j][k] = 0; 
        } 
      }
    }
    if(displaySteps) //display current step
    {
      cout << "\nReduce Column " << pivotCol << " to Zero: " << endl;
      printMatrix();
      cout << endl;
    }
  }
  zeroCase = checkZeroRows(rows-1); //final check for zeroes
  return zeroCase; 
}

void Matrix::solveSystem() //solves system using back substitution
{
  //back substition
  cout << endl;
  for(int i = rows - 1; i >= 0; i--)
  { /*Solving for xn in an_xn + ... + a2_x2 + a1_x1 = b 
      can be done by rewriting it as xn = b/an - ... - a2_x2/an - 
      a1_x1/an.*/
    solutions[i] = cell[i][cols-1] / cell[i][i];
    for(int j = i+1; j < cols - 1; j++)
    {
      solutions[i] -= cell[i][j]*solutions[j] / cell[i][i]; 
    }
      cout << "x" << rows - i << " = " << solutions[i] << endl;
  }
}

void Matrix::printMatrix() //prints matrix on console
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

int Matrix::saveToFile(int status) //save results to file
{
  char saveToFile;
  string save;
  int setS = 0;
  cout << "Do you want to save the results to a text file (Y/N)?";
  cin.get(saveToFile);
  cin.clear();
  cin.sync();
  if (saveToFile == 'y' || saveToFile == 'Y')
  {
    cout<< "Filename: ";
    cin >> save;
    cin.sync();
    cin.clear();
    if(save.find(".txt") == string::npos) //adds file extension
    {
      save = save + ".txt";
    }
    ofstream data;
    data.open(save.c_str());
    if(data.is_open()==true)
    { //sets number of sigfigs
      cout<<"How many significant figures?"<< endl;
      cout<< "Answer: ";
      cin>> setS;
      cin.sync();
      cin.clear();
      for(int i=0; i < origRows; i++) //original matrix
      {
        for(int j=0; j< origCols; j++)
        {
          printDouble(data, origMatrix[i][j], setS);
          data << " ";
        }
        data << endl;
      }
      data << endl;
      switch(status)
      {
        case 0: //has unique solution
          for(int i = 0; i < rows; i++)
          {
            data << "x" << i+1 << " = ";
            printDouble(data, solutions[i], setS);
            data << endl; 
          } 
          break;
        case 1: //no unique solution
          data << "No unique solution!" << endl;
          break;
        case 2: //contradiction
          data << "System is inconsistent." << endl;
          break;
        default:
          data << "Error occurred." << endl;
          break; 
      }
      return 0;
    }
    else
    {
      cout << "Error in loading file!"<< endl;
      return 0;
    }
  }
  else if (saveToFile== 'n' || saveToFile == 'N')
  { //no file saved
      return 0;
  }
  else
  { //invalid input
    return -1; 
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
