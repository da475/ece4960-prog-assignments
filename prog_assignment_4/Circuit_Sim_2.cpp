/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Circuit_Sim_2.cpp
 * Author: Vishisht
 * 
 * Created on April 21, 2018, 11:36 PM
 */

#include "Circuit_Sim_2.h"

void Circuit_Sim_2::fx(arrayMatCol *x, double t, arrayMatCol *result) {  
    
    double Is = 5e-6;
    double Kappa = 0.7;
    double Vth = 1;
    double Vdd = 5;
    double Rg = 10e3, Rl = 10e3;
    double C1 = 1e-12, C2 = 1e-12;
    double Vt = 26e-3;
    double Id = Is * (pow(log(1 + exp(Kappa * (x->col[0] - Vth))/(2 * Vt)), 2)) - 
    Is * (pow(log(1 + exp(Kappa * (x->col[0] - Vth) - x->col[1])/(2 * Vt)), 2));
    
    double i;
    t = fmod(t,20e-9);
    t *= 1e9;

    if (t < 1) i = 0.1e-3 * t;
    else if (t >= 1 && t <= 10) i = 0.1e-3;
    else if (t > 10 && t < 11) i = (-0.1e-3 * t) + 1.1e-3;
    else if (t >= 11) i = 0;
    
    result->rank = x->rank;
    result->col = (double *)calloc(x->rank, sizeof(double));
    
    result->col[0] = -(x->col[0]/(Rg * C1)) + i/C1;
    result->col[1] = -(Id/C2) - (x->col[1]/(Rl * C2)) + (Vdd/(Rl * C2));
}

Circuit_Sim_2::Circuit_Sim_2(double Step) {
    double start = 0;
    double stop = 100e-9;
    double step = Step * 1e-9;
    double rank = 2;
    double initialValue = 2;
    
    arrayMat *trueValues = new arrayMat();
    arrayMat *forwardEulerValues = new arrayMat();
    arrayMat *rk34WoAdaptValues = new arrayMat();
    fullVect *time = new fullVect();
    fullVect *delT = new fullVect();
    
    Global_Functions::create_Time_Values(start, stop, step, rank, trueValues, time, delT);
    Global_Functions::create_Time_Values(start, stop, step, rank, forwardEulerValues, time, delT);
    Global_Functions::create_Time_Values(start, stop, step, rank, rk34WoAdaptValues, time, delT);
    
    
    ODE_Solvers *solver = new ODE_Solvers(initialValue, time, delT, fx);
    
    solver->forward_Euler(forwardEulerValues);
    solver->rk34_Without_Adapt(rk34WoAdaptValues);
    
    Global_Functions::print_Comparison(time, forwardEulerValues, rk34WoAdaptValues);
}

Circuit_Sim_2::~Circuit_Sim_2() {
}