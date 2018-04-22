/* 
 * Author: Vishisht, Deepak
 * Netids: vmt28 and da475
 * Copyright @ 2018 Vishisht and Deepak. All rights reserved

 * Created on April 18, 2018, 5:54 PM
 * File:   Assignment4_Header.h
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
#define EXCEPTION_HANDLING false    // Macro to enable exception handling

using namespace std;

// Global Variables
extern double rel_tolerance;
extern double abs_tolerance;

// Custom variable types used
// Vector saves time and delT in form of a vector
typedef struct
{
    double *arr;
    int dim;
} fullVect;

// Every matrix of values is saved as arrayMatCol
typedef struct 
{
    double *col;
    int rank;
} arrayMatCol;

// Saves the complete values. Comprises an array of arrayMatCol
typedef struct
{
    arrayMatCol **arr;
    int rank;
    int dim;
} arrayMat;

// FullMat used for vector multiplications
typedef struct
{
    double *arr;
    int rank;
} fullMat;

// This is a globally defined class whose functions are
// made public and can be used by any other code file
class Global_Functions
{
private:
public:
    
    // Function: Calculate_Norm
    // Calculates the norm of any arrayMatCol
    // Output: Double
    static double calculate_Norm(arrayMatCol *value) 
    {
        double sum;
        
        // Adds the square of every term
        for (int i = 0; i < value->rank; i++)
        {
            sum += value->col[i] * value->col[i];
            #if EXCEPTION_HANDLING
                if (isinf(sum)) throw IS_INF_NINF;
                if (isnan(sum)) throw IS_NAN;
            #endif
        }
        double output = sqrt(sum);
        #if EXCEPTION_HANDLING
            if (isinf(output)) throw IS_INF_NINF;
            if (isnan(output)) throw IS_NAN;
        #endif  
        return sqrt(sum);
    }
    
    // Function: Calculate_Error
    // Calculates the error between the true value and calculated value in percentage
    // Output: Double
    static double calculate_Error(double trueValue, double calculated) 
    {
        double output = 100 * abs(trueValue - calculated)/trueValue;
        #if EXCEPTION_HANDLING
            if (isinf(output)) throw IS_INF_NINF;
            if (isnan(output)) throw IS_NAN;
        #endif  
        return output;
    }
    
    // Function: Matrix_Vector_Product
    // Creates a MatCol using the matrix multiplication of matrix and MatCol
    // Output: arrayMatCol
    static void matrix_Vector_Product(fullMat *mat, arrayMatCol *col, arrayMatCol *result) 
    {
        if (mat->rank != col->rank) throw UNMATCHED_RANK;
        
        int rank = mat->rank;
        
        result->rank = rank;
        result->col = (double *)calloc(rank, sizeof(double));
        
        // Product of every term of matrix with the corresponding term in vector.
        // Value is saved in result
        for (int i = 0; i < rank; i++)
        {
            for (int j = 0; j < rank; j++)
            {
                result->col[i] += mat->arr[i * rank + j] * col->col[j];
                #if EXCEPTION_HANDLING
                    if (isinf(result->col[i])) throw IS_INF_NINF;
                    if (isnan(result->col[i])) throw IS_NAN;
                #endif  
            }
        }
    }
    
    // Function: Convert_Vector_FullMat
    // Converts vector of values to an arrayMatrix of values
    // Output: arrayMat
    static void convert_Vector_FullMat(vector<arrayMatCol*> *vect, arrayMat *mat) 
    {
        mat->dim = vect->size();
        mat->rank = (*vect)[0]->rank;
        mat->arr = new arrayMatCol*[mat->dim];
        
        for (int i = 0; i < mat->dim; i++)
        {
            mat->arr[i] = (*vect)[i];
            #if EXCEPTION_HANDLING
                if (isinf(mat->arr[i])) throw IS_INF_NINF;
                if (isnan(mat->arr[i])) throw IS_NAN;
            #endif
 
        }
    }
    
    // Function: Convert_Vector_Vector
    // Converts vector of values to a fullVect of values
    // Output: fullVect
    static void convert_Vector_Vector(vector<double> *vect1, fullVect *vect2)
    {
        vect2->dim = vect1->size();
        vect2->arr = (double *)calloc(vect2->dim, sizeof(double));
        
        for (int i = 0; i < vect2->dim; i++)
        {
            vect2->arr[i] = (*vect1)[i];
            #if EXCEPTION_HANDLING
                if (isinf(vect2->arr[i])) throw IS_INF_NINF;
                if (isnan(vect2->arr[i])) throw IS_NAN;
            #endif
        }
    }
    
    // Function: Create_FullMat
    // Converts create a fullMat from an array pointer
    // Output: fullMat
    static void create_FullMat(double *arr, fullMat *mat, int rank)
    {
        mat->arr = (double *)calloc(rank * rank, sizeof(double));
        mat->rank = rank;
        
        for (int i = 0; i < rank; i++)
        {
            for (int j = 0; j < rank; j++)
            {
                mat->arr[(i * rank) + j] = arr[(i * rank) + j];
                #if EXCEPTION_HANDLING
                    if (isinf(mat->arr[i])) throw IS_INF_NINF;
                    if (isnan(mat->arr[i])) throw IS_NAN;
                #endif  
            }
        }
    } 
    
    // Function: Create_Time_Values
    // Initializes the necessary time, delT vector and values matrix from start stop and step
    // Output: arrayMat, fullVect, fullVect
    static void create_Time_Values(double start, double stop, double step, int rank, arrayMat *values, fullVect *time, fullVect *delT)
    {        
        int dim = (stop - start)/step + 1;
        double currTime = start;
        
        values->arr = new arrayMatCol*[dim];
        
        // Declare and Initialize every new MatCol in arrayMat
        for (int i = 0; i < dim; i++)
        {
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
        
        // Initialize the time and delT
        for (int i = 0; i < dim; i++)
        {
            time->arr[i] = currTime;
            delT->arr[i] = step;
            currTime += step;
            #if EXCEPTION_HANDLING
                if (isinf(time->arr[i])) throw IS_INF_NINF;
                if (isnan(time->arr[i])) throw IS_NAN;
                if (isinf(delT->arr[i])) throw IS_INF_NINF;
                if (isnan(delT->arr[i])) throw IS_NAN;
            #endif  
        }
    }
    
    // Function: Create_Values
    // Initializes the values matrix according to time vector
    // Output: arrayMat
    static void create_Values(int rank, arrayMat *values, fullVect *time)
    {        
        int dim = time->dim;
        
        values->arr = new arrayMatCol*[dim];
        
        // Declare and Initialize every new MatCol in arrayMat
        for (int i = 0; i < dim; i++)
        {
            values->arr[i] = new arrayMatCol();
            values->arr[i]->rank = rank;
            values->arr[i]->col = (double *)calloc(rank, sizeof(double));
        }
        values->dim = dim;
        values->rank = rank;
    }
    
    // Function: Column_Scaling
    // Scale the MatCol with the scaling constant and outputs the new MatCol in result
    // Output: arrayMatCol
    static void column_Scaling(double scalingConst, arrayMatCol *mat, arrayMatCol *result)
    {
        int rank = mat->rank;
        result->rank = rank;
        result->col = (double *)calloc(rank, sizeof(double));
        
        // Multiply every term with scalingConst
        for (int i = 0; i < rank; i++)
        {
            result->col[i] = scalingConst * mat->col[i];
            #if EXCEPTION_HANDLING
                if (isinf(result->col[i])) throw IS_INF_NINF;
                if (isnan(result->col[i])) throw IS_NAN;
            #endif  
        }
    }
    
    // Function: Column_Shifting
    // Shifts the MatCol with the scaling constant and outputs the new MatCol in result
    // Output: arrayMatCol
    static void column_Shifting(double scalingConst, arrayMatCol *mat, arrayMatCol *result)
    {
        int rank = mat->rank;
        result->rank = rank;
        result->col = (double *)calloc(rank, sizeof(double));
        
        // Add every term with scalingConst
        for (int i = 0; i < rank; i++)
        {
            result->col[i] = scalingConst + mat->col[i];
            #if EXCEPTION_HANDLING
                if (isinf(result->col[i])) throw IS_INF_NINF;
                if (isnan(result->col[i])) throw IS_NAN;
            #endif  
        }
    }
    
    // Function: Column_Negative
    // Multiplies every term of MatCol with -1 and outputs the new MatCol in result
    // Output: arrayMatCol
    static void column_Negative(arrayMatCol *mat, arrayMatCol *result)
    {
        int rank = mat->rank;
        result->rank = rank;
        result->col = (double *)calloc(rank, sizeof(double));
        
        // Negate every term
        for (int i = 0; i < rank; i++)
        {
            result->col[i] = -mat->col[i];
            #if EXCEPTION_HANDLING
                if (isinf(result->col[i])) throw IS_INF_NINF;
                if (isnan(result->col[i])) throw IS_NAN;
            #endif  
        }
    }
    
    // Function: Column_Addition
    // Adds every element of two matcol and outputs the new MatCol in result
    // Output: arrayMatCol
    static void column_Addition(arrayMatCol *matX, arrayMatCol *matY, arrayMatCol *result) 
    {
        if (matX->rank != matY->rank) throw UNMATCHED_RANK;
        
        int rank = matX->rank;
        result->rank = rank;
        result->col = (double *)calloc(rank, sizeof(double));
        
        // Add every term in the two MatCol
        for (int i = 0; i < rank; i++)
        {
            result->col[i] = matX->col[i] + matY->col[i];
            #if EXCEPTION_HANDLING
                if (isinf(result->col[i])) throw IS_INF_NINF;
                if (isnan(result->col[i])) throw IS_NAN;
            #endif  
        }
    }
    
    // Function: Column_Exponential
    // Takes every term of MatCol and takes its exponential and outputs it in result MatCol
    // Output: arrayMatCol
    static void column_Exponential(arrayMatCol *mat, arrayMatCol *result) 
    {
        int rank = mat->rank;
        result->rank = rank;
        result->col = (double *)calloc(rank, sizeof(double));
        
        // Takes exponential of every term in MatCol
        for (int i = 0; i < rank; i++)
        {
            result->col[i] = exp(mat->col[i]);
            #if EXCEPTION_HANDLING
                if (isinf(result->col[i])) throw IS_INF_NINF;
                if (isnan(result->col[i])) throw IS_NAN;
            #endif  
        }
    }
    
    // Function: Print_Comparison
    // Prints the terms of values. If true Values are provided then it also calculates the error
    static void print_Comparison(fullVect *time, arrayMat *calValues, arrayMat *trueValues = NULL) 
    {
        if ((time->dim != calValues->dim) || (trueValues != NULL && (time->dim != trueValues->dim))) throw UNMATCHED_DIM;
        
        int dim = calValues->dim;
        if (trueValues != NULL)
        {
            cout << "Time\tTrue Values\tCalculated Values\tCalculated Error" << endl;
            cout << "----------------------------------------------------------------" << endl;
            for (int i = 0; i < dim; i++)
            {
                cout << time->arr[i] << "\t" <<
                        trueValues->arr[i]->col[0] << "\t\t" << 
                        calValues->arr[i]->col[0] << "\t\t\t" << 
                        calculate_Error(trueValues->arr[i]->col[0], calValues->arr[i]->col[0]) << "%" <<
                        endl;
                #if EXCEPTION_HANDLING
                    if (isinf(time->arr[i])) throw IS_INF_NINF;
                    if (isnan(time->arr[i])) throw IS_NAN;
                    if (isinf(trueValues->arr[i]->col[0])) throw IS_INF_NINF;
                    if (isnan(trueValues->arr[i]->col[0])) throw IS_NAN;
                    if (isinf(calValues->arr[i]->col[0])) throw IS_INF_NINF;
                    if (isnan(calValues->arr[i]->col[0])) throw IS_NAN;
                    if (isinf(calculate_Error(trueValues->arr[i]->col[0], calValues->arr[i]->col[0]))) throw IS_INF_NINF;
                    if (isnan(calculate_Error(trueValues->arr[i]->col[0], calValues->arr[i]->col[0]))) throw IS_NAN;
                #endif
            }
        }
        else {
            cout << "Time\t\t\tCalculated Values(V1)\t\tCalculated Values(V2)" << endl;
            cout << "-----------------------------------------------------------------------------------" << endl;
            for (int i = 0; i < dim; i++)
            {
                cout << time->arr[i] << "\t\t" <<
                        calValues->arr[i]->col[0] << "\t\t\t" << 
                        calValues->arr[i]->col[1] <<
                        endl;
                #if EXCEPTION_HANDLING
                    if (isinf(time->arr[i])) throw IS_INF_NINF;
                    if (isnan(time->arr[i])) throw IS_NAN;
                    if (isinf(trueValues->arr[i]->col[0])) throw IS_INF_NINF;
                    if (isnan(trueValues->arr[i]->col[0])) throw IS_NAN;
                    if (isinf(calValues->arr[i]->col[0])) throw IS_INF_NINF;
                    if (isnan(calValues->arr[i]->col[0])) throw IS_NAN;
                #endif
            }
        }
    }
    
    // Function: Matrix_Print
    // Prints the values of arrayMat. Used mostly for debugging
    static void matrix_Print(arrayMat *mat)
    {
        int dim = mat->dim;
        int rank = mat->rank;
        
        for (int i = 0; i < dim; i++)
        {
            for (int j = 0; j < rank - 1; j++)
            {
                cout << mat->arr[i]->col[j] << "\t\t";
                #if EXCEPTION_HANDLING
                    if (isinf(mat->arr[i]->col[j])) throw IS_INF_NINF;
                    if (isnan(mat->arr[i]->col[j])) throw IS_NAN;
                #endif
            }
            cout << endl;
        }        
    }
    
    // Function: Vector_Print
    // Prints the values of fullVect. Used mostly for debugging
    static void vector_Print(fullVect *vect)
    {
        int dim = vect->dim;
        
        for (int i = 0; i < dim; i++)
        {
            cout << vect->arr[i] << " ";
            #if EXCEPTION_HANDLING
                if (isinf(vect->arr[i])) throw IS_INF_NINF;
                if (isnan(vect->arr[i])) throw IS_NAN;
            #endif
        }
        cout << endl;      
    }
    
    // Function: Column_Print
    // Prints the values of arrayMatCol. Used mostly for debugging
    static void column_Print(arrayMatCol *col)
    {
        int rank = col->rank;
        
        for (int i = 0; i < rank; i++)
        {
            cout << col->col[i] << " ";
            #if EXCEPTION_HANDLING
                if (isinf(col->col[i])) throw IS_INF_NINF;
                if (isnan(col->col[i])) throw IS_NAN;
            #endif
        }
        cout << endl;     
    }
    
    // Function: FullMatrix_Print
    // Prints the values of fullMat. Used mostly for debugging
    static void fullMatrix_Print(fullMat *matrix) 
    {
        cout << endl;
        cout << "Matrix in full-format is" << endl;
        
        for (int i = 0; i < matrix->rank; i++)
        {
            for (int j = 0; j < matrix->rank; j++)
            {
                cout << matrix->arr[(i * matrix->rank) + j] << " ";
                #if EXCEPTION_HANDLING
                    if (isinf(matrix->arr[(i * matrix->rank) + j])) throw IS_INF_NINF;
                    if (isnan(matrix->arr[(i * matrix->rank) + j])) throw IS_NAN;
                #endif
            }
            cout << endl;
        }
    }
};

#endif /* ASSIGNMENT_4_HEADER_H */