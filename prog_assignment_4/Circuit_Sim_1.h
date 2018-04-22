/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Circuit_Sim_1.h
 * Author: Vishisht
 *
 * Created on April 21, 2018, 11:06 PM
 */

#include "Assignment_4_Header.h"
#include "ODE_Solvers.h"

#ifndef CIRCUIT_SIM_1_H
#define CIRCUIT_SIM_1_H

class Circuit_Sim_1 {
public:
    Circuit_Sim_1(double Step);
    virtual ~Circuit_Sim_1();
private:
    static void fx(arrayMatCol *x, double t, arrayMatCol *result);
};

#endif /* CIRCUIT_SIM_1_H */

