/* 
 * Author: Vishisht, Deepak
 * Netids: vmt28 and da475
 * Copyright @ 2018 Vishisht and Deepak. All rights reserved

 * Created on March 4, 2018, 8:23 PM
 * File:   Assignment2_Header.h
 * Desc: Main header file defining a class of global functions 
         and declaring other classes
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

#ifndef ASSIGNMENT2_HEADER_H
#define ASSIGNMENT2_HEADER_H

// Defining constants
#define NO_ERROR 0
#define UNMATCHED_RANK 1
#define IS_INF_NINF 2
#define IS_NAN 3
#define ERROR 4
#define UNMATCHED_NZ 5
#define EXCEPTION_HANDLING false    // Macro to enable exception handling

using namespace std;

// Global Variables
extern double tolerance;

typedef struct {
    double *arr;
    int rank;
}full_Matrix;

typedef struct {
    double *value;
    int *rowPtr;
    int *colInd;
    int rank;
    int nZ;
}sparse_Matrix;

typedef struct {
    double *arr;
    int rank;
}full_Vector;

/* Class: Global_Functions
Description: Class of statically defined generic functions which
            can be used by any other class.
*/
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
    
    // Function: Create_Full_Matrix
    // Allocates a matrix dynamically of the same rank as sparse matrix
    // and copies the elements from row-compressed matrix to full matrix
    // Input: Row-compressed Matrix
    // Output: Full Matrix
    static int Create_Full_Matrix(full_Matrix *fullMatrix, sparse_Matrix *sparseMatrix) 
    {
        // allocate the memory
        fullMatrix->arr = (double *)malloc(sparseMatrix->rank * sparseMatrix->rank * sizeof(double));
        fullMatrix->rank = sparseMatrix->rank;
        
        for (int i = 0; i < sparseMatrix->rank; i++) {
            int counter = 0;
            for (int j = sparseMatrix->rowPtr[i]; j < sparseMatrix->rowPtr[i+1]; j++) {
                
                if (sparseMatrix->colInd[j] == counter) {
                    fullMatrix->arr[(i * sparseMatrix->rank) + counter] = sparseMatrix->value[j];
                    #if EXCEPTION_HANDLING
                        for (int i = 0; i < fullMatrix->rank; i++) {
                            for (int j = 0; j < fullMatrix->rank; j++) {
                                if (isinf(fullMatrix->arr[(i * sparseMatrix->rank) + counter])) return IS_INF_NINF;
                                if (isnan(fullMatrix->arr[(i * sparseMatrix->rank) + counter])) return IS_NAN;
                            }
                        }
                    #endif  
                }
                else {
                    fullMatrix->arr[(i * sparseMatrix->rank) + counter] = 0;
                    j--;
                }
                if (counter > fullMatrix->rank) j++;
                counter++;
            }
            for (int j = counter; j < sparseMatrix->rank; j++) {
                fullMatrix->arr[(i * sparseMatrix->rank) + j] = 0;
            }
        }
        return NO_ERROR;
    }
    
    // Function: Create_Row_Compressed_Matrix
    // Allocates a matrix dynamically of the same rank as full-matrix
    // and copies the elements from input full matrix in row-compressed format
    // Input: Full Matrix
    // Output: Sparse Matrix
    static int Create_Row_Compressed_Matrix(full_Matrix *fullMatrix, sparse_Matrix *sparseMatrix) 
    {
        int nZ = 0;
        for (int i = 0; i < fullMatrix->rank; i++) {
            for (int j = 0; j < fullMatrix->rank; j++) {
                if (fullMatrix->arr[(i * fullMatrix->rank) + j] != 0) nZ++;
            }
        }
        
        sparseMatrix->value = (double *)malloc(nZ * sizeof(double));
        sparseMatrix->rowPtr = (int *)malloc((fullMatrix->rank + 1) * sizeof(int));
        sparseMatrix->colInd = (int *)malloc(nZ * sizeof(int));
        sparseMatrix->nZ = nZ;
        sparseMatrix->rank = fullMatrix->rank;
        
        sparseMatrix->rowPtr[0] = 0;
        
        int countNZRow = 0;
        
        for (int i = 0; i < fullMatrix->rank; i++) {
            for (int j = 0; j < fullMatrix->rank; j++) {
                if (fullMatrix->arr[(i * fullMatrix->rank) + j] != 0) {
                    sparseMatrix->value[countNZRow] = fullMatrix->arr[(i * fullMatrix->rank) + j];
                    #if EXCEPTION_HANDLING
                        for (int i = 0; i < fullMatrix->rank; i++) {
                            for (int j = 0; j < fullMatrix->rank; j++) {
                                if (isinf(sparseMatrix->value[countNZRow])) return IS_INF_NINF;
                                if (isnan(sparseMatrix->value[countNZRow])) return IS_NAN;
                            }
                        }
                    #endif  
                    sparseMatrix->colInd[countNZRow] = j;
                    countNZRow++;
                }
            }
            sparseMatrix->rowPtr[i+1] = countNZRow;
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
    
    // Function: printMatrixSparse
    // Prints a sparse matrix
    // Input: Row-compressed Matrix
    // Output: 0 if successful
    static int printMatrixSparse(sparse_Matrix *matrix) {
        cout << endl;
        cout << "Matrix in row-format is" << endl;
        
        for (int i = 0; i <= matrix->rank; i++) {
            for (int j = matrix->rowPtr[i]; j < matrix->rowPtr[i+1]; j++) {
                #if EXCEPTION_HANDLING
                    for (int i = 0; i < matrix->rank; i++) {
                        for (int j = 0; j < matrix->rank; j++) {
                            if (isinf(matrix->value[j])) return IS_INF_NINF;
                            if (isnan(matrix->value[j])) return IS_NAN;
                        }
                    }
                #endif  
                cout << matrix->value[j] << " ";
            }
            cout << endl;
        }
        cout << endl;
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
    
    // Function: norm_Full_Sparse_Matrix
    // Calculates the norm between a full matrix and row-compressed matrix
    // and compares it to a given tolerance value
    // Input: Full matrix and row-compressed matrix
    // Output: ERROR if norm is greater than given tolerance, otherwise NO_ERROR
    static int norm_Full_Sparse_Matrix(full_Matrix *fullMatrix, sparse_Matrix *sparseMatrix) {

        // compare the ranks of the two matrix
        if (fullMatrix->rank != sparseMatrix->rank) return UNMATCHED_RANK;

        // calculate non-zero elements        
        int nZ = 0;
        for (int i = 0; i < fullMatrix->rank; i++) {
            for (int j = 0; j < fullMatrix->rank; j++) {
                if (fullMatrix->arr[(i * fullMatrix->rank) + j] != 0) {
                    nZ++;
                }
            }
        }
        if (nZ != sparseMatrix->nZ) return UNMATCHED_NZ;
        
        long double norm = 0;
        for (int i = 0; i < fullMatrix->rank; i++) {
            for (int j = sparseMatrix->rowPtr[i]; j < sparseMatrix->rowPtr[i + 1]; j++) {
                norm += ((fullMatrix->arr[(i * fullMatrix->rank) + sparseMatrix->colInd[j]] * fullMatrix->arr[(i * fullMatrix->rank) + sparseMatrix->colInd[j]])
                        - (sparseMatrix->value[j] * sparseMatrix->value[j]));
                #if EXCEPTION_HANDLING
                    for (int i = 0; i < fullMatrix->rank; i++) {
                        for (int j = 0; j < fullMatrix->rank; j++) {
                            if (isinf(norm)) return IS_INF_NINF;
                            if (isnan(norm)) return IS_NAN;
                        }
                    }
                #endif
            }
        }

        if (norm < 0) norm = -norm;
        if (norm < tolerance) return NO_ERROR;
        else return ERROR;
    }
    
    // Function: norm_Matrix_Matrix
    // Calculates the norm between two full matrices
    // and compares it to a given tolerance value
    // Input: Two full matrices
    // Output: ERROR if norm is greater than given tolerance, otherwise NO_ERROR
    static int norm_Matrix_Matrix(full_Matrix *fullMatrix1, full_Matrix *fullMatrix2) {
        if (fullMatrix1->rank != fullMatrix2->rank) return UNMATCHED_RANK;

        long double norm = 0;
        for (int i = 0; i < fullMatrix1->rank; i++) {
            for (int j = 0; j < fullMatrix1->rank; j++) {
                norm += ((fullMatrix1->arr[(i * fullMatrix1->rank) + j]
                        * fullMatrix1->arr[(i * fullMatrix1->rank) + j])
                        - (fullMatrix2->arr[(i * fullMatrix2->rank) + j]
                        * fullMatrix2->arr[(i * fullMatrix2->rank) + j]));
                #if EXCEPTION_HANDLING
                    for (int i = 0; i < fullMatrix1->rank; i++) {
                        for (int j = 0; j < fullMatrix2->rank; j++) {
                            if (isinf(norm)) return IS_INF_NINF;
                            if (isnan(norm)) return IS_NAN;
                        }
                    }
                #endif
            }
        }
        if (norm < 0) norm = -norm;
        if (norm < tolerance) return NO_ERROR;
        else return ERROR;
    }
    
    // Function: norm_Vector_Vector
    // Calculates the norm between two full vecrors
    // and compares it to a given tolerance value
    // Input: Two vectors
    // Output: ERROR if norm is greater than given tolerance, otherwise NO_ERROR
    static int norm_Vector_Vector(full_Vector *fullVector1, full_Vector *fullVector2) {
        if (fullVector1->rank != fullVector2->rank) return UNMATCHED_RANK;
 
        long double norm = 0;
        for (int i = 0; i < fullVector1->rank; i++) {
            norm += ((fullVector1->arr[i] - fullVector2->arr[i]) *
                    (fullVector1->arr[i] - fullVector2->arr[i]));
            #if EXCEPTION_HANDLING
                for (int i = 0; i < fullVector1->rank; i++) {
                    for (int j = 0; j < fullVector2->rank; j++) {
                        if (isinf(norm)) return IS_INF_NINF;
                        if (isnan(norm)) return IS_NAN;
                    }
                }
            #endif
        }
       
        if (norm < tolerance) return NO_ERROR;
        else return ERROR;
    }
    
    static long double difference_Using_Norm_Vector_Vector(full_Vector *fullVector1, full_Vector *fullVector2) {
        if (fullVector1->rank != fullVector2->rank) return -1;
 
        long double norm = 0;
        for (int i = 0; i < fullVector1->rank; i++) {
            norm += ((fullVector1->arr[i] - fullVector2->arr[i]) *
                    (fullVector1->arr[i] - fullVector2->arr[i]));
        }
        return norm;
    }
    
    static long double normalized_Residual_Norm_Full_Matrix(full_Matrix *A, full_Vector *x, full_Vector *b, full_Vector *newB) {
        
        long double numerator = 0;
        long double denominator = 0;
        
        for (int i = 0; i < x->rank; i++) {
            numerator += ((b->arr[i] - newB->arr[i]) * (b->arr[i] - newB->arr[i]));
            denominator += b->arr[i] * b->arr[i];
        }
        return (sqrt(numerator)/sqrt(denominator));
    }
    
    static long double normalized_Residual_Norm_Sparse_Matrix(sparse_Matrix *A, full_Vector *x, full_Vector *b, full_Vector *newB) {
        
        long double numerator = 0;
        long double denominator = 0;
        
        for (int i = 0; i < x->rank; i++) {
            numerator += ((b->arr[i] - newB->arr[i]) * (b->arr[i] - newB->arr[i]));
            denominator += b->arr[i] * b->arr[i];
        }
        return (sqrt(numerator)/sqrt(denominator));
    }
    
    // Function for checking exceptions or signed zero
    static string Check_For_Exceptions_Zeros(double x) {
        if (x > numeric_limits<double>::max() && x > 0) return "Positive Infinity";
        if (x < -numeric_limits<double>::max() && x < 0) return "Negative Infinity";
        if (x != x) return "NAN";
        if (x == 0.0 && !signbit(x)) return "Positive Zero";
        if (x == 0.0 && signbit(x)) return "Negative Zero";
        // If none of the other exceptions occurred then return the string
        return (to_string(x) + " which is neither an exception nor signed zero");
    }
};

/* Class: Matrix_Operations
Description: Class to implement permute, scaling and multiply
            operations on full and row-compressed matrices.
*/
class Matrix_Operations {
private:
public:

    // Function to do row-permutation operation in full matrix format
    int rowPermuteFull(full_Matrix *matrix,  int rowPermuteTo, int rowPermuteFrom);


    // Function to do row-permutation operation in sparse matrix format
    int rowPermuteSparse(sparse_Matrix *matrix,  int rowPermuteTo, int rowPermuteFrom);


    // Function to do row-scaling operation in full matrix format
    int rowScaleFull(full_Matrix *matrix,  int rowScaledTo, int rowScaledFrom, double sFactor);


    // Function to do row-scaling operation in sparse matrix format
    int rowScaleSparse(sparse_Matrix *matrix,  int rowScaledTo, int rowScaledFrom, double sFactor);


    // Function to do product operation in full matrix format
    int productAxFull(full_Matrix *A, full_Vector *x, full_Vector *b);


    // Function to do product operation in sparse matrix format
    int productAxSparse(sparse_Matrix *A, full_Vector *x, full_Vector *b);

};

/* Class: Jacobi
Description: Class to implement iterative solver Jacobi
            on full and row-compressed matrices.
*/
class Jacobi
{
private:
    full_Matrix *A;
    full_Vector *x;
    full_Vector *b;
    
    sparse_Matrix *ASparse;
public:
    Jacobi(full_Matrix *A, full_Vector *b, full_Vector *x);
    Jacobi(sparse_Matrix *ASparse, full_Vector *b, full_Vector *x);
    ~Jacobi();
    
    void Initializing_Matrix();

    // Implement Jacobi method on full-matrix
    void Full_Matrix_Jacobi_Implementation();

    // Implement Jacobi method on row-compressed matrix
    void Row_Compressed_Jacobi_Implementation();
};

/* Class: Load_Mat1
Description: Class to implement functions to load row, column and value data
            from a .csv file and generate a row-compressed matrix using them.
*/
class Load_Mat1
{
private:
    sparse_Matrix *matrix;
public:
    Load_Mat1();
    ~Load_Mat1();
    
    void find_Number_Of_NonZero_Elements();
    void find_Rank();

    // Functions to load the csv files in an array    
    void load_ColInd();
    void load_RowPtr();
    void load_Value();
    
    int get_Number_Of_NonZero_Elements();
    int get_Rank();
    
    int* get_ColInd();
    int* get_RowPtr();
    double* get_Value();
    sparse_Matrix* get_Sparse_Matrix();
};

#endif /* ASSIGNMENT2_HEADER_H */
