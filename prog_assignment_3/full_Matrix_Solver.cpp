/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   full_Matrix_Solver.cpp
 * Author: Vishisht
 * 
 * Created on April 4, 2018, 4:02 PM
 */

#include "full_Matrix_Solver.h"

double tolerance = pow(10,-12);

// Function to take a square matrix of rank N and return matrix of rank N-1
// This is helper function used to calculate the determinant
void full_Matrix_Solver::convert_To_Smaller_Matrix(full_Matrix *matrix, full_Matrix *newMatrix, int col) {
    if (col >= rank) throw ERROR;
    newMatrix->rank = matrix->rank - 1;
    newMatrix->arr = (double *)calloc(newMatrix->rank * newMatrix->rank, sizeof(double));
    int k = 0, l = 0;
    for (int i = 1; i < matrix->rank; i++) {
        l = 0;
        for (int j = 0; j < matrix->rank; j++) {
            if (j != col) {
                newMatrix->arr[(k * newMatrix->rank) + l] = matrix->arr[(i * matrix->rank) + j];
                l++;
            }
        }
        k++;
    }
    #if EXCEPTION_HANDLING
        for (int i = 0; i < newMatrix->rank; i++) {
            for (int j = 0; j < newMatrix->rank; j++) {
                if (isinf(matrix->arr[(i * newMatrix->rank) + j])) throw IS_INF_NINF;
                if (isnan(matrix->arr[(i * newMatrix->rank) + j])) throw IS_NAN;
            }
        }
    #endif  
}

// Function to calculate the determinant through recursion
double full_Matrix_Solver::determinant(full_Matrix *matrix) {
    if (matrix->rank == 2) return (matrix->arr[0] * matrix->arr[3]) - (matrix->arr[1] * matrix->arr[2]);
    bool sign = true;
    double value = 0;
    for (int i = 0; i < matrix->rank; i++) {
        full_Matrix *matrixTemp = new full_Matrix();
        full_Matrix_Solver::convert_To_Smaller_Matrix(matrix, matrixTemp, i);
        if (sign) {
            value += matrix->arr[i] * determinant(matrixTemp);      // recursive call to smaller matrix
        }
        else {
            value -= matrix->arr[i] * determinant(matrixTemp);      // recursive call to smaller matrix
        }     
        sign = !sign;       // keep toggling the sign at every iteration
    }
    if (isinf(value)) throw IS_INF_NINF;
    if (isnan(value)) throw IS_NAN;
    return value;
}

// Function to perform row-permutation between the two
// input rows rowA and rowB, also checks for exception handling
void full_Matrix_Solver::row_Permutation(int rowA, int rowB) {
    if ((rowA >= rank) || (rowB >= rank)) throw ERROR;
    if (matrix->rank != vector->rank) throw UNMATCHED_RANK;
    double temp = 0;
    for (int i = 0; i < rank; i++) {
        temp = matrix->arr[(rowA * rank) + i];
        matrix->arr[(rowA * rank) + i] = matrix->arr[(rowB * rank) + i];
        matrix->arr[(rowB * rank) + i] = temp;
    }
    temp = vector->arr[rowA];
    vector->arr[rowA] = vector->arr[rowB];
    vector->arr[rowB] = temp;
    
    #if EXCEPTION_HANDLING
        for (int i = 0; i < rank; i++) {
            if (isinf(matrix->arr[(rowA * rank) + i])) throw IS_INF_NINF;
            if (isnan(matrix->arr[(rowA * rank) + i])) throw IS_NAN;
            if (isinf(matrix->arr[(rowB * rank) + i])) throw IS_INF_NINF;
            if (isnan(matrix->arr[(rowB * rank) + i])) throw IS_NAN;
        }
        if (isinf(vector->arr[rowA])) throw IS_INF_NINF;
        if (isnan(vector->arr[rowB])) throw IS_NAN;
    #endif  
}

