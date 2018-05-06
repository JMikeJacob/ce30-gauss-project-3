#include <cstdlib>
#include <iostream>
#include "matrix.h"

using namespace std;

int readFromFile(Matrix&);

int readFromFile(Matrix& GaussMatrix)
{
    int rows, cols;
    const char * filename;
    cout << "Filename: ";
    cin >> filename;
    
    ifstream is(filename);

    if (!is)
    {
        cout << "Unable to open file: " << filename << endl;
        return 1;
    }

    int rows = 0, cols = 0;

    if (!(is >> rows >> cols))
        cout << "Error reading dimensions" << endl;
    else
        cout << "Rows: " << rows << "  Columns: " << cols << endl;

    GaussMatrix.initMatrix(rows,cols)
    
    // Read the data
    for (int i = 0; i<rows; i++)
        for (int j=0; j< cols; j++)
            is >> board[i][j];
            GaussMatrix.insertElement(i, j, test[i][j])
  
  if(rows < cols - 1) return 1;
  return 0;

  /*int rows = 3;
  int cols = 4;
  double test[3][4] = {{1,2,3,4},
                       {5,6,7,8},
                       {9,10,11,12}};
  GaussMatrix.initMatrix(3,4);
  for(int i = 0; i < 3; i++)
  {
    for(int j = 0; j < 4; j++)
    {
      GaussMatrix.insertElement(i, j, test[i][j]);
    } 
  }
  if(rows < cols - 1) return 1;
  return 0;*/
}
int main(int argc, char *argv[])
{
  int systemCase = 0;
  Matrix GaussMatrix;
  systemCase = readFromFile(GaussMatrix);
  GaussMatrix.printMatrix();
  if(systemCase == 1)
  {
    cout << "No unique solution!" << endl;
    cout << "Less equations than variables detected." << endl;
    return 0;
  }
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
  
  GaussMatrix.deleteArrays();
  return 0;
   //start of save to file part
  int rows = 3, cols = 4;
    double matrix[rows][cols] = {{1,2,3,4}, {5,6,7,8},{9,10,11,12}};
    string save;
    int setS, num;
    string saveToFile;
    cout << "Do you want to save the results to a text file? (Yes or No?)\nAnswer: ";
    cin>> saveToFile;
    cin.clear();
    if (saveToFile=="yes" || saveToFile=="Yes")
    {
      cout << "To which text file would you want to save your data?"<< endl;
      cout<< "Filename: ";
      cin >> save;
      cin.clear();
      if(save.find(".txt") == string::npos) //adds file extension
      {
        save = save + ".txt";
      }
      ofstream data;
      data.open(save);
      if(data.is_open()==true)
      {
        cout<<"How many significant digits do you like in presenting your data?"<< endl;
        cout<< "Answer: ";
        cin>> setS;
        cin.clear();
        for(int i=0; i<rows; i++)
        {
            for(int j=0; j<cols; j++)
            {
                printDouble(data,matrix[i][j], setS);
                data<< " ";
            }
            data<< endl;
        }
      }
      else
      {
        cout<<"Error in loading file!"<< endl;
      }

    }

    else if (saveToFile=="no" || saveToFile=="No")
    {
        return 0;
    }
    //end of savetofile part
}
