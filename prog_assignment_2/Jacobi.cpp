/* 
 * File:   Jacobi.cpp
 * Author: Vishisht, Deepak
 *
 * Created on March 4, 2018, 1:23 PM
 */

#include "Assignment2_Header.h"
    
void Jacobi::Initializing_Matrix() 
{
    x->arr = (double *)malloc(b->rank * sizeof(double));
    x->rank = b->rank;

    for (int i = 0; i < b->rank; i++) {
        x->arr[i] = 0;
    }
}
    
void Jacobi::Full_Matrix_Jacobi_Implementation() 
{
    double *T = (double *)malloc(A->rank * A->rank * sizeof(double));
    
    for (int i = 0; i < A->rank; i++) {
        x->arr[i] = 0;
    }
    for (int i = 0; i < A->rank; i++) {
        for (int j = 0; j < A->rank; j ++) {
            T[(i * A->rank) + j] = A->arr[(i * A->rank) + j];
        }
    }
    
    for (int i = 0; i < A->rank; i++){
        for (int j = 0; j < A->rank; j++) {
            T[(i * A->rank) + j] /= -A->arr[(i * A->rank) + i];
        }
        T[(i * A->rank) + i] = 0;
    }

    double *xtemp = (double *)malloc(A->rank * sizeof(double));

    long double converged= 0;
    int counter = 0;
    do {
        converged = 0;
        counter++;
        for (int i = 0; i < A->rank; i++) {
            xtemp[i] = x->arr[i];
            x->arr[i] = 0;
        }
        for (int i = 0; i < A->rank; i++) {
            for (int j = 0; j < A->rank; j++) {
                x->arr[i] += T[(i * A->rank) + j] * xtemp[j];
            }
            x->arr[i] += b->arr[i]/A->arr[(i * A->rank) + i];
        }
        for (int i = 0; i < A->rank; i++) {
            if ((xtemp[i] - x->arr[i]) < 0) converged += -(xtemp[i] - x->arr[i]);
            else converged += (xtemp[i] - x->arr[i]);
        }
    } while (converged > tolerance);
}
    
void Jacobi::Row_Compressed_Jacobi_Implementation()
{
    for (int i = 0; i < ASparse->rank; i++) {
        x->arr[i] = 0;
    }

    double *TRowCompressed = (double *)malloc(ASparse->nZ * sizeof(double));
    for (int i = 0; i < ASparse->nZ; i++) {
        TRowCompressed[i] = ASparse->value[i];
    }

    double diag = 0;
    for (int i = 1; i < (ASparse->rank + 1); i++) {
        for (int j = ASparse->rowPtr[i - 1]; j < ASparse->rowPtr[i]; j++) {
            if (ASparse->colInd[j] == i - 1) {
                diag = ASparse->value[j];
                TRowCompressed[j] = 0;
                break;
            }
        }
        for (int j = ASparse->rowPtr[i - 1]; j < ASparse->rowPtr[i]; j++) {
            TRowCompressed[j] /= -diag;
        }
    }

    double *xtemp = (double *)malloc(ASparse->rank * sizeof(double));

    long double converged= 0;
    int counter = 0;
    do {
        converged = 0;
        counter++;
        for (int i = 0; i < ASparse->rank; i++) {
            xtemp[i] = x->arr[i];
            x->arr[i] = 0;
        }
        double diag = 0;
        for (int i = 1; i < (ASparse->rank + 1); i++) {
            for (int j = ASparse->rowPtr[i - 1]; j < ASparse->rowPtr[i]; j++) {
                if (ASparse->colInd[j] == i - 1) {
                    diag = ASparse->value[j];
                    TRowCompressed[j] = 0;
                    break;
                }
            }
            for (int j = ASparse->rowPtr[i - 1]; j < ASparse->rowPtr[i]; j++) {
                x->arr[i-1] += TRowCompressed[j] * xtemp[ASparse->colInd[j]];
            }
            x->arr[i-1] += b->arr[i-1]/diag;
        }
        for (int i = 0; i < ASparse->rank; i++) {
            converged += abs(xtemp[i] - x->arr[i]);
        }
    } while (converged > tolerance);
}

Jacobi::Jacobi(full_Matrix *A, full_Vector *b, full_Vector *x) 
{
    this->A = A;
    this->b = b;
    this->x = x;
    
    Initializing_Matrix();
    Full_Matrix_Jacobi_Implementation();
}

Jacobi::Jacobi(sparse_Matrix *ASparse, full_Vector *b, full_Vector *x) 
{
    this->ASparse = ASparse;
    this->b = b;
    this->x = x;

    Initializing_Matrix();
    Row_Compressed_Jacobi_Implementation();
}

Jacobi::~Jacobi() 
{
    if (this->A->arr) free(this->A->arr);
    if (this->x->arr) free(this->x->arr);
    if (this->b->arr) free(this->b->arr);
    
    if (this->A) free(this->A);
    if (this->x) free(this->x);
    if (this->b) free(this->b);
    
    if (this->ASparse->value) free(this->ASparse->value);
    if (this->ASparse->colInd) free(this->ASparse->colInd);
    if (this->ASparse->rowPtr) free(this->ASparse->rowPtr);
}