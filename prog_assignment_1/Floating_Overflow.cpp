/* 
 * File:   Floating_Overflow.cpp
 * Author: Vishisht, Deepak
 *
 * Created on February 12, 2018, 4:50 PM
 */

// Including common header
#include "Assignment1_Header.h"

// Following function checks the flag for finding floating overflow
void Floating_Overflow::TestPowerIterationsUsingFlag() 
{
    cout << endl << endl << "Floating Overflow : USING FLAG" << endl;
    double result = 1;
    int power = 0;
    // Clears the flag
    feclearexcept(FE_OVERFLOW);
    // CHecks if overflow flag is raised
    while (fetestexcept(FE_OVERFLOW) == 0) 
    {
        power++;
        result *= 10;
        if (fetestexcept(FE_OVERFLOW) != 0) 
        {
            cout << "At " << power << "th iteration, the floating point overflowed" << endl;
            cout << "Hence double overflowed at 10^" << power << " value" << endl;
        }
    }
    cout << endl;
}

// Following function checks the division to see if flag is raised
void Floating_Overflow::TestPowerIterationsUsingDivision() 
{
    cout << endl << endl << "Floating Overflow : USING DIVISION" << endl;
    double result = 1;
    double prevResult = 1;
    int power = 0;
    bool overflown = false;
    // Checks if overflow has occurred
    while (!overflown) 
    {
        power++;
        result *= 10;
        // It checks both the values between type casted value of 0.99 is 0
        if ((int)((result/10)/prevResult) != 1 && (int)((result/10)/prevResult) != 0)
        {
            cout << "At " << power << "th iteration, the floating point overflowed" << endl;
            cout << "Hence double overflowed at 10^" << power << " value" << endl;
            overflown = true;
        }
        prevResult = result;
    }
    cout << endl;
}