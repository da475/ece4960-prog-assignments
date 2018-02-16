/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Assignment1_Header.h
 * Author: Vishisht
 *
 * Created on February 15, 2018, 10:01 PM
 */
#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <cstdlib>
#include <cmath>
#include <cfenv>
#include <string.h>

#ifndef ASSIGNMENT1_HEADER_H
#define ASSIGNMENT1_HEADER_H

#define INT_VAL_MAX 2147483647

using namespace std;

extern double INF;
extern double NINF;
extern double NANVAL;
extern double POSZERO;
extern double NEGZERO;

class Global_Functions
{
private:
public:
    static string Check_For_Exceptions_Zeros(double x) {
        if (isinf(x) && !signbit(x)) return "Positive Infinity";
        if (isinf(x) && signbit(x)) return "Negative Infinity";
        if (isnan(x)) return "NAN";
        if (x == 0.0 && !signbit(x)) return "Positive Zero";
        if (x == 0.0 && signbit(x)) return "Negative Zero";
        return "Neither Positive Infinity, nor Negative Infinity nor NAN nor 0";
    }
};


#endif /* ASSIGNMENT1_HEADER_H */

