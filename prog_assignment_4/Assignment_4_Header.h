/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Assignment_4_Header.h
 * Author: Vishisht
 *
 * Created on April 18, 2018, 5:54 PM
 */

#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <cstdlib>
#include <cmath>
#include <vector>

#ifndef ASSIGNMENT_4_HEADER_H
#define ASSIGNMENT_4_HEADER_H

// Defining constants
#define NO_ERROR 0
#define ERROR 1
#define UNMATCHED_RANK 2
#define UNMATCHED_DIM 3
#define IS_INF_NINF 4
#define IS_NAN 5

using namespace std;

// Global Variables
extern double tolerance;

typedef struct {
    double *arr;
    int dim;
} fullVect;

typedef struct {
    double *col;
    int rank;
} arrayMatCol;

typedef struct {
    arrayMatCol **arr;
    int rank;
    int dim;
} arrayMat;

typedef struct {
    double *arr;
    int rank;
} fullMat;

// This is a globally defined class whose functions are
// made public and can be used by any other code file
class Global_Functions
{
private:
public:
    
    static double error(double trueValue, double calculated) {
        return 100 * (trueValue - calculated)/trueValue;
    }
    
    static void print_Comparison(arrayMat *forEulerValues, arrayMat *rk34WoAdaptValues, arrayMat *trueValues = NULL) {
        if (forEulerValues->dim != rk34WoAdaptValues->dim || (trueValues != NULL && (rk34WoAdaptValues->dim != trueValues->dim))) throw UNMATCHED_DIM;
        
        int dim = forEulerValues->dim;
        
        if (trueValues != NULL) {
            cout << "True Values\tForward Euler Values\tForward Euler Error\tRK34 With Time Adapt Values\tRK34 With Time Adapt Error" << endl;
            for (int i = 0; i < dim; i++)
                cout << trueValues->arr[i]->col[0] << "\t\t" << 
                        forEulerValues->arr[i]->col[0] << "\t\t\t" << 
                        error(trueValues->arr[i]->col[0], forEulerValues->arr[i]->col[0]) << "%\t\t\t" << 
                        rk34WoAdaptValues->arr[i]->col[0] << "\t\t\t\t" <<
                        error(trueValues->arr[i]->col[0], rk34WoAdaptValues->arr[i]->col[0]) << "%" << 
                        endl;
        }
        else {
            cout << "Forward Euler Values(V1)\tForward Euler Values(V2)\tRK34 With Time Adapt Values(V1)\t\tRK34 With Time Adapt Values(V2)" << endl;
            for (int i = 0; i < dim; i++)
                cout << forEulerValues->arr[i]->col[0] << "\t\t\t\t" << 
                        forEulerValues->arr[i]->col[1] << "\t\t\t\t" << 
                        rk34WoAdaptValues->arr[i]->col[0] << "\t\t\t\t\t" <<
                        rk34WoAdaptValues->arr[i]->col[1] << 
                        endl;
        }
    }
    
    static void matrix_Vector_Product(fullMat *mat, arrayMatCol *col, arrayMatCol *result) {
        
        int rank = mat->rank;
        
        result->rank = rank;
        result->col = (double *)calloc(rank, sizeof(double));
        
        for (int i = 0; i < rank; i++) {
            for (int j = 0; j < rank; j++) {
                result->col[i] += mat->arr[i * rank + j] * col->col[j];
            }
        }
    }
    
    
    static void create_FullMat(double *arr, fullMat *mat, int rank)
    {
        mat->arr = (double *)calloc(rank * rank, sizeof(double));
        mat->rank = rank;
        for (int i = 0; i < rank; i++) {
            for (int j = 0; j < rank; j++)
                mat->arr[(i * rank) + j] = arr[(i * rank) + j];
        }
    } 
    
    static void create_Time_Values(double start, double stop, double step, int rank, arrayMat *values, fullVect *time, fullVect *delT)
    {        
        int dim = (stop - start)/step + 1;
        double currTime = start;
        
        values->arr = new arrayMatCol*[dim];
        for (int i = 0; i < dim; i++) {
            values->arr[i] = new arrayMatCol();
            values->arr[i]->rank = rank;
            values->arr[i]->col = (double *)calloc(rank, sizeof(double));
        }
        values->dim = dim;
        values->rank = rank;
        
        time->arr = (double *)calloc(dim, sizeof(double));
        time->dim = dim;
        
        delT->arr = (double *)calloc(dim, sizeof(double));
        delT->dim = dim;
        
        for (int i = 0; i < dim; i++) {
            time->arr[i] = currTime;
            delT->arr[i] = step;
            currTime += step;
        }
    }
    
