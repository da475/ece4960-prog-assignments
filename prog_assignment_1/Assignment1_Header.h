/* 
 * File:   Assignment1_Header.h
 * Author: Deepak, Vishisht
 *
 * Created on February 15, 2018, 10:01 PM
 */

// Including all classes
#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <cstdlib>
#include <cmath>
#include <cfenv>
#include <string.h>

#ifndef ASSIGNMENT1_HEADER_H
#define ASSIGNMENT1_HEADER_H

// Defining constants
#define INT_VAL_MAX 2147483647
#define INT_VAL_MIN -2147483647

using namespace std;

// Global Variables
extern double INF;
extern double NINF;
extern double NANVAL;
extern double POSZERO;
extern double NEGZERO;

// Global Functions
class Global_Functions
{
private:
public:
    // Function for checking exceptions or signed zero
    static string Check_For_Exceptions_Zeros(double x) {
        if (x > numeric_limits<double>::max() && x > 0) return "Positive Infinity";
        if (x < -numeric_limits<double>::max() && x < 0) return "Negative Infinity";
        if (x != x) return "NAN";
        if (x == 0.0 && !signbit(x)) return "Positive Zero";
        if (x == 0.0 && signbit(x)) return "Negative Zero";
        // If none of the other exceptions occurred then return the string
        return (to_string(x) + " which is neither an exception nor signed zero");
    }
};

// Declaration of Integer_Overflow class
class Integer_Overflow
{
private:
public:
    void TestMult(int num);
    void TestFact();
    void TestFibonacci();
    void DivbyZero();
};

// Declaration of Floating_Overflow class
class Floating_Overflow
{
private:   
public:
    void TestPowerIterationsUsingFlag();
    void TestPowerIterationsUsingDivision();
};

// Declaration of Floating_Operations class
class Floating_Operations{
private:   
public:
    void INF_Operations();
    void NINF_Operations();
    void NAN_Operations();
    void Prop_And_Interaction();
    Floating_Operations();
};

// Declaration of Signed_Zero class
class Signed_Zero{
private:
public:
    void Log_Operations();
    void Sinc_Operations();
    void Sinc_With_Absolute_Operations();
    Signed_Zero();
};

// Declaration of Gradual_Underflow class
class Gradual_Underflow{
private:
    double temp;
public:
    void x_minus_y();
    void x_div_y();
    void underFlow_Using_Sin();
    Gradual_Underflow();
};

class Calculate_Pi{
private: 
public:
    long double sqroot(long double);
    long double logcal(long double);
    long double precision_30();
};
#endif /* ASSIGNMENT1_HEADER_H */
