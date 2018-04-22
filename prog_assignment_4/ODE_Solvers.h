/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ODE_Solvers.h
 * Author: Vishisht
 *
 * Created on April 18, 2018, 5:19 PM
 */

#include "Assignment_4_Header.h"

#ifndef ODE_SOLVERS_H
#define ODE_SOLVERS_H

class ODE_Solvers {
public:
    void true_Values(arrayMat *values, fullVect *time);
    void initializeValue(double initialValues, arrayMat *values);
    void forward_Euler(double initialValues, arrayMat *values, fullVect *time, fullVect *delT, void(*func)(arrayMatCol*,double,arrayMatCol*));
    void rk34_K1(arrayMatCol *k1, arrayMatCol *value, double time, void(*func)(arrayMatCol*,double,arrayMatCol*));
    void rk34_K2(arrayMatCol *k2, arrayMatCol *value, double time, double delT, arrayMatCol *k1, void(*func)(arrayMatCol*,double,arrayMatCol*));
    void rk34_K3(arrayMatCol *k3, arrayMatCol *value, double time, double delT, arrayMatCol *k2, void(*func)(arrayMatCol*,double,arrayMatCol*));
    void rk34_K4(arrayMatCol *k4, arrayMatCol *value, double time, double delT, arrayMatCol *k3, void(*func)(arrayMatCol*,double,arrayMatCol*));
    void rk34_Without_Adapt(double initialValue, arrayMat *values, fullVect *time, fullVect *delT, void(*func)(arrayMatCol*,double,arrayMatCol*));
    /*
    void forward_Euler(double initialValue, arrayMat *values, arrayMat *time, arrayMat *delT, double(*func)(double,double));
    double rk34_K1(double value, double time, double(*func)(double, double));
    double rk34_K2(double value, double time, double delT, double k1, double(*func)(double, double));
    double rk34_K3(double value, double time, double delT, double k2, double(*func)(double, double));
    double rk34_K4(double value, double time, double delT, double k3, double(*func)(double, double));
    double new_TimeSteps(double err_estimate, double x, double delT, double rel_tol, double abs_tol);
    void rk34_Without_Adapt(double initialValue, arrayMat *values, arrayMat *time, arrayMat *delT, double(*func)(double, double));
    void rk34_With_Adapt(double initialValue, arrayMat *values, arrayMat *time, arrayMat *delT, double(*func)(double, double));
    */
    ODE_Solvers();
    virtual ~ODE_Solvers();
private:

};

#endif /* ODE_SOLVERS_H */

