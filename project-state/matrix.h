#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class Matrix
{
  private:
    int rows, origRows;
    int cols, origCols;
    double** origMatrix;
    double** cell;
    double* solutions;
  public:
    bool displaySteps;
    double absv(double value);
    void initMatrix(int, int);
    void printMatrix();
    void insertElement(int, int, double);
    void deleteArrays();
    void switchRows(int, int);
    int identifyPivot(int, int);
    int gaussElim();
    void solveSystem();
    int readFromFile(string);
    int saveToFile(int);
    int checkZeroRows(int);
};

#endif
