/* 
 * File:   ODE_Solvers.cpp
 * Author: Vishisht
 * 
 * Created on April 18, 2018, 5:19 PM
 */

#include "ODE_Solvers.h"

double rel_tolerance = 1e-7;
double abs_tolerance = 1e-4;

void ODE_Solvers::initializeValue(arrayMat *values) {
    Global_Functions::column_Shifting(this->initialValue, values->arr[0], values->arr[0]);
}

void ODE_Solvers::forward_Euler(arrayMat *values) {
    if (values->dim != this->time->dim || this->time->dim != this->delT->dim) throw UNMATCHED_DIM;
    
    int dim = values->dim;
    
    initializeValue(values);
    
    for (int i = 0; i < dim - 1; i++) {
        arrayMatCol *temp = new arrayMatCol();
        arrayMatCol *temp1 = new arrayMatCol();
        arrayMatCol *temp2 = new arrayMatCol();
        
        this->func(values->arr[i], this->time->arr[i], temp);
        Global_Functions::column_Scaling(this->delT->arr[i], temp, temp1);
        Global_Functions::column_Addition(temp1, values->arr[i], temp2);
        values->arr[i + 1] = temp2;
    } 
}

void ODE_Solvers::rk34_K1(arrayMatCol *k1, arrayMatCol *value, double time) {
    this->func(value, time, k1);
}

void ODE_Solvers::rk34_K2(arrayMatCol *k2, arrayMatCol *value, double time, double delT, arrayMatCol *k1) {
    arrayMatCol *scaledK1 = new arrayMatCol();
    arrayMatCol *newValue = new arrayMatCol();
    
    Global_Functions::column_Scaling(0.5 * delT, k1, scaledK1);
    Global_Functions::column_Addition(value, scaledK1, newValue);
                 
    this->func(newValue, time + (0.5 * delT), k2);
}

void ODE_Solvers::rk34_K3(arrayMatCol *k3, arrayMatCol *value, double time, double delT, arrayMatCol *k2) {
    arrayMatCol *scaledK2 = new arrayMatCol();
    arrayMatCol *newValue = new arrayMatCol();
    
    Global_Functions::column_Scaling(0.75 * delT, k2, scaledK2);
    Global_Functions::column_Addition(value, scaledK2, newValue);
                 
    this->func(newValue, time + (0.75 * delT), k3);   
}

void ODE_Solvers::rk34_K4(arrayMatCol *k4, arrayMatCol *value, double time, double delT, arrayMatCol *k3) {
    arrayMatCol *scaledK3 = new arrayMatCol();
    arrayMatCol *newValue = new arrayMatCol();
    
    Global_Functions::column_Scaling(delT, k3, scaledK3);
    Global_Functions::column_Addition(value, scaledK3, newValue);
                 
    this->func(newValue, time + delT, k4);
}


void ODE_Solvers::rk34_Without_Adapt(arrayMat *values) {
    if (values->dim != this->time->dim || this->time->dim != this->delT->dim) throw UNMATCHED_RANK;
    
    initializeValue(values);
    
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
        rk34_K1(k1, values->arr[i], this->time->arr[i]);
        rk34_K2(k2, values->arr[i], this->time->arr[i], this->delT->arr[i], k1);
        rk34_K3(k3, values->arr[i], this->time->arr[i], this->delT->arr[i], k2);
        rk34_K4(k4, values->arr[i], this->time->arr[i], this->delT->arr[i], k3);
        
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
        
        Global_Functions::column_Scaling(this->delT->arr[i] / 24.0, kSum3, kSumScaled);
        
        Global_Functions::column_Addition(values->arr[i], kSumScaled, values->arr[i + 1]);
    }
}

double ODE_Solvers::new_TimeSteps(arrayMatCol *err_estimate, arrayMatCol *value, double delT) {
    double numerator = rel_tolerance;
    double errNorm = Global_Functions::calculate_Norm(err_estimate);
    double valueNorm = Global_Functions::calculate_Norm(value);
    double denominator = errNorm/(valueNorm + abs_tolerance);
//    cout.precision(10);
//    cout << numerator << "a" << denominator << endl;
//    cout.precision(2);
    return delT * cbrt(numerator/denominator);
}