    static void column_Scaling(double scalingConst, arrayMatCol *mat, arrayMatCol *result)
    {
        int rank = mat->rank;
        result->rank = rank;
        result->col = (double *)calloc(rank, sizeof(double));
        
        for (int i = 0; i < rank; i++)
            result->col[i] = scalingConst * mat->col[i];
    }
    
    static void column_Shifting(double scalingConst, arrayMatCol *mat, arrayMatCol *result)
    {
        int rank = mat->rank;
        result->rank = rank;
        result->col = (double *)calloc(rank, sizeof(double));
        
        for (int i = 0; i < rank; i++)
            result->col[i] = scalingConst + mat->col[i];
    }
    
    static void column_Negative(arrayMatCol *mat, arrayMatCol *result)
    {
        int rank = mat->rank;
        result->rank = rank;
        result->col = (double *)calloc(rank, sizeof(double));
        
        for (int i = 0; i < rank; i++)
            result->col[i] = -mat->col[i];
    }
    
    static void column_Addition(arrayMatCol *matX, arrayMatCol *matY, arrayMatCol *result) 
    {
        if (matX->rank != matY->rank) throw UNMATCHED_RANK;
        
        int rank = matX->rank;
        result->rank = rank;
        result->col = (double *)calloc(rank, sizeof(double));
        
        for (int i = 0; i < rank; i++)
            result->col[i] = matX->col[i] + matY->col[i];
    }
    
    static void column_Subtraction(arrayMatCol *matX, arrayMatCol *matY, arrayMatCol *result) 
    {
        if (matX->rank != matY->rank) throw UNMATCHED_RANK;
        
        int rank = matX->rank;
        result->rank = rank;
        result->col = (double *)calloc(rank, sizeof(double));
        
        for (int i = 0; i < rank; i++)
            result->col[i] = matX->col[i] - matY->col[i];
    }
    
    static void column_Multiply(arrayMatCol *matX, arrayMatCol *matY, arrayMatCol *result) 
    {
        if (matX->rank != matY->rank) throw UNMATCHED_RANK;
        
        int rank = matX->rank;
        result->rank = rank;
        result->col = (double *)calloc(rank, sizeof(double));
        
        for (int i = 0; i < rank; i++)
            result->col[i] = matX->col[i] * matY->col[i];
    }
    
    static void column_Exponential(arrayMatCol *mat, arrayMatCol *result) 
    {
        int rank = mat->rank;
        result->rank = rank;
        result->col = (double *)calloc(rank, sizeof(double));
        
        for (int i = 0; i < rank; i++)
            result->col[i] = exp(mat->col[i]);
    }
    
    
    
    
    
    
    
    
    static void matrix_Print(arrayMat *mat)
    {
        int dim = mat->dim;
        int rank = mat->rank;
        
        for (int i = 0; i < dim; i++) {
            for (int j = 0; j < rank - 1; j++)
                cout << mat->arr[i]->col[j] << "\t\t";
            cout << endl;
        }        
    }
    
    static void vector_Print(fullVect *vect)
    {
        int dim = vect->dim;
        
        for (int i = 0; i < dim; i++)
            cout << vect->arr[i] << " ";
        cout << endl;      
    }
    
    static void column_Print(arrayMatCol *col)
    {
        int rank = col->rank;
        
        for (int i = 0; i < rank; i++)
            cout << col->col[i] << " ";
        cout << endl;     
    }
    
    static int fullMatrix_Print(fullMat *matrix) {
        cout << endl;
        cout << "Matrix in full-format is" << endl;
        
        for (int i = 0; i < matrix->rank; i++) {
            for (int j = 0; j < matrix->rank; j++) 
                cout << matrix->arr[(i * matrix->rank) + j] << " ";
            cout << endl;
        }
        return NO_ERROR;
    }
    
};

#endif /* ASSIGNMENT_4_HEADER_H */