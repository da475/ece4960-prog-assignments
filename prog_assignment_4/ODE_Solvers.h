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
    void forward_Euler(double x0, double start, double end, double delT, double(*fx)(double,double),double(*x)(double));
    void backward_Euler(double x0, double start, double end, double delT, double(*fx)(double,double), double(*x)(double));
    void trapezoidal_Euler(double x0, double start, double end, double delT, double(*fx)(double,double), double(*x)(double));
    void rk34_Without_Time_Adaptivity(double x0, double delT, double(*fx)(double,double), double(*x)(double));
    void rk34_With_Time_Adaptivity(double x0, double delT, double(*fx)(double,double), double(*x)(double));
    double new_TimeSteps(double error_estimate, double x, double delT, double rel_tol);
    ODE_Solvers();
    double error(double actual, double calculated);
    virtual ~ODE_Solvers();
private:

};

#endif /* ODE_SOLVERS_H */

