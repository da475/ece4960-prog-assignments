/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   power_Law_Parameter_Extraction.cpp
 * Author: Vishisht
 * 
 * Created on April 5, 2018, 3:56 PM
 */

#include "power_Law_Parameter_Extraction.h"

void power_Law_Parameter_Extraction::find_S_Measured() {
    for (int i = 0; i < sizeof(X)/sizeof(X[0]); i++) {
        double temp = (rand() % 40 + 80);
        if (temp > 90 && temp <= 100) temp -= 10;
        if (temp > 100 && temp < 110) temp += 10;
        temp /= 100;
        S_Measured[i] = 10 * pow(X[i], -0.5) * temp;
    }
    #if EXCEPTION_HANDLING
        for (int i = 0; i < sizeof(X)/sizeof(X[0]); i++) {
            if (isinf(S_Measured[i])) throw IS_INF_NINF;
            if (isnan(S_Measured[i])) throw IS_NAN;
            if (isinf(X[i])) throw IS_INF_NINF;
            if (isnan(X[i])) throw IS_NAN;
        }
    #endif  
}

void power_Law_Parameter_Extraction::find_S_Model(full_Vector *answer) {
    double *jacobianPointer = (double *)calloc(rank * rank, sizeof(double));
    
    for (int i = 0; i < sizeof(X)/sizeof(X[0]); i++) {
        jacobianPointer[0] += log(X[i])*log(X[i]);
        jacobianPointer[1] += log(X[i]);
    }
    jacobianPointer[2] = jacobianPointer[1];
    jacobianPointer[3] = 10;
    
    #if EXCEPTION_HANDLING
        for (int i = 0; i < sizeof(X)/sizeof(X[0]); i++) {
            if (isinf(jacobianPointer[0])) throw IS_INF_NINF;
            if (isinf(jacobianPointer[1])) throw IS_INF_NINF;
            if (isinf(jacobianPointer[2])) throw IS_INF_NINF;
            if (isinf(jacobianPointer[3])) throw IS_INF_NINF;
            if (isnan(jacobianPointer[0])) throw IS_NAN;
            if (isnan(jacobianPointer[1])) throw IS_NAN;
            if (isnan(jacobianPointer[2])) throw IS_NAN;
            if (isnan(jacobianPointer[3])) throw IS_NAN;
        }
    #endif  
    
    full_Matrix *jacobian = new full_Matrix();
    Global_Functions::create_Struct_From_Matrix(jacobianPointer, jacobian, rank);
    
    double *RHSPointer = (double *)calloc(2, sizeof(double));
    for (int i = 0; i < sizeof(X)/sizeof(X[0]); i++) {
        RHSPointer[0] += log(X[i])*log(S_Measured[i]) ;
        RHSPointer[1] += log(S_Measured[i]);
    }
    
    #if EXCEPTION_HANDLING
        for (int i = 0; i < sizeof(X)/sizeof(X[0]); i++) {
            if (isinf(RHSPointer[0])) throw IS_INF_NINF;
            if (isinf(RHSPointer[1])) throw IS_INF_NINF;
            if (isnan(RHSPointer[0])) throw IS_NAN;
            if (isnan(RHSPointer[1])) throw IS_NAN;
        }
    #endif  
    
    full_Vector *RHS = new full_Vector();
    Global_Functions::create_Struct_From_Vector(RHSPointer, RHS, rank);
    
    full_Matrix_Solver *solver = new full_Matrix_Solver(jacobian, RHS);
    solver->l_U_Decomposition();
    solver->back_Substitution(answer);
    answer->arr[rank - 1] = exp(answer->arr[rank - 1]);
    
    #if EXCEPTION_HANDLING
        for (int i = 0; i < rank; i++) {
            if (isinf(answer->arr[i])) throw IS_INF_NINF;
            if (isnan(answer->arr[i])) throw IS_NAN;
        }
    #endif  
}

power_Law_Parameter_Extraction::power_Law_Parameter_Extraction() {
    srand(time(0));
    for (int i = 0; i < sizeof(X)/sizeof(X[0]); i++) {
        X[i] = (double)(rand() % 500)/100;
    }
    this->rank = 2;
}

power_Law_Parameter_Extraction::~power_Law_Parameter_Extraction() {
}