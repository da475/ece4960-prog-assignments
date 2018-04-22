/*
 * To cdelTange tdelTis license delTeader, cdelToose License Headers in Project Properties.
 * To cdelTange tdelTis template file, cdelToose Tools | Templates
 * and open tdelTe template in tdelTe editor.
 */

/* 
 * File:   ODE_Solvers.cpp
 * Author: Vishisht
 * 
 * Created on April 18, 2018, 5:19 PM
 */

#include "ODE_Solvers.h"

ODE_Solvers::ODE_Solvers() {
}



void ODE_Solvers::initializeValue(double initialValue, arrayMat *values) {
    Global_Functions::column_Shifting(initialValue, values->arr[0], values->arr[0]);
}

void ODE_Solvers::forward_Euler(double initialValue, arrayMat *values, fullVect *time, fullVect *delT, void(*func)(arrayMatCol*,double,arrayMatCol*)) {
    if (values->dim != time->dim || time->dim != delT->dim) throw UNMATCHED_DIM;
    
    int dim = values->dim;
    
    initializeValue(initialValue, values);
    
    for (int i = 0; i < dim - 1; i++) {
        arrayMatCol *temp = new arrayMatCol();
        arrayMatCol *temp1 = new arrayMatCol();
        arrayMatCol *temp2 = new arrayMatCol();
        
        func(values->arr[i], time->arr[i], temp);
        Global_Functions::column_Scaling(delT->arr[i], temp, temp1);
        Global_Functions::column_Addition(temp1, values->arr[i], temp2);
        values->arr[i + 1] = temp2;
    } 
}

void ODE_Solvers::rk34_K1(arrayMatCol *k1, arrayMatCol *value, double time, void(*func)(arrayMatCol*,double,arrayMatCol*)) {
    func(value, time, k1);
}

void ODE_Solvers::rk34_K2(arrayMatCol *k2, arrayMatCol *value, double time, double delT, arrayMatCol *k1, void(*func)(arrayMatCol*,double,arrayMatCol*)) {
    arrayMatCol *scaledK1 = new arrayMatCol();
    arrayMatCol *newValue = new arrayMatCol();
    
    Global_Functions::column_Scaling(0.5 * delT, k1, scaledK1);
    Global_Functions::column_Addition(value, scaledK1, newValue);
                 
    func(newValue, time + (0.5 * delT), k2);
}

void ODE_Solvers::rk34_K3(arrayMatCol *k3, arrayMatCol *value, double time, double delT, arrayMatCol *k2, void(*func)(arrayMatCol*,double,arrayMatCol*)) {
    arrayMatCol *scaledK2 = new arrayMatCol();
    arrayMatCol *newValue = new arrayMatCol();
    
    Global_Functions::column_Scaling(0.75 * delT, k2, scaledK2);
    Global_Functions::column_Addition(value, scaledK2, newValue);
                 
    func(newValue, time + (0.75 * delT), k3);   
}

void ODE_Solvers::rk34_K4(arrayMatCol *k4, arrayMatCol *value, double time, double delT, arrayMatCol *k3, void(*func)(arrayMatCol*,double,arrayMatCol*)) {
    arrayMatCol *scaledK3 = new arrayMatCol();
    arrayMatCol *newValue = new arrayMatCol();
    
    Global_Functions::column_Scaling(delT, k3, scaledK3);
    Global_Functions::column_Addition(value, scaledK3, newValue);
                 
    func(newValue, time + delT, k4);
}


