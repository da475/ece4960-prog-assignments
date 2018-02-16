/* 
 * File:   Gradual_Underflow.cpp
 * Author: Deepak, Vishisht
 *
 * Created on February 12, 2018, 7:17 PM
 */

// Include common header
#include "Assignment1_Header.h"


// Underflow using sin
void Gradual_Underflow::underFlow_Using_Sin() 
{
    cout << "Value of sin(1.23456789012345x)/x where x is +0 is: " << Global_Functions::Check_For_Exceptions_Zeros(sin(temp*POSZERO)/POSZERO) << endl;
}

// Underflow using x - y
void Gradual_Underflow::x_minus_y() 
{
    float base1 = 4.50;
    float base2 = 4.51;
    double x = base1 * pow(10, -300); 
    double y = base2 * pow(10, -300); 

    cout << endl << endl << "Test for gradual underflow by using (X-Y) operation" << endl;

    int i=0;
    for(i=0; i<40; i++) 
    {
        // Check if gradual underflow is supported
        if((x != y) && (x-y == 0)) {
            cout << "Gradual underflow or Soft Landing not supported" << endl;
        }

        if(x - y == 0 && (x == y)) {
            cout << "Hit for iteration " << i << endl;
            break;
        }

        x = x/10;
        y = y/10;

    }

    cout << "X and Y were initially set to 4.50e-300 and 4.51e-300 and their substraction (x-y) was calculated." << endl;
    cout << "Then both X and Y were divided by 10, so reach the minimum for double precision floating point" << endl;
    cout << "At iteration number " << i << ", both the conditions (X==Y) and (X-Y == 0) got true which means the gradual underflow is supported in MacOS" << endl << endl;

}

// Underflow using x/y
void Gradual_Underflow::x_div_y() 
{
    float base1 = 4.50;
    float base2 = 4.51;
    double x = base1 * pow(10, -300); 
    double y = base2 * pow(10, -300);

    cout << endl << endl << "Test for gradual undeflow by using (X/Y) operation" << endl;

    int i=0;
    for(i=0; i<40; i++) 
    {
        // Check if gradual underflow is supported
        if(x / y == 0) {
            cout << "Hit for iteration " << i << endl;
            break;
        }

        x = x/20;
        y = y/10;
    }

    cout << "X and Y were initially set to 4.50e-300 and 4.51e-300 and their division (x/y) was calculated." << endl;
    cout << "Then both X was divided by 20, and Y was divided by 10 so that they reach the minimum for double precision floating point" << endl;
    cout << "At iteration number " << i << ", both the conditions (X==Y) and (X-Y == 0) got true which means the gradual underflow is supported in MacOS" << endl << endl;

}

// Constructor for class
Gradual_Underflow::Gradual_Underflow() 
{
    temp = 1.234567890123456;
}
