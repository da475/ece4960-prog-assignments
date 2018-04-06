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

#include "assignment_3_Header.h"

#ifndef FULL_MATRIX_SOLVER_H
#define FULL_MATRIX_SOLVER_H

class full_Matrix_Solver {
public:
    full_Matrix_Solver(full_Matrix *matrix, full_Vector *vector);
    void back_Substitution(full_Vector *answer);
    void l_U_Decomposition();
    virtual ~full_Matrix_Solver();
private:
    full_Matrix *matrix;
    full_Vector *vector;
    int rank;
    void row_Permeutation(int rowA, int rowB);
    void row_Scaling(int rowA, int rowB, double scallingConst);
    void partial_Row_Pivoting(element *ele);
    
    double determinant(full_Matrix *matrix);
    void convert_To_Smaller_Matrix(full_Matrix *matrix, full_Matrix *newMatrix, int col);
};

#endif /* FULL_MATRIX_SOLVER_H */

