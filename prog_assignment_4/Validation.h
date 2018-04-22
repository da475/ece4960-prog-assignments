/* 
 * Author: Vishisht, Deepak
 * Netids: vmt28 and da475
 * Copyright @ 2018 Vishisht and Deepak. All rights reserved

 * Created on April 21, 2018, 10:03 PM
 * File: Validation.h
 * Desc: Validation equations are declared here.
 */

#include "Assignment_4_Header.h"
#include "ODE_Solvers.h"

#ifndef VALIDATION_H
#define VALIDATION_H

class Validation
{
public:
    Validation();
    virtual ~Validation();
private:
    static void fx(arrayMatCol *x, double t, arrayMatCol *result);
    void true_Values(arrayMat *values, fullVect *time);
};

#endif /* VALIDATION_H */

