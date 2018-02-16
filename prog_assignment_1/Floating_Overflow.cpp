/* 
 * File:   Floating_Overflow.cpp
 * Author: Deepak, Vishisht
 *
 * Created on February 12, 2018, 4:50 PM
 */

#include "Assignment1_Header.h"

void Floating_Overflow::TestPowerIterations() 
{
    double result = 1;
    int power = 0;
    feclearexcept(FE_OVERFLOW);
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


    // Maybe by several checks he means factorial fibonacci etc.


}