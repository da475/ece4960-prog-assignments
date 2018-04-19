/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Assignment_4_Main.cpp
 * Author: Vishisht
 *
 * Created on April 18, 2018, 5:54 PM
 */

#include "Assignment_4_Header.h"
#include "ODE_Solvers.h"
/*
 * 
 */

double fx(double x, double t) {
    return (4 * exp(0.8 * t)) - (0.5 * x);
}

double x(double t) {
    return ((4/1.3) * (exp(0.8*t) - exp(-0.5*t))) + (2 * exp(-0.5*t));
}


int main(int argc, char** argv) {
    
    ODE_Solvers *solvers = new ODE_Solvers();
    solvers->forward_Euler(2,0,5,1,fx,x);
    solvers->backward_Euler(2,0,5,1,fx,x);
    solvers->trapezoidal_Euler(2,0,5,1,fx,x);
    solvers->rk34_Without_Time_Adaptivity(2, 1, fx, x);
    solvers->rk34_With_Time_Adaptivity(2, 1, fx, x);

    return 0;
}

