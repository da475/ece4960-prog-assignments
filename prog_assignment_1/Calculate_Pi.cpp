/* 
 * File:   Calculate_Pi.cpp
 * Author: Deepak
 *
 * Created on February 12, 2018
 */

#include "Assignment1_Header.h"

void precision_30() {
    long double num1 = 640320;
    long double num2 = 744;

    cout.precision(30);
    long double numer = pow(num1, 3) + num2;
    long double logval = log(numer);
    cout << "num is " << numer << endl; 
    cout << "log is " << log(numer) << endl; 


    long double root_val = sqrt(163);
    long double pi_val = logval / root_val;
    cout << "root value " << root_val << endl;
    cout << "pi value " << pi_val << endl;

}