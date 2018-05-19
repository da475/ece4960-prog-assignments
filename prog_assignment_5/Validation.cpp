/* 
 * Author: Vishisht Tiwari, Deepak Agarwal
 * Netids: vmt28 and da475
 * Copyright @ 2018 Vishisht Tiwari and Deepak Agarwal. All rights reserved

 * Created on May 15, 2018, 7:43 PM
 * File: Validation.cpp
 * Desc: Validation equations are implemented here. This class
 * calls ODE_Solvers to get the solution
 */

#include "Validation.h"

// dx/dt implemented here
// Exception handling is done by all the Global_Functions
void Validation::fx(arrayMatCol *x, double t, arrayMatCol *result, double order)
{   
    arrayMatCol *scaledX = new arrayMatCol();
    
    Global_Functions::column_Scaling(-0.5, x, scaledX);
    Global_Functions::column_Shifting(4 * exp(0.8 * t), scaledX, result);
}

// x at a given time can be found here
// Exception handling is done by all the Global_Functions
void Validation::true_Values(arrayMat *values, fullVect *time)
{
    if (values->dim != time->dim) throw UNMATCHED_DIM;

    int dim = values->dim;
    
    for (int i = 0; i < dim; i++)
    {
        double tempConst = ((4.0/1.3) * (exp(0.8 * time->arr[i]) - exp(-0.5 * time->arr[i]))) + (2 * exp(-0.5 * time->arr[i]));
        Global_Functions::column_Shifting(tempConst, values->arr[i], values->arr[i]);
    }
}
 // Constructor
Validation::Validation()
{
    double start = 0;
    double stop = 5;
    double step = 0.1;
    double rank = 1;
    double initialValue = 2;
    
    
    // Initialize the arrayMat and fullVect for values, time and delT
    arrayMat *trueValues1 = new arrayMat();
    arrayMat *calculatedValues = new arrayMat();
    fullVect *time = new fullVect();
    fullVect *delT = new fullVect();
    
    // Initialize the solver class
    ODE_Solvers *solver = new ODE_Solvers(initialValue, time, delT, start, stop, step, fx);
    
    // Solving ODE Using Forward Euler
    Global_Functions::create_Time_Values(start, stop, step, rank, trueValues1, time, delT);
    Global_Functions::create_Time_Values(start, stop, step, rank, calculatedValues, time, delT);
    
    // Record start time
    auto startTime= chrono::high_resolution_clock::now();
    
    // Solving ODE Using RK23 Without Time Adaptivity
    cout << endl << endl << endl << "-------------- Solving ODE Using RK23 Without Time Adaptivity --------------" << endl << endl;
    solver->rungeKutta(calculatedValues, time, TWOTHREE);
    Global_Functions::create_Values(rank, trueValues1, time);
    true_Values(trueValues1, time);
    #if WRITE_VALUES
        Global_Functions::write_Comparison(time, calculatedValues, "Solving Validation ODE Using RK23 Without Time Adaptivity", step, 1, trueValues1);
    #endif
    #if PRINT_VALUES
        Global_Functions::print_Comparison(time, calculatedValues, trueValues1);
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
    Global_Functions::create_Values(rank, trueValues1, time);
    true_Values(trueValues1, time);
    #if WRITE_VALUES
        Global_Functions::write_Comparison(time, calculatedValues, "Solving Validation ODE Using RK23 With Time Adaptivity Using Bisection", step, 1, trueValues1);
    #endif
    #if PRINT_VALUES
        Global_Functions::print_Comparison(time, calculatedValues, trueValues1);
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
    Global_Functions::create_Values(rank, trueValues1, time);
    true_Values(trueValues1, time);
    #if WRITE_VALUES
        Global_Functions::write_Comparison(time, calculatedValues, "Solving Validation ODE Using RK23 With Time Adaptivity Using Constant E.h", step, 1, trueValues1);
    #endif
    #if PRINT_VALUES
        Global_Functions::print_Comparison(time, calculatedValues, trueValues1);
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
    Global_Functions::create_Values(rank, trueValues1, time);
    true_Values(trueValues1, time);
    #if WRITE_VALUES
        Global_Functions::write_Comparison(time, calculatedValues, "Solving Validation ODE Using RK23 With Time Adaptivity Using O(h)", step, 1, trueValues1);
    #endif
    #if PRINT_VALUES
        Global_Functions::print_Comparison(time, calculatedValues, trueValues1);
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
    Global_Functions::create_Values(rank, trueValues1, time);
    true_Values(trueValues1, time);
    #if WRITE_VALUES
        Global_Functions::write_Comparison(time, calculatedValues, "Solving Validation ODE Using RK34 Without Time Adaptivity", step, 1, trueValues1);
    #endif
    #if PRINT_VALUES
        Global_Functions::print_Comparison(time, calculatedValues, trueValues1);
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
    Global_Functions::create_Values(rank, trueValues1, time);
    true_Values(trueValues1, time);
    #if WRITE_VALUES
        Global_Functions::write_Comparison(time, calculatedValues, "Solving Validation ODE Using RK34 With Time Adaptivity Using Bisection", step, 1, trueValues1);
    #endif
    #if PRINT_VALUES
        Global_Functions::print_Comparison(time, calculatedValues, trueValues1);
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
    Global_Functions::create_Values(rank, trueValues1, time);
    true_Values(trueValues1, time);
    #if WRITE_VALUES
        Global_Functions::write_Comparison(time, calculatedValues, "Solving Validation ODE Using RK34 With Time Adaptivity Using Constant E.h", step, 1, trueValues1);
    #endif    
    #if PRINT_VALUES
        Global_Functions::print_Comparison(time, calculatedValues, trueValues1);
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
    Global_Functions::create_Values(rank, trueValues1, time);
    true_Values(trueValues1, time);
    #if WRITE_VALUES
        Global_Functions::write_Comparison(time, calculatedValues, "Solving Validation ODE Using RK34 With Time Adaptivity Using O(h)", step, 1, trueValues1);
    #endif
    #if PRINT_VALUES
        Global_Functions::print_Comparison(time, calculatedValues, trueValues1);
    #endif

    // Record end time
    finishTime = chrono::high_resolution_clock::now();
    
    elapsed = 1000 * (finishTime - startTime);
    cout << "Elapsed time: " << elapsed.count() << " ms\n";
}

// Destructor
Validation::~Validation()
{
}