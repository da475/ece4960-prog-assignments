/* 
 * File:   Matrix_Operations.cpp
 * Author: Vishisht, Deepak
 *
 * Created on March 6, 2018, 7:17 PM
 */

// include the class header file
#include "Assignment2_Header.h"

double tolerance = pow(10,-7);

// Function to do row-permutation operation in full matrix format
// Input arguments: row rowPermuteTo and row rowPermuteFrom (matrix is part of private member of the class)
// Note: row index starts from 0
int Matrix_Operations::rowPermuteFull(full_Matrix *matrix,  int rowPermuteTo, int rowPermuteFrom) {
    cout << endl;
    rowPermuteTo--;
    rowPermuteFrom--;
    int temp;
    // swap the elements
    for (int i = 0; i < matrix->rank; i++) {
        temp = matrix->arr[(rowPermuteTo * matrix->rank) + i];
        matrix->arr[(rowPermuteTo * matrix->rank) + i] = matrix->arr[(rowPermuteFrom * matrix->rank) + i];
        matrix->arr[(rowPermuteFrom * matrix->rank) + i] = temp;
    }
    #if EXCEPTION_HANDLING
        cout << "Exception Checking is Being Executed" << endl;
        for (int i = 0; i < matrix->rank; i++) {
            for (int j = 0; j < matrix->rank; j++) {
                if (isinf(matrix->arr[(i * matrix->rank) + j])) return IS_INF_NINF;
                if (isnan(matrix->arr[(i * matrix->rank) + j])) return IS_NAN;
            }
        }
    #endif

    cout << endl;
    cout << "Permutation performed in full-format between " << rowPermuteTo+1 << " " << rowPermuteFrom+1 << endl << endl;
    cout << endl;
    
    return NO_ERROR;
}

// Function to do row-permutation operation in sparse matrix format
// Input arguments: row i and row rowPermuteFrom (matrix is part of private member of the class)
int Matrix_Operations::rowPermuteSparse(sparse_Matrix *matrix,  int rowPermuteTo, int rowPermuteFrom) {

    int nZSizeOfFirst = matrix->rowPtr[rowPermuteTo] - matrix->rowPtr[rowPermuteTo-1];
    int nZSizeOfSecond = matrix->rowPtr[rowPermuteFrom] - matrix->rowPtr[rowPermuteFrom-1];


    int tempFirstArrayValue[nZSizeOfFirst];
    int tempSecondArrayValue[nZSizeOfSecond];
    int tempFirstArrayColInd[nZSizeOfFirst];
    int tempSecondArrayColInd[nZSizeOfSecond];

    int counter = 0;

    // Copy the value and col for first row in a temp array
    for (int i = matrix->rowPtr[rowPermuteTo-1]; i < matrix->rowPtr[rowPermuteTo]; i++) {
        tempFirstArrayValue[counter] = matrix->value[i];
        tempFirstArrayColInd[counter] = matrix->colInd[i];
        counter++;
    }

    counter = 0;

    // Copy the value and col for second row in a temp array
    for (int i = matrix->rowPtr[rowPermuteFrom-1]; i < matrix->rowPtr[rowPermuteFrom]; i++) {
        tempSecondArrayValue[counter] = matrix->value[i];
        tempSecondArrayColInd[counter] = matrix->colInd[i];
        counter++;
    }

    // shift original col and val array by difference in no of elements of both rows
    // if row1 has more elements than row2, array will shift leftwards
    // if row1 has less elements than row2, array will shift rightwards
    
    int tempColInd[matrix->nZ];
    double tempValue[matrix->nZ];
    for (int i = 0; i < matrix->nZ; i++) {
        tempColInd[i] = matrix->colInd[i];
        tempValue[i] = matrix->value[i];
    }
    for (int i = matrix->rowPtr[rowPermuteTo]; i < matrix->rowPtr[rowPermuteFrom] - 1; i++) {
        matrix->colInd[i - (nZSizeOfFirst - nZSizeOfSecond)] = tempColInd[i];
        matrix->value[i - (nZSizeOfFirst - nZSizeOfSecond)] = tempValue[i];
    }

    counter = 0;
    for (int i = matrix->rowPtr[rowPermuteTo - 1]; i < (matrix->rowPtr[rowPermuteTo - 1] + nZSizeOfSecond); i++) {
        matrix->value[i] = tempSecondArrayValue[counter];
        matrix->colInd[i] = tempSecondArrayColInd[counter];
        counter++;
    }
    counter = 0;
    for (int i = matrix->rowPtr[rowPermuteFrom - 1]; i < (matrix->rowPtr[rowPermuteFrom - 1] + nZSizeOfFirst); i++) {
        matrix->value[i-1] = tempFirstArrayValue[counter];
        matrix->colInd[i-1] = tempFirstArrayColInd[counter];
        counter++;
    }

    for (int i = rowPermuteTo; i < rowPermuteFrom; i++) {
        matrix->rowPtr[i] -= nZSizeOfFirst - nZSizeOfSecond;
    }
    
    #if EXCEPTION_HANDLING
        cout << "Exception Checking is Being Executed" << endl;
        for (int i = 0; i < nZ; i++) {
            if (isinf(matrix->value[i])) return IS_INF_NINF;
            if (isnan(matrix->value[i])) return IS_NAN;
        }
    #endif

    cout << endl;
    cout << "Permutation performed in row-compressed format between row " << rowPermuteTo << " and row " << rowPermuteFrom << endl << endl;
    cout << endl;
    return NO_ERROR;
}

