/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Validation.h
 * Author: Vishisht
 *
 * Created on May 15, 2018, 7:43 PM
 */

/* 
 * Author: Vishisht Tiwari, Deepak Agarwal
 * Netids: vmt28 and da475
 * Copyright @ 2018 Vishisht Tiwari and Deepak Agarwal. All rights reserved

 * Created on May 15, 2018, 7:43 PM
 * File: Validation.h
 * Desc: Validation equations are declared here.
 */

#include "Assignment_5_Header.h"
#include "ODE_Solvers.h"

#ifndef VALIDATION_H
#define VALIDATION_H

class Validation
{
public:
    Validation();
    virtual ~Validation();
private:
    static void fx(arrayMatCol *x, double t, arrayMatCol *result, double order);
    void true_Values(arrayMat *values, fullVect *time);
};

#endif /* VALIDATION_H */

