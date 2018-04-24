#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>

using namespace std;

class Matrix
{
  private:
    int rows;
    int cols;
    int size;
    double** cell;
    double* solutions;
  public:
    double absv(double value);
    void emptyMatrix();
    void initMatrix(int, int);
    void printMatrix();
    void insertElement(int, int, double);
    void deleteArrays();
    void switchRows(int, int);
    int identifyPivot(int, int);
    int gaussElim();
    void solveSystem();
//    void printSolutions();
    int checkZeroRows(int);
};

#endif
