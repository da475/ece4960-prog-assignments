/* 
 * File:   Signed_Zero.cpp
 * Author: Vishisht, Deepak
 *
 * Created on February 12, 2018, 5:15 PM
 */

// Include the common header
#include "Assignment1_Header.h"

// Log operations on signed 0
void Signed_Zero::Log_Operations() {
    cout << "Value of log(x) where x is +0 is: " << Global_Functions::Check_For_Exceptions_Zeros(log(POSZERO)) << endl;
    cout << "Value of log(x) where x is -0 is: " << Global_Functions::Check_For_Exceptions_Zeros(log(NEGZERO)) << endl;
    cout << endl;
}

// Sinc operations on signed 0
void Signed_Zero::Sinc_Operations() {
    cout << "Value of sin(x)/x where x is +0 is: " << Global_Functions::Check_For_Exceptions_Zeros(sin(POSZERO)/POSZERO) << endl;
    cout << "Value of sin(x)/x where x is -0 is: " << Global_Functions::Check_For_Exceptions_Zeros(sin(NEGZERO)/NEGZERO) << endl;
    cout << endl;
}

// Sinc with absolute value operations on signed 0
void Signed_Zero::Sinc_With_Absolute_Operations() {
    cout << "Value of sin(x)/|x| where x is +0 is: " << Global_Functions::Check_For_Exceptions_Zeros(sin(POSZERO)/abs(POSZERO)) << endl;
    cout << "Value of sin(x)/|x| where x is -0 is: " << Global_Functions::Check_For_Exceptions_Zeros(sin(NEGZERO)/abs(NEGZERO)) << endl;
    cout << endl;
}

// Constructor
Signed_Zero::Signed_Zero() {
    // Check for positive zero
    if (Global_Functions::Check_For_Exceptions_Zeros(POSZERO) == "Positive Zero") 
    {
        cout << "Positive Zero value has been detected and tested after generation" << endl;
    }
    else
    {
        cout << "The number used for Positive Zero operations is not Positive Zero. The program will exit now." << endl;
        exit (EXIT_FAILURE);
    }

    // Check for negative zero
    if (Global_Functions::Check_For_Exceptions_Zeros(NEGZERO) == "Negative Zero") 
    {
        cout << "Negative Zero value has been detected and tested after generation" << endl;
    }
    else
    {
        cout << "The number used for Negative Zero operations is not Negative Zero. The program will exit now." << endl;
        exit (EXIT_FAILURE);
    }
}