void ODE_Solvers::rk34_Without_Adapt(double initialValue, arrayMat *values, fullVect *time, fullVect *delT, void(*func)(arrayMatCol*,double,arrayMatCol*)) {
    if (values->dim != time->dim || time->dim != delT->dim) throw UNMATCHED_RANK;
    
    initializeValue(initialValue, values);
    
    int dim = values->dim;
    int rank = values->rank;
    
    arrayMatCol *k1 = new arrayMatCol();
    arrayMatCol *k2 = new arrayMatCol();
    arrayMatCol *k3 = new arrayMatCol();
    arrayMatCol *k4 = new arrayMatCol();
    
    k1->rank = rank;
    k2->rank = rank;
    k3->rank = rank;
    k4->rank = rank;
    
    k1->col = (double *)calloc(rank, sizeof(double));
    k2->col = (double *)calloc(rank, sizeof(double));
    k3->col = (double *)calloc(rank, sizeof(double));
    k4->col = (double *)calloc(rank, sizeof(double));
    
    for (int i = 0; i < dim - 1; i++) {
        rk34_K1(k1, values->arr[i], time->arr[i], func);
        rk34_K2(k2, values->arr[i], time->arr[i], delT->arr[i], k1, func);
        rk34_K3(k3, values->arr[i], time->arr[i], delT->arr[i], k2, func);
        rk34_K4(k4, values->arr[i], time->arr[i], delT->arr[i], k3, func);
        
        arrayMatCol *k1Scaled = new arrayMatCol();
        arrayMatCol *k2Scaled = new arrayMatCol();
        arrayMatCol *k3Scaled = new arrayMatCol();
        arrayMatCol *k4Scaled = new arrayMatCol();
        arrayMatCol *kSum1 = new arrayMatCol();
        arrayMatCol *kSum2 = new arrayMatCol();
        arrayMatCol *kSum3 = new arrayMatCol();
        arrayMatCol *kSumScaled = new arrayMatCol();
        
        Global_Functions::column_Scaling(7, k1, k1Scaled);
        Global_Functions::column_Scaling(6, k2, k2Scaled);
        Global_Functions::column_Scaling(8, k3, k3Scaled);
        Global_Functions::column_Scaling(3, k4, k4Scaled);
        
        Global_Functions::column_Addition(k1Scaled, k2Scaled, kSum1);
        Global_Functions::column_Addition(k3Scaled, k4Scaled, kSum2);
        Global_Functions::column_Addition(kSum1, kSum2, kSum3);
        
        Global_Functions::column_Scaling(delT->arr[i] / 24.0, kSum3, kSumScaled);
        
        Global_Functions::column_Addition(values->arr[i], kSumScaled, values->arr[i + 1]);
    }
}





/*
 * double ODE_Solvers::new_TimeSteps(double err_estimate, double x, double delT, double rel_tol, double abs_tol) {
    double numerator = rel_tol;
    double denominator = abs(err_estimate)/(abs(x) + abs_tol);
    return delT * cbrt(numerator/denominator);
}
 * 
void ODE_Solvers::rk34_With_Adapt(double initialValue, arrayMat *values, arrayMat *time, arrayMat *delT, double(*func)(double, double)) {
    if (values->rank != time->rank || time->rank != delT->rank) throw UNMATCHED_RANK;
    
    int start = time->arr[0];
    int stop = time->arr[rank - 1];
    
    vector<double> newValues = new vector<double>();
    vector<double> newTime = new vector<double>();
    vector<double> newdelT = new vector<double>();
    
    double err_estimate;
    
    values->arr[0] = initialValue;
    
    int rank = values->rank;
    
    arrayMat *k1 = new arrayMat();
    arrayMat *k2 = new arrayMat();
    arrayMat *k3 = new arrayMat();
    arrayMat *k4 = new arrayMat();
    
    k1->rank = rank;
    k2->rank = rank;
    k3->rank = rank;
    k4->rank = rank;
    
    k1->col = (double *)calloc(rank, sizeof(double));
    k2->col = (double *)calloc(rank, sizeof(double));
    k3->col = (double *)calloc(rank, sizeof(double));
    k4->col = (double *)calloc(rank, sizeof(double));
    
    for (int t = start; t < stop; t += delT) {
        
        
        
        
        
        
        
        
        k1->col[i] = rk34_K1(values->arr[i], time->arr[i], func);
        k2->col[i] = rk34_K2(values->arr[i], time->arr[i], 0.5 * delT->arr[i], k1->col[i], func);
        k3->col[i] = rk34_K3(values->arr[i], time->arr[i], 0.75 * delT->arr[i], k2->col[i], func);
        k4->col[i] = rk34_K4(values->arr[i], time->arr[i], delT->arr[i], k3->col[i], func);
        values->arr[i + 1] = values->arr[i] + ((7 * k1->col[i]) + (6 * k2->col[i]) + (8 * k3->col[i]) + (3 * k4->col[i])) * (delT->arr[i] / 24);
        err_estimate = ((-5 * k1->col[i]) + (6 * k2->col[i]) + (8 * k3->col[i]) + (-9 * k4->col[i])) * (delT->arr[i] / 72);
        delT->arr[i + 1] = new_TimeSteps(err_estimate, values->arr[i + 1], delT->arr[i], 1e-4, 1e-7);
    }
}



*/


ODE_Solvers::~ODE_Solvers() {
}

