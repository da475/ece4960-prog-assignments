/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   assignment_3_Header.h
 * Author: Vishisht
 *
 * Created on April 4, 2018, 6:24 PM
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
#include "full_Matrix_Solver.h"

#ifndef ASSIGNMENT_3_HEADER_H
#define ASSIGNMENT_3_HEADER_H

// Defining constants
#define NO_ERROR 0
#define ERROR 1
#define UNMATCHED_RANK 2

using namespace std;

class Global_Functions
{
private:
public:

    // Function: Create_Pointer_From_Matrix
    // Allocates a matrix dynamically of a given rank
    // and copies the elements to it from a given array
    // Input: array and rank
    // Output: Full-matrix
    static int Create_Pointer_From_Matrix(double *array, full_Matrix *fullMatrix, int rank) 
    {
        fullMatrix->rank = rank;

        // allocate the memory
        fullMatrix->arr = (double *)malloc(rank * rank * sizeof(double));

        for (int i = 0; i < fullMatrix->rank; i++) {
            for (int j = 0; j < fullMatrix->rank; j++) {
                fullMatrix->arr[(i * fullMatrix->rank) + j] = array[(i * fullMatrix->rank) + j];
                #if EXCEPTION_HANDLING
                    for (int i = 0; i < fullMatrix->rank; i++) {
                        for (int j = 0; j < fullMatrix->rank; j++) {
                            if (isinf(fullMatrix->arr[(i * fullMatrix->rank) + j])) return IS_INF_NINF;
                            if (isnan(fullMatrix->arr[(i * fullMatrix->rank) + j])) return IS_NAN;
                        }
                    }
                #endif  
            }
        }
        return NO_ERROR;
    }
    
    // Function: Create_Pointer_From_Vector
    // Allocates a vector dynamically of a given rank
    // and copies the elements to it from a given array
    // Input: array and rank
    // Output: Vector
    static int Create_Pointer_From_Vector(double *array, full_Vector *fullVector, int rank) 
    {
        fullVector->rank = rank;

        // allocate the memory
        fullVector->arr = (double *)malloc(rank * sizeof(double));

        for (int i = 0; i < fullVector->rank; i++) {
            fullVector->arr[i] = array[i];
            #if EXCEPTION_HANDLING
                for (int i = 0; i < fullVector->rank; i++) {
                    for (int j = 0; j < fullVector->rank; j++) {
                        if (isinf(fullVector->arr[i])) return IS_INF_NINF;
                        if (isnan(fullVector->arr[i])) return IS_NAN;
                    }
                }
            #endif  
        }
        return NO_ERROR;
    }
    
    // Function: printMatrixFull
    // Prints a full matrix
    // Input: Full Matrix
    // Output: 0 if successful
    static int printMatrixFull(full_Matrix *matrix) {
        cout << endl;
        cout << "Matrix in full-format is" << endl;
        
        for (int i = 0; i < matrix->rank; i++) {
            for (int j = 0; j < matrix->rank; j++) {
                #if EXCEPTION_HANDLING
                    for (int i = 0; i < matrix->rank; i++) {
                        for (int j = 0; j < matrix->rank; j++) {
                            if (isinf(matrix->arr[(i * matrix->rank) + j])) return IS_INF_NINF;
                            if (isnan(matrix->arr[(i * matrix->rank) + j])) return IS_NAN;
                        }
                    }
                #endif  
                cout << matrix->arr[(i * matrix->rank) + j] << " ";
            }
            cout << endl;
        }
        return NO_ERROR;
    }
    
    // Function: printVectorFull
    // Prints a full vector
    // Input: Full vector
    // Output: 0 if successful
    static int printVectorFull(full_Vector *vec) {
        cout << endl;
        cout << "Vector in full-format is" << endl;
        
        for (int i = 0; i < vec->rank; i++) {
            #if EXCEPTION_HANDLING
                for (int i = 0; i < vec->rank; i++) {
                    for (int j = 0; j < vec->rank; j++) {
                        if (isinf(vec->arr[j])) return IS_INF_NINF;
                        if (isnan(vec->arr[j])) return IS_NAN;
                    }
                }
            #endif  
            cout << vec->arr[i] << " ";
        }
        cout << endl;
        return NO_ERROR;
    }
};


#endif /* ASSIGNMENT_3_HEADER_H */

