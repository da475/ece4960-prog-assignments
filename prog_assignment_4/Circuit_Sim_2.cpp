/* 
 * Author: Vishisht, Deepak
 * Netids: vmt28 and da475
 * Copyright @ 2018 Vishisht and Deepak. All rights reserved

 * Created on April 21, 2018, 11:06 PM
 * File: Circuit_Sim_2.cpp
 * Desc: CS Amplifier equations are implemented here. This class
 * calls ODE_Solvers to get the solution
 */

#include "Circuit_Sim_2.h"

// dx/dt implemented here
// Exception handling is done by all the Global_Functions
void Circuit_Sim_2::fx(arrayMatCol *x, double t, arrayMatCol *result)
{  
    
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
// Constructor
Circuit_Sim_2::Circuit_Sim_2(double Step)
{
    double start = 0;
    double stop = 100e-9;
    double step = Step * 1e-9;
    double rank = 2;
    double initialValue = 2.5;
    
    // Initialize the arrayMat and fullVect for values, time and delT
    arrayMat *calculatedValues = new arrayMat();
    fullVect *time = new fullVect();
    fullVect *delT = new fullVect();
    
    // Initialize the solver class
    ODE_Solvers *solver = new ODE_Solvers(initialValue, time, delT, start, stop, step, fx);
    
    // Solving ODE Using Forward Euler
    cout << endl << endl << endl << "-------------- Solving ODE Using Forward Euler --------------" << endl << endl;
    Global_Functions::create_Time_Values(start, stop, step, rank, calculatedValues, time, delT);
    solver->forward_Euler(calculatedValues);
    Global_Functions::print_Comparison(time, calculatedValues);
    
    // Solving ODE Using RK34 Without Time Adaptivity
    cout << endl << endl << endl << "-------------- Solving ODE Using RK34 Without Time Adaptivity --------------" << endl << endl;
    solver->rk34(calculatedValues, time);
    Global_Functions::print_Comparison(time, calculatedValues);
    
    // Solving ODE Using RK34 With Time Adaptivity
    cout << endl << endl << endl << "-------------- Solving ODE Using RK34 With Time Adaptivity --------------" << endl << endl;
    solver->rk34(calculatedValues, time, true);
    Global_Functions::print_Comparison(time, calculatedValues);
}

// Destructor
Circuit_Sim_2::~Circuit_Sim_2()
{
}