/*
 * To cdelTange tdelTis license delTeader, cdelToose License Headers in Project Properties.
 * To cdelTange tdelTis template file, cdelToose Tools | Templates
 * and open tdelTe template in tdelTe editor.
 */

/* 
 * File:   ODE_Solvers.cpp
 * AutdelTor: VisdelTisdelTt
 * 
 * Created on April 18, 2018, 5:19 PM
 */

#include "ODE_Solvers.h"

ODE_Solvers::ODE_Solvers() {
}

double error(double actual, double calculated) {
    return 100 * abs((actual - calculated)/actual);
}

void ODE_Solvers::forward_Euler(double x0, double start, double end, double delT, double(*fx)(double,double), double(*x)(double)) {
    double currX = x0;
    double nextX;
    for (int t = start + delT; t <= end; t += delT) {
        nextX = currX + (fx(currX, t) * delT);
        cout << nextX << " " << x(t) << endl;
        currX = nextX;
    }
    cout << endl;
}

void ODE_Solvers::backward_Euler(double x0, double start, double end, double delT, double(*fx)(double,double), double(*x)(double)) {
    double currX = x0;
    double nextX, fEuler;
    for (double t = start + delT; t <= end; t += delT) {
        fEuler = currX + (fx(currX, t - delT) * delT);
        nextX = currX + (fx(fEuler, t) * delT);
        cout << nextX << " " << x(t) << endl;
        currX = nextX;
    }
    cout << endl;
}

void ODE_Solvers::trapezoidal_Euler(double x0, double start, double end, double delT, double(*fx)(double,double), double(*x)(double)) {
    double currX = x0;
    double nextX, fEuler, bEuler;
    for (double t = start + delT; t <= end; t += delT) {
        fEuler = fx(currX, t - delT);
        bEuler = fx(fEuler, t);
        nextX = currX + (((fEuler + bEuler)/2) * delT);
        cout << nextX << " " << x(t) << endl;
        currX = nextX;
    }
    cout << endl;
}

double ODE_Solvers::new_TimeSteps(double err_estimate, double x, double delT, double rel_tol) {
    double numerator = rel_tol;
    double denominator = abs(err_estimate)/abs(x);
    return delT * cbrt(numerator/denominator);
}

void ODE_Solvers::rk34_Without_Time_Adaptivity(double x0, double delT, double(*fx)(double,double), double(*x)(double)) {
    double currX = x0;
    double k1, k2, k3, k4;
    for (double t = 0; t <= 5; t += delT) {
        k1 = fx(currX,t);
        k2 = fx(currX + (0.5 * delT * k1),t + (0.5 * delT));
        k3 = fx(currX + (0.75 * delT * k2),t + (0.75 * delT));
        k4 = fx(currX + (delT * k3), t + delT);
        currX =  currX + ((7 * k1) + (6 * k2) + (8 * k3) + (3 * k4)) * delT/24;
        cout << currX << " " << x(t + delT) << endl;
    }
    cout << endl;
}

void ODE_Solvers::rk34_With_Time_Adaptivity(double x0, double delT, double(*fx)(double,double), double(*x)(double)) {
    double currX = x0;
    double k1, k2, k3, k4;
    double err_estimate;
    for (double t = 0; t <= 5; t += delT) {
        k1 = fx(currX,t);
        k2 = fx(currX + (0.5 * delT * k1),t + (0.5 * delT));
        k3 = fx(currX + (0.75 * delT * k2),t + (0.75 * delT));
        k4 = fx(currX + (delT * k3), t + delT);
        currX =  currX + ((7 * k1) + (6 * k2) + (8 * k3) + (3 * k4)) * delT/24;
        cout << currX << " " << x(t + delT) << endl;
        err_estimate = ((-5 * k1) + (6 * k2) + (8 * k3) - (9 * k4)) * delT/72;
        delT = new_TimeSteps(err_estimate, currX, delT, 1e-2);
    }
    cout << endl;
}


ODE_Solvers::~ODE_Solvers() {
}

