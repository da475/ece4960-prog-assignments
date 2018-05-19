/* 
 * Author: Vishisht Tiwari, Deepak Agarwal
 * Netids: vmt28 and da475
 * Copyright @ 2018 Vishisht Tiwari and Deepak Agarwal. All rights reserved

 * Created on May 15, 2018, 11:24 PM
 * File: Circuit_Sim.cpp
 * Desc: CS Amplifier equations are implemented here. This class
 * calls ODE_Solvers to get the solution
 */

#include "Circuit_Sim.h"

// dx/dt implemented here
// Exception handling is done by all the Global_Functions
void Circuit_Sim::fx(arrayMatCol *x, double t, arrayMatCol *result, double order)
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
    t = fmod(t,order*(20e-9));
    t *= (order*1e9);

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
Circuit_Sim::Circuit_Sim(double Step, double order)
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
    ODE_Solvers *solver = new ODE_Solvers(initialValue, time, delT, start, stop, step, fx, order);
    
    // Solving ODE Using Forward Euler
    Global_Functions::create_Time_Values(start, stop, step, rank, calculatedValues, time, delT);
    
    // Record start time
    auto startTime= chrono::high_resolution_clock::now();
    
    // Solving ODE Using RK23 Without Time Adaptivity
    cout << endl << endl << endl << "-------------- Solving ODE Using RK23 Without Time Adaptivity --------------" << endl << endl;
    solver->rungeKutta(calculatedValues, time, TWOTHREE);
    
    #if WRITE_VALUES
        Global_Functions::write_Comparison(time, calculatedValues, "Solving Amplifier ODE Using RK23 Without Time Adaptivity", step, order);
    #endif
    #if PRINT_VALUES
        Global_Functions::print_Comparison(time, calculatedValues);
    #endif
    
    
    // Record end time
    auto finishTime = chrono::high_resolution_clock::now();
    
    chrono::duration<double> elapsed = 1000 * (finishTime - startTime);
    cout << "Elapsed time: " << elapsed.count() << " ms\n";
    
    // Record start time
    startTime= chrono::high_resolution_clock::now();
    
    // Solving ODE Using RK23 With Time Adaptivity Using Bisection
    cout << endl << endl << endl << "-------------- Solving ODE Using RK23 With Time Adaptivity Using Bisection --------------" << endl << endl;
    solver->rungeKutta(calculatedValues, time, TWOTHREE, BISECTION, true);
    
    #if WRITE_VALUES
        Global_Functions::write_Comparison(time, calculatedValues, "Solving Amplifier ODE Using RK23 With Time Adaptivity Using Bisection", step, order);
    #endif
    #if PRINT_VALUES
        Global_Functions::print_Comparison(time, calculatedValues);
    #endif
    
    // Record end time
    finishTime = chrono::high_resolution_clock::now();
    
    elapsed = 1000 * (finishTime - startTime);
    cout << "Elapsed time: " << elapsed.count() << " ms\n";
    
    // Record start time
    startTime= chrono::high_resolution_clock::now();
    
    // Solving ODE Using RK23 With Time Adaptivity Using Constant E.h
    cout << endl << endl << endl << "-------------- Solving ODE Using RK23 With Time Adaptivity Using Constant E.h --------------" << endl << endl;
    solver->rungeKutta(calculatedValues, time, TWOTHREE, CONSTANT_E_H, true);
    
    #if WRITE_VALUES
        Global_Functions::write_Comparison(time, calculatedValues, "Solving Amplifier ODE Using RK23 With Time Adaptivity Using Constant E.h", step, order);
    #endif
    #if PRINT_VALUES
        Global_Functions::print_Comparison(time, calculatedValues);
    #endif
    
    // Record end time
    finishTime = chrono::high_resolution_clock::now();
    
    elapsed = 1000 * (finishTime - startTime);
    cout << "Elapsed time: " << elapsed.count() << " ms\n";
    
    // Record start time
    startTime= chrono::high_resolution_clock::now();
    
    // Solving ODE Using RK23 With Time Adaptivity Using O(h)
    cout << endl << endl << endl << "-------------- Solving ODE Using RK23 With Time Adaptivity Using O(h) --------------" << endl << endl;
    solver->rungeKutta(calculatedValues, time, TWOTHREE, USE_O_H, true);
    
    #if WRITE_VALUES
        Global_Functions::write_Comparison(time, calculatedValues, "Solving Amplifier ODE Using RK23 With Time Adaptivity Using O(h)", step, order);
    #endif
    #if PRINT_VALUES
        Global_Functions::print_Comparison(time, calculatedValues);
    #endif
    
    // Record end time
    finishTime = chrono::high_resolution_clock::now();
    
    elapsed = 1000 * (finishTime - startTime);
    cout << "Elapsed time: " << elapsed.count() << " ms\n";
    
    // Record start time
    startTime= chrono::high_resolution_clock::now();
    
    // Solving ODE Using RK34 Without Time Adaptivity
    cout << endl << endl << endl << "-------------- Solving ODE Using RK34 Without Time Adaptivity --------------" << endl << endl;
    solver->rungeKutta(calculatedValues, time, THREEFOUR);
    
    #if WRITE_VALUES
        Global_Functions::write_Comparison(time, calculatedValues, "Solving Amplifier ODE Using RK34 Without Time Adaptivity", step, order);
    #endif
    #if PRINT_VALUES
        Global_Functions::print_Comparison(time, calculatedValues);
    #endif
    
    // Record end time
    finishTime = chrono::high_resolution_clock::now();
    
    elapsed = 1000 * (finishTime - startTime);
    cout << "Elapsed time: " << elapsed.count() << " ms\n";
    
    // Record start time
    startTime= chrono::high_resolution_clock::now();
    
    // Solving ODE Using RK34 With Time Adaptivity Using Bisection
    cout << endl << endl << endl << "-------------- Solving ODE Using RK34 With Time Adaptivity Using Bisection --------------" << endl << endl;
    solver->rungeKutta(calculatedValues, time, THREEFOUR, BISECTION, true);
    
    #if WRITE_VALUES
        Global_Functions::write_Comparison(time, calculatedValues, "Solving Amplifier ODE Using RK34 With Time Adaptivity Using Bisection", step, order);
    #endif
    #if PRINT_VALUES
        Global_Functions::print_Comparison(time, calculatedValues);
    #endif
    
    // Record end time
    finishTime = chrono::high_resolution_clock::now();
    
    elapsed = 1000 * (finishTime - startTime);
    cout << "Elapsed time: " << elapsed.count() << " ms\n";
    
    // Record start time
    startTime= chrono::high_resolution_clock::now();
    
    // Solving ODE Using RK34 With Time Adaptivity Using Constant E.h
    cout << endl << endl << endl << "-------------- Solving ODE Using RK34 With Time Adaptivity Using Constant E.h --------------" << endl << endl;
    solver->rungeKutta(calculatedValues, time, THREEFOUR, CONSTANT_E_H, true);
    #if WRITE_VALUES
        Global_Functions::write_Comparison(time, calculatedValues, "Solving Amplifier ODE Using RK34 With Time Adaptivity Using Constant E.h", step, order);
    #endif
    #if PRINT_VALUES
        Global_Functions::print_Comparison(time, calculatedValues);
    #endif
    
    // Record end time
    finishTime = chrono::high_resolution_clock::now();
    
    elapsed = 1000 * (finishTime - startTime);
    cout << "Elapsed time: " << elapsed.count() << " ms\n";
    
    // Record start time
    startTime= chrono::high_resolution_clock::now();
    
    // Solving ODE Using RK34 With Time Adaptivity Using O(h)
    cout << endl << endl << endl << "-------------- Solving ODE Using RK34 With Time Adaptivity Using O(h) --------------" << endl << endl;
    solver->rungeKutta(calculatedValues, time, THREEFOUR, USE_O_H, true);
    
    #if WRITE_VALUES
        Global_Functions::write_Comparison(time, calculatedValues, "Solving Amplifier ODE Using RK34 With Time Adaptivity Using O(h)", step, order);
    #endif
    #if PRINT_VALUES
        Global_Functions::print_Comparison(time, calculatedValues);
    #endif
    
    // Record end time
    finishTime = chrono::high_resolution_clock::now();
    
    elapsed = 1000 * (finishTime - startTime);
    cout << "Elapsed time: " << elapsed.count() << " ms\n";
}

// Destructor
Circuit_Sim::~Circuit_Sim()
{
}