// Function to do row-scaling operation in full matrix format
// Input arguments: row i, row j and scaling factor a (matrix is part of private member of the class)
// Result: row[i] = row[i] + row[j]*a
int Matrix_Operations::rowScaleFull(full_Matrix *matrix,  int rowScaledTo, int rowScaledFrom, double sFactor) {
    rowScaledTo--, rowScaledFrom--;

    for (int i= 0; i < matrix->rank; i++) {
        matrix->arr[rowScaledTo * matrix->rank + i] += sFactor * matrix->arr[rowScaledFrom * matrix->rank + i];
    }
    
    #if EXCEPTION_HANDLING
        cout << "Exception Checking is Being Executed" << endl;
        for (int i = 0; i < matrix->rank; i++) {
            for (int j = 0; j < matrix->rank; j++) {
                if (isinf(matrix->arr[(i * rank) + j])) return IS_INF_NINF;
                if (isnan(matrix->arr[(i * rank) + j])) return IS_NAN;
            }
        }
    #endif
    
    cout << endl;
    cout << "Scaling performed in full-matrix format between row " << rowScaledTo+1 << " and row " << rowScaledFrom+1 << " with scaling factor = " << sFactor  << endl;
    cout << endl;
    return NO_ERROR;
}

// Function to do row-scaling operation in sparse matrix format
// Input arguments: row i, row j and scaling factor a (matrix is part of private member of the class)
// Result: row[j] = row[j] + row[i]*a
int Matrix_Operations::rowScaleSparse(sparse_Matrix *matrix,  int rowScaledTo, int rowScaledFrom, double sFactor) {
    
    int nZInScaledToRow = abs(matrix->rowPtr[rowScaledTo] - matrix->rowPtr[rowScaledTo - 1]);
    
    int beforeValueArray[matrix->rowPtr[rowScaledTo - 1]];
    int afterValueArray[matrix->rowPtr[matrix->rank] - matrix->rowPtr[rowScaledTo]];
    int beforeColIndArray[matrix->rowPtr[rowScaledTo - 1]];
    int afterColIndArray[matrix->rowPtr[matrix->rank] - matrix->rowPtr[rowScaledTo]];
    
    for (int i = 0; i < matrix->rowPtr[rowScaledTo - 1]; i++) {
        beforeValueArray[i] = matrix->value[i];
        beforeColIndArray[i] = matrix->colInd[i];
    }
    for (int i = matrix->rowPtr[rowScaledTo]; i < matrix->rowPtr[matrix->rank]; i++) {
        afterValueArray[i - matrix->rowPtr[rowScaledTo]] = matrix->value[i];
        afterColIndArray[i - matrix->rowPtr[rowScaledTo]] = matrix->colInd[i];
    }
    
    int tempRowScaledTo[matrix->rank];
    int tempRowScaledFrom[matrix->rank];
    
    int tempCounterI = 0, tempCounterJ = 0;
    for (int i = matrix->rowPtr[rowScaledTo - 1]; i < matrix->rowPtr[rowScaledTo]; i++) {
        if (matrix->colInd[i] == tempCounterI) {
            tempRowScaledTo[tempCounterI] = matrix->value[i];
        }
        else {
            tempRowScaledTo[tempCounterI] = 0;
            i--;
        }
        tempCounterI++;
    }
    for (int i = tempCounterI; i < matrix->rank; i++) {
        tempRowScaledTo[i] = 0;
    }
    
    for (int i = matrix->rowPtr[rowScaledFrom - 1]; i < matrix->rowPtr[rowScaledFrom]; i++) {
        if (matrix->colInd[i] == tempCounterJ) {
            tempRowScaledFrom[tempCounterJ] = matrix->value[i] * sFactor;
        }
        else {
            tempRowScaledFrom[tempCounterJ] = 0;
            i--;
        }
        tempCounterJ++;
    }
    for (int i = tempCounterJ; i < matrix->rank; i++) {
        tempRowScaledFrom[i] = 0;
    }
    
    for (int i = 0; i < matrix->rank; i++) {
        tempRowScaledTo[i] += tempRowScaledFrom[i];
    }
    
    int newNZInScaledToRow = 0;
    for (int i = 0; i < matrix->rank; i++) {
        if (tempRowScaledTo[i] != 0) newNZInScaledToRow++;
    }
    int tempNZRowScaledToValues[newNZInScaledToRow];
    int tempNZRowScaledToColInd[newNZInScaledToRow];
    int tempCounter = 0;
    for (int i = 0; i < matrix->rank; i++) {
        if (tempRowScaledTo[i] != 0) {
            tempNZRowScaledToValues[tempCounter] = tempRowScaledTo[i];
            tempNZRowScaledToColInd[tempCounter] = i;
            tempCounter++;
        }
    }
    
    matrix->nZ = matrix->nZ - nZInScaledToRow + newNZInScaledToRow;
    
    
    matrix->value = (double *)malloc(matrix->nZ * sizeof(double));
    matrix->colInd = (int *)malloc(matrix->nZ * sizeof(int));
    
    tempCounter = 0;
    for (int i = 0; i < matrix->rowPtr[rowScaledTo - 1]; i++) {
        matrix->value[tempCounter] = beforeValueArray[i];
        matrix->colInd[tempCounter] = beforeColIndArray[i];
        tempCounter++;
    }
    for (int i = 0; i < newNZInScaledToRow; i++) {
        matrix->value[tempCounter] = tempNZRowScaledToValues[i];
        matrix->colInd[tempCounter] = tempNZRowScaledToColInd[i];
        tempCounter++;
    }
    for (int i = 0; i < (matrix->rowPtr[matrix->rank] - matrix->rowPtr[rowScaledTo]); i++) {
        matrix->value[tempCounter] = afterValueArray[i];
        matrix->colInd[tempCounter] = afterColIndArray[i];
        tempCounter++;
    }
    for (int i = rowScaledTo; i < matrix->rank + 1; i++) {
        matrix->rowPtr[i] += newNZInScaledToRow - nZInScaledToRow;
    }
    
    
    #if EXCEPTION_HANDLING
        cout << "Exception Checking is Being Executed" << endl;
        for (int i = 0; i < nZ; i++) {
            if (isinf(value[i])) return IS_INF_NINF;
            if (isnan(value[i])) return IS_NAN;
        }
    #endif
    
    cout << endl;
    cout << "Scaling performed in sparse-matrix format between row " << rowScaledTo << " and row " << rowScaledFrom << " with scaling factor = " << sFactor  << endl;
    cout << endl;
    
    return NO_ERROR;
}

