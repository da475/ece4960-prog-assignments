/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   full_Matrix_Solver.h
 * Author: Vishisht
 *
 * Created on April 4, 2018, 4:02 PM
 */

// Including all classes
#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <cstdlib>
#include <cmath>
#include <cfenv>
#include <string.h>
#include <fstream>

#ifndef FULL_MATRIX_SOLVER_H
#define FULL_MATRIX_SOLVER_H

// Defining constants
#define NO_ERROR 0
#define ERROR 1
#define UNMATCHED_RANK 2

using namespace std;

typedef struct {
    double *arr;
    int rank;
}full_Matrix;

typedef struct {
    double *arr;
    int rank;
}full_Vector;

typedef struct {
    int row;
    int col;
    double value;
}element;

class full_Matrix_Solver {
public:
    full_Matrix_Solver(full_Matrix *matrix, full_Vector *vector);
    int back_Substitution(full_Vector *answer);
    int l_U_Decomposition();
    virtual ~full_Matrix_Solver();
private:
    full_Matrix *matrix;
    full_Vector *vector;
    int rank;
    int row_Permeutation(int rowA, int rowB);
    int row_Scaling(int rowA, int rowB, double scallingConst);
    int partial_Row_Pivoting(element *ele);
    
    double determinant(full_Matrix *matrix);
    void convert_To_Smaller_Matrix(full_Matrix *matrix, full_Matrix *newMatrix, int col);
};

#endif /* FULL_MATRIX_SOLVER_H */

