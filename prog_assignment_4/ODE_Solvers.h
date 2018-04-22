/* 
 * Author: Vishisht, Deepak
 * Netids: vmt28 and da475
 * Copyright @ 2018 Vishisht and Deepak. All rights reserved

 * Created on April 18, 2018, 5:19 PM
 * File: ODE_Solvers.h
 * Desc: Forward Euler, Runge Kutta 34 and 
 *       Time Adaptive Runge Kutta functions
 */

#include "Assignment_4_Header.h"

#ifndef ODE_SOLVERS_H
#define ODE_SOLVERS_H

class ODE_Solvers
{
public:
    void true_Values(arrayMat *values, fullVect *time);
    void forward_Euler(arrayMat *values);
    void rk34(arrayMat *valuesOriginal, fullVect*timeOiginal, bool adapt = false);
    
    ODE_Solvers(double initialValue, fullVect *time, fullVect *delT, double start, double stop, double step, void(*func)(arrayMatCol*,double,arrayMatCol*));
    virtual ~ODE_Solvers();
private:
    double initialValue;
    fullVect *time;
    fullVect *delT;
    double start;
    double stop;
    double step;
    void(*func)(arrayMatCol*,double,arrayMatCol*);
    
    void initializeValue(arrayMat *values);
    
    void rk34_K1(arrayMatCol *k1, arrayMatCol *value, double time);
    void rk34_K2(arrayMatCol *k2, arrayMatCol *value, double time, double delT, arrayMatCol *k1);
    void rk34_K3(arrayMatCol *k3, arrayMatCol *value, double time, double delT, arrayMatCol *k2);
    void rk34_K4(arrayMatCol *k4, arrayMatCol *value, double time, double delT, arrayMatCol *k3);
    
    double new_TimeSteps(arrayMatCol *err_estimate, arrayMatCol *value, double delT);
};

#endif /* ODE_SOLVERS_H */

