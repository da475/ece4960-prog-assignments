/*
 * Author: Vishisht Tiwari, Deepak Agarwal
 * Netids: vmt28 and da475
 * Copyright @ 2018 Vishisht Tiwari and Deepak Agarwal. All rights reserved

 * Created on May 15, 2018, 7:27 PM
 * File: ODE_Solvers.h
 * Desc: Forward Euler, Runge Kutta 34 and 
 *       Time Adaptive Runge Kutta functions
 */

#include "Assignment_5_Header.h"

#ifndef ODE_SOLVERS_H
#define ODE_SOLVERS_H

class ODE_Solvers
{
public:
    void rungeKutta(arrayMat *valuesOriginal, fullVect*timeOiginal, int typeRK, int typeTimeSteps = 0, bool adapt = false);
    
    ODE_Solvers(double initialValue, fullVect *time, fullVect *delT, double start, double stop, double step, void(*func)(arrayMatCol*,double,arrayMatCol*,double), double order = 1);
    virtual ~ODE_Solvers();
private:
    double initialValue;
    fullVect *time;
    fullVect *delT;
    double start;
    double stop;
    double step;
    void(*func)(arrayMatCol*,double,arrayMatCol*,double);
    double order;
    
    void initializeValue(arrayMat *values);
    
    void rk1(arrayMatCol *k1, arrayMatCol *value, double time);
    void rk2(arrayMatCol *k2, arrayMatCol *value, double time, double delT, arrayMatCol *k1);
    void rk3(arrayMatCol *k3, arrayMatCol *value, double time, double delT, arrayMatCol *k2);
    void rk4(arrayMatCol *k4, arrayMatCol *value, double time, double delT, arrayMatCol *k3);
    
    double newTimeSteps(arrayMatCol *err_estimate, arrayMatCol *value, double delT, int typeTimeSteps);
    
    void nextTimeSteps(int rank, arrayMatCol *k1, arrayMatCol *k2, arrayMatCol *k3, arrayMatCol *k4, vector<arrayMatCol*> *values, vector<double> *time, vector<double> *delT, int iter, int typeRK, int typeTimeSteps);
};

#endif /* ODE_SOLVERS_H */

