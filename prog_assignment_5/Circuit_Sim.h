/* 
 * Author: Vishisht Tiwari, Deepak Agarwal
 * Netids: vmt28 and da475
 * Copyright @ 2018 Vishisht Tiwari and Deepak Agarwal. All rights reserved

 * Created on May 15, 2018, 11:24 PM
 * File: Circuit_Sim.h
 * Desc: CS Amplifier equations are declared here.
 */

#include "Assignment_5_Header.h"
#include "ODE_Solvers.h"

#ifndef CIRCUIT_SIM_H
#define CIRCUIT_SIM_H

class Circuit_Sim
{
public:
    Circuit_Sim(double Step, double order = 1);
    virtual ~Circuit_Sim();
private:
    static void fx(arrayMatCol *x, double t, arrayMatCol *result, double order);
};

#endif /* CIRCUIT_SIM_H */