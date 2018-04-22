/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Validation.cpp
 * Author: Vishisht
 * 
 * Created on April 21, 2018, 10:03 PM
 */

#include "Validation.h"


void Validation::fx(arrayMatCol *x, double t, arrayMatCol *result) {
    arrayMatCol *scaledX = new arrayMatCol();
    
    Global_Functions::column_Scaling(-0.5, x, scaledX);
    Global_Functions::column_Shifting(4 * exp(0.8 * t), scaledX, result);
}

void Validation::true_Values(arrayMat *values, fullVect *time) {
    if (values->dim != time->dim) throw UNMATCHED_DIM;

    
    int dim = values->dim;
    
    for (int i = 0; i < dim; i++) {
        double tempConst = ((4.0/1.3) * (exp(0.8 * time->arr[i]) - exp(-0.5 * time->arr[i]))) + (2 * exp(-0.5 * time->arr[i]));
        Global_Functions::column_Shifting(tempConst, values->arr[i], values->arr[i]);
    }
}

Validation::Validation() {
    double start = 0;
    double stop = 5;
    double step = 1;
    double rank = 1;
    double initialValue = 2;
    
    arrayMat *trueValues = new arrayMat();
    arrayMat *forwardEulerValues = new arrayMat();
    arrayMat *rk34WoAdaptValues = new arrayMat();
    fullVect *time = new fullVect();
    fullVect *delT = new fullVect();
    
    Global_Functions::create_Time_Values(start, stop, step, rank, trueValues, time, delT);
    Global_Functions::create_Time_Values(start, stop, step, rank, forwardEulerValues, time, delT);
    Global_Functions::create_Time_Values(start, stop, step, rank, rk34WoAdaptValues, time, delT);
    
    
    ODE_Solvers *solver = new ODE_Solvers();
    
    solver->forward_Euler(initialValue, forwardEulerValues, time, delT, fx);
    solver->rk34_Without_Adapt(initialValue, rk34WoAdaptValues, time, delT, fx);
    true_Values(trueValues, time);
    
    Global_Functions::print_Comparison(forwardEulerValues, rk34WoAdaptValues, trueValues);
}

Validation::~Validation() {
}

