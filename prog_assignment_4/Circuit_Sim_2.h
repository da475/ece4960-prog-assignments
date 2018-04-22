/* 
 * Author: Vishisht, Deepak
 * Netids: vmt28 and da475
 * Copyright @ 2018 Vishisht and Deepak. All rights reserved

 * Created on April 21, 2018, 11:06 PM
 * File: Circuit_Sim_2.h
 * Desc: CS Amplifier equations are declared here.
 */

#include "Assignment_4_Header.h"
#include "ODE_Solvers.h"

#ifndef CIRCUIT_SIM_2_H
#define CIRCUIT_SIM_2_H

class Circuit_Sim_2
{
public:
    Circuit_Sim_2(double Step);
    virtual ~Circuit_Sim_2();
private:
    static void fx(arrayMatCol *x, double t, arrayMatCol *result);
};

#endif /* CIRCUIT_SIM_2_H */