void ODE_Solvers::rk34_With_Adapt(arrayMat *valuesOriginal, fullVect*timeOiginal, double start, double stop, double step) {
    
    int rank = valuesOriginal->rank;
    
    vector<arrayMatCol*> *values = new vector<arrayMatCol*>();
    vector<double> *time = new vector<double>();
    vector<double> *delT = new vector<double>();
    
    arrayMatCol *initial = new arrayMatCol();
    initial->rank = rank;
    initial->col = (double *)calloc(rank, sizeof(double));
    for (int i = 0; i < rank; i++) initial->col[i] = this->initialValue;
    
    values->push_back(initial);
    time->push_back(start);
    delT->push_back(step);
    
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
    
    
    
    int i = 0;
    do {
        rk34_K1(k1, (*values)[i], (*time)[i]);
        rk34_K2(k2, (*values)[i], (*time)[i], (*delT)[i], k1);
        rk34_K3(k3, (*values)[i], (*time)[i], (*delT)[i], k2);
        rk34_K4(k4, (*values)[i], (*time)[i], (*delT)[i], k3);
        
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
        
        Global_Functions::column_Scaling((*delT)[i] / 24.0, kSum3, kSumScaled);
        
        arrayMatCol *nextValue = new arrayMatCol();
        nextValue->rank = rank;
        nextValue->col = (double *)calloc(rank, sizeof(double));
        values->push_back(nextValue);
        
        Global_Functions::column_Addition((*values)[i], kSumScaled, (*values)[i + 1]);
        arrayMatCol *k1ErrorScaled = new arrayMatCol();
        arrayMatCol *k2ErrorScaled = new arrayMatCol();
        arrayMatCol *k3ErrorScaled = new arrayMatCol();
        arrayMatCol *k4ErrorScaled = new arrayMatCol();
        arrayMatCol *kErrorSum1 = new arrayMatCol();
        arrayMatCol *kErrorSum2 = new arrayMatCol();
        arrayMatCol *kErrorSum3 = new arrayMatCol();
        arrayMatCol *err_Estimate = new arrayMatCol();
        err_Estimate->rank = rank;
        err_Estimate->col = (double *)calloc(rank, sizeof(double));
        
        Global_Functions::column_Scaling(-5, k1, k1ErrorScaled);
        Global_Functions::column_Scaling(6, k2, k2ErrorScaled);
        Global_Functions::column_Scaling(8, k3, k3ErrorScaled);
        Global_Functions::column_Scaling(-9, k4, k4ErrorScaled);
        
        Global_Functions::column_Addition(k1ErrorScaled, k2ErrorScaled, kErrorSum1);
        Global_Functions::column_Addition(k3ErrorScaled, k4ErrorScaled, kErrorSum2);
        Global_Functions::column_Addition(kErrorSum1, kErrorSum2, kErrorSum3);
        
        Global_Functions::column_Scaling((*delT)[i] / 72.0, kErrorSum3, err_Estimate);
        
        delT->push_back(new_TimeSteps(err_Estimate, (*values)[i + 1], (*delT)[i]));
        time->push_back((*time)[i] + (*delT)[i + 1]);
        i++;
        cout << (*time)[i] << " " << (*delT)[i] << endl;
    } while((*time)[i] <= stop);
    Global_Functions::convert_Vector_FullMat(values, valuesOriginal);
    Global_Functions::convert_Vector_Vector(time, timeOiginal);
}

ODE_Solvers::ODE_Solvers(double initialValue, fullVect *time, fullVect *delT, void(*func)(arrayMatCol*,double,arrayMatCol*)) {
    this->initialValue = initialValue;
    this->time = time;
    this->delT = delT;
    this->func = func;
}

ODE_Solvers::~ODE_Solvers() {
}

