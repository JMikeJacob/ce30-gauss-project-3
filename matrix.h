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
  public:
    void emptyMatrix();
    void initMatrix(int, int);
    void printMatrix();
    void insertElement(int, int, double);
    void deleteArrays();
    void switchRows(int, int);
};

#endif