// Function to do product operation in full matrix format
// Input arguments: row i, row j and scaling factor a (matrix is part of private member of the class)
// TODO below code is wrong
int Matrix_Operations::productAxFull(full_Matrix *A, full_Vector *x, full_Vector *b) {
    
    #if EXCEPTION_HANDLING
        cout << "Exception Checking is Being Executed" << endl;
        if (A->rank != x->rank) return UNMATCHED_RANK;
    #endif
    
    b->arr = (double *)malloc(A->rank * sizeof(double));
    b->rank = A->rank;
    
    for (int i = 0; i < A->rank; i++) {
        b->arr[i] = 0;
    }
    for (int i = 0; i < A->rank; i++) {
        for (int j = 0; j < A->rank; j++) {
            b->arr[i] += A->arr[(i * A->rank) + j] * x->arr[j];
        }
    }
    
    #if EXCEPTION_HANDLING
        cout << "Exception Checking is Being Executed" << endl;
        for (int i = 0; i < rank; i++) {
            if (isinf(b[i]) return IS_INF_NINF;
            if (isnan(b[i]) return IS_NAN;
        }
    #endif

    cout << endl;
    cout << "Product performed in full-matrix format" << endl;
    cout << endl;

    return NO_ERROR;
}

// Function to do row-scaling operation in full matrix format
// Input arguments: row i, row j and scaling factor a (matrix is part of private member of the class)
// TODO below code is wrong
int Matrix_Operations::productAxSparse(sparse_Matrix *A, full_Vector *x, full_Vector *b) {
    
    #if EXCEPTION_HANDLING
        cout << "Exception Checking is Being Executed" << endl;
        if (A->rank != x->rank) return UNMATCHED_RANK;
    #endif
    
    int tempRowScaledTo[A->rank];
    int tempCounterI = 0;
    
    b->arr = (double *)malloc(A->rank * sizeof(double));
    b->rank = A->rank;

    for (int i = 0; i < A->rank; i++) {
        b->arr[i] = 0;
    }
    
    
    for (int i = 0; i < A->rank; i++) {
        tempCounterI = 0;
        for (int j = A->rowPtr[i]; j < A->rowPtr[i + 1]; j++) {
            if (A->colInd[j] == tempCounterI) {
                tempRowScaledTo[tempCounterI] = A->value[j];
            }
            else {
                tempRowScaledTo[tempCounterI] = 0;
                j--;
            }
            if (tempCounterI > 4990) 
            cout << i << " " << j << " " << tempCounterI << " " << tempRowScaledTo[tempCounterI] << endl;
            tempCounterI++;
        }
        for (int j = tempCounterI; j < A->rank; j++) {
            tempRowScaledTo[j] = 0;
        }
        //for (int k = 0; k < A->rank; k++) {
        //    cout << tempRowScaledTo[k] << " ";
        //}
        cout << endl;
        //cout << i << endl;
        for (int j = 0; j < A->rank; j++) {
            b->arr[i] +=  tempRowScaledTo[j] * x->arr[j];
        }
    }
    
    #if EXCEPTION_HANDLING
        cout << "Exception Checking is Being Executed" << endl;
        for (int i = 0; i < rank; i++) {
            if (isinf(b[i]) return IS_INF_NINF;
            if (isnan(b[i]) return IS_NAN;
        }
    #endif

    cout << endl;
    cout << "Product performed in sparse-matrix format" << endl;
    cout << endl;

    return NO_ERROR;
}