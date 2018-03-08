/* 
 * File:   Assignment2_Header.h
 * Author: Vishisht, Deepak
 *
 * Created on March 4, 2018, 8:23 PM
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
#define EXCEPTION_HANDLING false

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

// Global Functions
class Global_Functions
{
private:
public:
    static int Create_Pointer_From_Matrix(double *array, full_Matrix *fullMatrix, int rank) {
        fullMatrix->rank = rank;
        fullMatrix->arr = (double *)malloc(rank * rank * sizeof(double));

        for (int i = 0; i < fullMatrix->rank; i++) {
            for (int j = 0; j < fullMatrix->rank; j++) {
                fullMatrix->arr[(i * fullMatrix->rank) + j] = array[(i * fullMatrix->rank) + j];
            }
        }
        return 0;
    }
    
    static int Create_Pointer_From_Vector(double *array, full_Vector *fullVector, int rank) {
        fullVector->rank = rank;
        fullVector->arr = (double *)malloc(rank * sizeof(double));

        for (int i = 0; i < fullVector->rank; i++) {
            fullVector->arr[i] = array[i];
        }
        return 0;
    }
    
    static void Create_Full_Matrix(full_Matrix *fullMatrix, sparse_Matrix *sparseMatrix) {
        fullMatrix->arr = (double *)malloc(sparseMatrix->rank * sparseMatrix->rank * sizeof(double));
        fullMatrix->rank = sparseMatrix->rank;
        
        for (int i = 0; i < sparseMatrix->rank; i++) {
            int counter = 0;
            for (int j = sparseMatrix->rowPtr[i]; j < sparseMatrix->rowPtr[i+1]; j++) {
                
                if (sparseMatrix->colInd[j] == counter) {
                    fullMatrix->arr[(i * sparseMatrix->rank) + counter] = sparseMatrix->value[j];
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
        
    }
    
    static void Create_Row_Compressed_Matrix(full_Matrix *fullMatrix, sparse_Matrix *sparseMatrix) 
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
                    sparseMatrix->colInd[countNZRow] = j;
                    countNZRow++;
                }
            }
            sparseMatrix->rowPtr[i+1] = countNZRow;
        }
    }
    
    // Function to print a matrix in full-compressed format
    static void printMatrixFull(full_Matrix *matrix) {
        cout << endl;
        cout << "Matrix in full-format is" << endl;
        
        for (int i = 0; i < matrix->rank; i++) {
            for (int j = 0; j < matrix->rank; j++) {
                cout << matrix->arr[(i * matrix->rank) + j] << " ";
            }
            cout << endl;
        }
        return;
    }
    
    // Function to print a matrix in row-compressed format
    static void printMatrixSparse(sparse_Matrix *matrix) {
        cout << endl;
        cout << "Matrix in row-format is" << endl;
        
        for (int i = 0; i <= matrix->rank; i++) {
            for (int j = matrix->rowPtr[i]; j < matrix->rowPtr[i+1]; j++) {
                cout << matrix->value[j] << " ";
            }
            cout << endl;
        }
        cout << endl;
        return;
    }
    
    // Function to print a matrix in full-compressed format
    static void printVectorFull(full_Vector *vec) {
        cout << endl;
        cout << "Vector in full-format is" << endl;
        
        for (int i = 0; i < vec->rank; i++) {
            cout << vec->arr[i] << " ";
        }
        cout << endl;
        return;
    }
    
    static int norm_Full_Sparse_Matrix(full_Matrix *fullMatrix, sparse_Matrix *sparseMatrix) {
        if (fullMatrix->rank != sparseMatrix->rank) return 1;
        
        
        int nZ = 0;
        for (int i = 0; i < fullMatrix->rank; i++) {
            for (int j = 0; j < fullMatrix->rank; j++) {
                if (fullMatrix->arr[(i * fullMatrix->rank) + j] != 0) {
                    nZ++;
                }
            }
        }
        if (nZ != sparseMatrix->nZ) return 1;
        
        long double norm = 0;
        for (int i = 0; i < fullMatrix->rank; i++) {
            for (int j = sparseMatrix->rowPtr[i]; j < sparseMatrix->rowPtr[i + 1]; j++) {
                norm += ((fullMatrix->arr[(i * fullMatrix->rank) + sparseMatrix->colInd[j]] * fullMatrix->arr[(i * fullMatrix->rank) + sparseMatrix->colInd[j]])
                        - (sparseMatrix->value[j] * sparseMatrix->value[j]));
            }
        }

        if (norm < 0) norm = -norm;
        if (norm < tolerance) return 0;
        else return 1;
    }
    
    static int norm_Matrix_Matrix(full_Matrix *fullMatrix1, full_Matrix *fullMatrix2) {
        if (fullMatrix1->rank != fullMatrix2->rank) return 1;

        long double norm = 0;
        for (int i = 0; i < fullMatrix1->rank; i++) {
            for (int j = 0; j < fullMatrix1->rank; j++) {
                norm += ((fullMatrix1->arr[(i * fullMatrix1->rank) + j]
                        * fullMatrix1->arr[(i * fullMatrix1->rank) + j])
                        - (fullMatrix2->arr[(i * fullMatrix2->rank) + j]
                        * fullMatrix2->arr[(i * fullMatrix2->rank) + j]));
            }
        }
        if (norm < 0) norm = -norm;
        if (norm < tolerance) return 0;
        else return 1;
    }
    
    static int norm_Vector_Vector(full_Vector *fullVector1, full_Vector *fullVector2) {
        if (fullVector1->rank != fullVector2->rank) return 1;
 
        long double norm = 0;
        for (int i = 0; i < fullVector1->rank; i++) {
            for (int j = 0; j < fullVector1->rank; j++) {
                norm += ((fullVector1->arr[(i * fullVector1->rank) + j]
                        * fullVector1->arr[(i * fullVector1->rank) + j])
                        - (fullVector2->arr[(i * fullVector2->rank) + j]
                        * fullVector2->arr[(i * fullVector2->rank) + j]));
            }
        }
       
        cout << norm;
        if (norm < 0) norm = -norm;
        if (norm < tolerance) return 0;
        else return 1;
    }
    
    static long double difference_Using_Norm_Vector_Vector(full_Vector *fullVector1, full_Vector *fullVector2) {
        if (fullVector1->rank != fullVector2->rank) return -1;
 
        long double norm = 0;
        for (int i = 0; i < fullVector1->rank; i++) {
            for (int j = 0; j < fullVector1->rank; j++) {
                norm += ((fullVector1->arr[(i * fullVector1->rank) + j]
                        * fullVector1->arr[(i * fullVector1->rank) + j])
                        - (fullVector2->arr[(i * fullVector2->rank) + j]
                        * fullVector2->arr[(i * fullVector2->rank) + j]));
            }
        }
        return norm;
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
    void Full_Matrix_Jacobi_Implementation();
    void Row_Compressed_Jacobi_Implementation();
};

class Load_Mat1
{
private:
    sparse_Matrix *matrix;
public:
    Load_Mat1();
    ~Load_Mat1();
    
    void find_Number_Of_NonZero_Elements();
    void find_Rank();
    
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