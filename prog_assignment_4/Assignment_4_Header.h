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
extern double rel_tolerance;
extern double abs_tolerance;

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
    
    static double calculate_Norm(arrayMatCol *value) {
        double sum;
        for (int i = 0; i < value->rank; i++)
            sum += value->col[i] * value->col[i];
        
        return sqrt(sum);
    }
    
    static double calculate_Error(double trueValue, double calculated) {
        return 100 * (trueValue - calculated)/trueValue;
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
    
    static void convert_Vector_FullMat(vector<arrayMatCol*> *vect, arrayMat *mat) {
        mat->dim = vect->size();
        mat->rank = (*vect)[0]->rank;
        mat->arr = new arrayMatCol*[mat->dim];
        for (int i = 0; i < mat->dim; i++) {
            mat->arr[i] = (*vect)[i];
        }
    }
    
    static void convert_Vector_Vector(vector<double> *vect1, fullVect *vect2) {
        vect2->dim = vect1->size();
        vect2->arr = (double *)calloc(vect2->dim, sizeof(double));
        for (int i = 0; i < vect2->dim; i++) {
            vect2->arr[i] = (*vect1)[i];
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
    
    static void create_Values(int rank, arrayMat *values, fullVect *time)
    {        
        int dim = time->dim;
        
        values->arr = new arrayMatCol*[dim];
        for (int i = 0; i < dim; i++) {
            values->arr[i] = new arrayMatCol();
            values->arr[i]->rank = rank;
            values->arr[i]->col = (double *)calloc(rank, sizeof(double));
        }
        values->dim = dim;
        values->rank = rank;
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
    
    static void column_Exponential(arrayMatCol *mat, arrayMatCol *result) 
    {
        int rank = mat->rank;
        result->rank = rank;
        result->col = (double *)calloc(rank, sizeof(double));
        
        for (int i = 0; i < rank; i++)
            result->col[i] = exp(mat->col[i]);
    }
    
    
    
    static void print_Comparison(fullVect *time, arrayMat *calValues, arrayMat *trueValues = NULL) 
    {
        int dim = calValues->dim;
        
        if (trueValues != NULL) {
            cout << "Time\tTrue Values\tCalculated Values\tCalculated Error" << endl;
            for (int i = 0; i < dim; i++)
                cout << time->arr[i] << "\t" <<
                        trueValues->arr[i]->col[0] << "\t\t" << 
                        calValues->arr[i]->col[0] << "\t\t\t" << 
                        calculate_Error(trueValues->arr[i]->col[0], calValues->arr[i]->col[0]) << "%\t\t\t" << 
                        endl;
        }
        else {
            cout << "Time\tCalculated Values(V1)\tCalculated Values(V2)" << endl;
            for (int i = 0; i < dim; i++)
                cout << time->arr[i] << "\t" <<
                        calValues->arr[i]->col[0] << "\t\t\t\t" << 
                        calValues->arr[i]->col[1] << "\t\t\t\t" << 
                        endl;
        }
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