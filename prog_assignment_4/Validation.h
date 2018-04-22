/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Validation.h
 * Author: Vishisht
 *
 * Created on April 21, 2018, 10:03 PM
 */

#include "Assignment_4_Header.h"
#include "ODE_Solvers.h"

#ifndef VALIDATION_H
#define VALIDATION_H

class Validation {
public:
    Validation();
    virtual ~Validation();
private:
    static void fx(arrayMatCol *x, double t, arrayMatCol *result);
    void true_Values(arrayMat *values, fullVect *time);
};

#endif /* VALIDATION_H */

