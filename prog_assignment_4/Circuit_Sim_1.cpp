/* 
 * Author: Vishisht, Deepak
 * Netids: vmt28 and da475
 * Copyright @ 2018 Vishisht and Deepak. All rights reserved

 * Created on April 21, 2018, 11:06 PM
 * File: Circuit_Sim_1.cpp
 * Desc: Simple RC equations are implemented here. This class
 * calls ODE_Solvers to get the solution
 */

#include "Circuit_Sim_1.h"

// dx/dt implemented here
// Exception handling is done by all the Global_Functions
void Circuit_Sim_1::fx(arrayMatCol *x, double t, arrayMatCol *result)
{  
    arrayMatCol *firstTerm = new arrayMatCol();
    arrayMatCol *lastTerm = new arrayMatCol();
    
    double C = 1e-12;
    double R = 10e3;
    
    double matCR[4] = {-((1/(R*C)) + (1/(R*C))), 1/(R*C), 1/(R*C), -((1/(R*C)) + (1/(R*C)))};
    fullMat *fullMatCR = new fullMat();
    Global_Functions::create_FullMat(matCR, fullMatCR, x->rank);
    Global_Functions::matrix_Vector_Product(fullMatCR, x, firstTerm);
    
    double i;
    t = fmod(t,20e-9);
    t *= 1e9;

    if (t < 1) i = 0.1e-3 * t;
    else if (t >= 1 && t <= 10) i = 0.1e-3;
    else if (t > 10 && t < 11) i = (-0.1e-3 * t) + 1.1e-3;
    else if (t >= 11) i = 0;

    lastTerm->rank = x->rank;
    lastTerm->col = (double *)calloc(x->rank, sizeof(double));
    lastTerm->col[0] = i/C;
    
    Global_Functions::column_Addition(firstTerm, lastTerm, result);
}

// Constructor
Circuit_Sim_1::Circuit_Sim_1(double Step)
{
    double start = 0;
    double stop = 100e-9;
    double step = Step * 1e-9;
    double rank = 2;
    double initialValue = 0;
    
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
Circuit_Sim_1::~Circuit_Sim_1()
{
}