// Function to perform row scaling by taking the two rows
// and the scaling coefficient as the inputs
void full_Matrix_Solver::row_Scaling(int rowA, int rowB, double scalingConst) {
    if ((rowA >= rank) || (rowB >= rank)) throw ERROR;
    if (matrix->rank != vector->rank) throw UNMATCHED_RANK;
    for (int i = 0; i < rank; i++) matrix->arr[(rowB * rank) + i] += scalingConst * matrix->arr[(rowA * rank) + i];
    vector->arr[rowB] += scalingConst * vector->arr[rowA];
    
    #if EXCEPTION_HANDLING
        for (int i = 0; i < rank; i++) {
            if (isinf(matrix->arr[(rowA * rank) + i])) throw IS_INF_NINF;
            if (isnan(matrix->arr[(rowA * rank) + i])) throw IS_NAN;
            if (isinf(matrix->arr[(rowB * rank) + i])) throw IS_INF_NINF;
            if (isnan(matrix->arr[(rowB * rank) + i])) throw IS_NAN;
        }
        if (isinf(vector->arr[rowA])) throw IS_INF_NINF;
        if (isnan(vector->arr[rowB])) throw IS_NAN;
    #endif  
}

// Function to perform partial row pivoting
void full_Matrix_Solver::partial_Row_Pivoting(element *ele) {
    if ((ele->row >= rank) || (ele->col >= rank)) throw ERROR;
    if (matrix->rank != vector->rank) throw UNMATCHED_RANK;
    for (int i = ele->row + 1; i < rank; i++) {
        if (matrix->arr[(i * rank) + ele->col] != 0) {
            full_Matrix_Solver::row_Scaling(ele->row, i, -(matrix->arr[(i * rank) + ele->col]/ele->value));
        }
    }
}

// Function to perform L-U Decomposition
void full_Matrix_Solver::l_U_Decomposition() {
    if (matrix->rank != vector->rank) throw UNMATCHED_RANK;

    // Iterate over the diagonal elements
    for (int i = 0; i < rank; i++) {
        // if the diagonal element is zero, do row permutation with other rows
        if (matrix->arr[(i * rank) + i] == 0) {
            for (int j = 1; j < rank; j++) {
                if (matrix->arr[(j * rank) + i] != 0) {
                    full_Matrix_Solver::row_Permutation(i, j);
                    break;
                }
            }
        }
        // calculate the determinant before performing partial pivoting
        double before = full_Matrix_Solver::determinant(this->matrix);

        element *ele = new element();
        ele->col = i;
        ele->row = i;
        ele->value = matrix->arr[(i * rank) + i];
        
        full_Matrix_Solver::partial_Row_Pivoting(ele);

        // calculate the determinant after performing partial pivoting
        double after = full_Matrix_Solver::determinant(this->matrix);

        // check for tolerance limit and return error if crossed
        if (((abs(after - before))/abs(after)) > tolerance) throw ERROR;
        
    } 
    
    #if EXCEPTION_HANDLING
        for (int i = 0; i < rank; i++) {
            for (int j = 0; j < rank; j++) {
                if (isinf(matrix->arr[(i * rank) + j])) throw IS_INF_NINF;
                if (isnan(matrix->arr[(i * rank) + j])) throw IS_NAN;
            }
        }
    #endif  
    
}

// Function to perform Back-Substitution, populates the outputs
// in the input vector using the class members as inputs
void full_Matrix_Solver::back_Substitution(full_Vector *answer) {
    if (matrix->rank != answer->rank) throw UNMATCHED_RANK;
    if (answer->rank != vector->rank) throw UNMATCHED_RANK;
    
    double sum = 0;
    for (int i = rank - 1; i >= 0; i--) {
        sum = vector->arr[i];
        for (int j = 1; j < rank; j++) {
            sum -= matrix->arr[(i * rank) + ((i + j) % rank)] * answer->arr[(i + j) % rank];
        }
        answer->arr[i] = sum/matrix->arr[(i * rank) + i];
    }
    
    #if EXCEPTION_HANDLING
        for (int i = 0; i < rank; i++) {
            if (isinf(answer->arr[i])) throw IS_INF_NINF;
            if (isnan(answer->arr[i])) throw IS_NAN;
        }
    #endif  
}

// Constructor
full_Matrix_Solver::full_Matrix_Solver(full_Matrix *matrix, full_Vector *vector) {
    this->matrix = matrix;
    this->vector = vector;
    this->rank = matrix->rank;
}

// Destructor
full_Matrix_Solver::~full_Matrix_Solver() {
}

