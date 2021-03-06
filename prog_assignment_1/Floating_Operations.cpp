/* 
 * File:   Floating_Operations.cpp
 * Author: Vishisht, Deepak
 *
 * Created on February 12, 2018, 4:53 PM
 */

// Including common header
#include "Assignment1_Header.h"

// Initializing the global variables
double INF = 1.0/0.0;
double NINF = -INF;
double NANVAL = INF * 0.0;
double POSZERO = 1/INF;
double NEGZERO = 1/NINF;

// operations on infinity to understand its behaviour
void Floating_Operations::INF_Operations() {
    cout << endl << endl << "Floating Operations : INFINITY" << endl;
    cout << "Value of 1/x where x is infinity is: " << Global_Functions::Check_For_Exceptions_Zeros(1/INF) << endl;
    cout << "Value of sin(x) where x is infinity is: " << Global_Functions::Check_For_Exceptions_Zeros(sin(INF)) << endl;
    cout << "Value of exp(x) where x is infinity is: " << Global_Functions::Check_For_Exceptions_Zeros(exp(INF)) << endl;
    cout << endl;
}

// operations on negative infinity to understand its behaviour
void Floating_Operations::NINF_Operations() {
    cout << endl << endl << "Floating Operations : NEGATIVE INFINITY" << endl;
    cout << "Value of 1/x where x is -infinity is: " << Global_Functions::Check_For_Exceptions_Zeros(1/NINF) << endl;
    cout << "Value of sin(x) where x is -infinity is: " << Global_Functions::Check_For_Exceptions_Zeros(sin(NINF)) << endl;
    cout << "Value of exp(x) where x is -infinity is: " << Global_Functions::Check_For_Exceptions_Zeros(exp(NINF)) << endl;
    cout << endl;
}

// operations on nan to understand its behaviour
void Floating_Operations::NAN_Operations() {
    cout << endl << endl << "Floating Operations : NAN" << endl;
    cout << "Value of 1/x where x is NAN is: " << Global_Functions::Check_For_Exceptions_Zeros(1/NANVAL) << endl;
    cout << "Value of sin(x) where x is NAN is: " << Global_Functions::Check_For_Exceptions_Zeros(sin(NANVAL)) << endl;
    cout << "Value of exp(x) where x is NAN is: " << Global_Functions::Check_For_Exceptions_Zeros(exp(NANVAL)) << endl;
    cout << endl;
}

// Propagation and Interaction of INF, NINF and NAN with each other and +0,-0
void Floating_Operations::Prop_And_Interaction() {
    cout << endl << endl << "Propagation and Interaction of INF, NINF and NAN with each other and +0,-0" << endl;
    cout << "Value of Positive Infinity + Positive Infinity is: " << Global_Functions::Check_For_Exceptions_Zeros(INF + INF) << endl;
    cout << "Value of Positive Infinity + Negative Infinity is: " << Global_Functions::Check_For_Exceptions_Zeros(INF + NINF) << endl;
    cout << "Value of Positive Infinity + NAN is: " << Global_Functions::Check_For_Exceptions_Zeros(INF + NANVAL) << endl;
    cout << "Value of Positive Infinity + Positive 0 is: " << Global_Functions::Check_For_Exceptions_Zeros(INF + POSZERO) << endl;
    cout << "Value of Positive Infinity + Negative 0 is: " << Global_Functions::Check_For_Exceptions_Zeros(INF + NEGZERO) << endl;
    cout << "Value of Positive Infinity - Positive Infinity is: " << Global_Functions::Check_For_Exceptions_Zeros(INF - INF) << endl;
    cout << "Value of Positive Infinity - Negative Infinity is: " << Global_Functions::Check_For_Exceptions_Zeros(INF - NINF) << endl;
    cout << "Value of Positive Infinity - NAN is: " << Global_Functions::Check_For_Exceptions_Zeros(INF - NANVAL) << endl;
    cout << "Value of Positive Infinity - Positive 0 is: " << Global_Functions::Check_For_Exceptions_Zeros(INF - POSZERO) << endl;
    cout << "Value of Positive Infinity - Negative 0 is: " << Global_Functions::Check_For_Exceptions_Zeros(INF - NEGZERO) << endl;
    cout << "Value of Positive Infinity * Positive Infinity is: " << Global_Functions::Check_For_Exceptions_Zeros(INF * INF) << endl;
    cout << "Value of Positive Infinity * Negative Infinity is: " << Global_Functions::Check_For_Exceptions_Zeros(INF * NINF) << endl;
    cout << "Value of Positive Infinity * NAN is: " << Global_Functions::Check_For_Exceptions_Zeros(INF * NANVAL) << endl;
    cout << "Value of Positive Infinity * Positive 0 is: " << Global_Functions::Check_For_Exceptions_Zeros(INF * POSZERO) << endl;
    cout << "Value of Positive Infinity * Negative 0 is: " << Global_Functions::Check_For_Exceptions_Zeros(INF * NEGZERO) << endl;
    cout << "Value of Positive Infinity / Positive Infinity is: " << Global_Functions::Check_For_Exceptions_Zeros(INF / INF) << endl;
    cout << "Value of Positive Infinity / Negative Infinity is: " << Global_Functions::Check_For_Exceptions_Zeros(INF / NINF) << endl;
    cout << "Value of Positive Infinity / NAN is: " << Global_Functions::Check_For_Exceptions_Zeros(INF / NANVAL) << endl;
    cout << "Value of Positive Infinity / Positive 0 is: " << Global_Functions::Check_For_Exceptions_Zeros(INF / POSZERO) << endl;
    cout << "Value of Positive Infinity / Negative 0 is: " << Global_Functions::Check_For_Exceptions_Zeros(INF / NEGZERO) << endl;
    cout << endl;
    cout << "Value of Negative Infinity + Positive Infinity is: " << Global_Functions::Check_For_Exceptions_Zeros(NINF + INF) << endl;
    cout << "Value of Negative Infinity + Negative Infinity is: " << Global_Functions::Check_For_Exceptions_Zeros(NINF + NINF) << endl;
    cout << "Value of Negative Infinity + NAN is: " << Global_Functions::Check_For_Exceptions_Zeros(NINF + NANVAL) << endl;
    cout << "Value of Negative Infinity + Positive 0 is: " << Global_Functions::Check_For_Exceptions_Zeros(NINF + POSZERO) << endl;
    cout << "Value of Negative Infinity + Negative 0 is: " << Global_Functions::Check_For_Exceptions_Zeros(NINF + NEGZERO) << endl;
    cout << "Value of Negative Infinity - Positive Infinity is: " << Global_Functions::Check_For_Exceptions_Zeros(NINF - INF) << endl;
    cout << "Value of Negative Infinity - Negative Infinity is: " << Global_Functions::Check_For_Exceptions_Zeros(NINF - NINF) << endl;
    cout << "Value of Negative Infinity - NAN is: " << Global_Functions::Check_For_Exceptions_Zeros(NINF - NANVAL) << endl;
    cout << "Value of Negative Infinity - Positive 0 is: " << Global_Functions::Check_For_Exceptions_Zeros(NINF - POSZERO) << endl;
    cout << "Value of Negative Infinity - Negative 0 is: " << Global_Functions::Check_For_Exceptions_Zeros(NINF - NEGZERO) << endl;
    cout << "Value of Negative Infinity * Positive Infinity is: " << Global_Functions::Check_For_Exceptions_Zeros(NINF * INF) << endl;
    cout << "Value of Negative Infinity * Negative Infinity is: " << Global_Functions::Check_For_Exceptions_Zeros(NINF * NINF) << endl;
    cout << "Value of Negative Infinity * NAN is: " << Global_Functions::Check_For_Exceptions_Zeros(NINF * NANVAL) << endl;
    cout << "Value of Negative Infinity * Positive 0 is: " << Global_Functions::Check_For_Exceptions_Zeros(NINF * POSZERO) << endl;
    cout << "Value of Negative Infinity * Negative 0 is: " << Global_Functions::Check_For_Exceptions_Zeros(NINF * NEGZERO) << endl;
    cout << "Value of Negative Infinity / Positive Infinity is: " << Global_Functions::Check_For_Exceptions_Zeros(NINF / INF) << endl;
    cout << "Value of Negative Infinity / Negative Infinity is: " << Global_Functions::Check_For_Exceptions_Zeros(NINF / NINF) << endl;
    cout << "Value of Negative Infinity / NAN is: " << Global_Functions::Check_For_Exceptions_Zeros(NINF / NANVAL) << endl;
    cout << "Value of Negative Infinity / Positive 0 is: " << Global_Functions::Check_For_Exceptions_Zeros(NINF / POSZERO) << endl;
    cout << "Value of Negative Infinity / Negative 0 is: " << Global_Functions::Check_For_Exceptions_Zeros(NINF / NEGZERO) << endl;
    cout << endl;
    cout << "Value of NAN + Positive Infinity is: " << Global_Functions::Check_For_Exceptions_Zeros(NANVAL + INF) << endl;
    cout << "Value of NAN + Negative Infinity is: " << Global_Functions::Check_For_Exceptions_Zeros(NANVAL + NINF) << endl;
    cout << "Value of NAN + NAN is: " << Global_Functions::Check_For_Exceptions_Zeros(NANVAL + NANVAL) << endl;
    cout << "Value of NAN + Positive 0 is: " << Global_Functions::Check_For_Exceptions_Zeros(NANVAL + POSZERO) << endl;
    cout << "Value of NAN + Negative 0 is: " << Global_Functions::Check_For_Exceptions_Zeros(NANVAL + NEGZERO) << endl;
    cout << "Value of NAN - Positive Infinity is: " << Global_Functions::Check_For_Exceptions_Zeros(NANVAL - INF) << endl;
    cout << "Value of NAN - Negative Infinity is: " << Global_Functions::Check_For_Exceptions_Zeros(NANVAL - NINF) << endl;
    cout << "Value of NAN - NAN is: " << Global_Functions::Check_For_Exceptions_Zeros(NANVAL - NANVAL) << endl;
    cout << "Value of NAN - Positive 0 is: " << Global_Functions::Check_For_Exceptions_Zeros(NANVAL - POSZERO) << endl;
    cout << "Value of NAN - Negative 0 is: " << Global_Functions::Check_For_Exceptions_Zeros(NANVAL - NEGZERO) << endl;
    cout << "Value of NAN * Positive Infinity is: " << Global_Functions::Check_For_Exceptions_Zeros(NANVAL * INF) << endl;
    cout << "Value of NAN * Negative Infinity is: " << Global_Functions::Check_For_Exceptions_Zeros(NANVAL * NINF) << endl;
    cout << "Value of NAN * NAN is: " << Global_Functions::Check_For_Exceptions_Zeros(NANVAL * NANVAL) << endl;
    cout << "Value of NAN * Positive 0 is: " << Global_Functions::Check_For_Exceptions_Zeros(NANVAL * POSZERO) << endl;
    cout << "Value of NAN * Negative 0 is: " << Global_Functions::Check_For_Exceptions_Zeros(NANVAL * NEGZERO) << endl;
    cout << "Value of NAN / Positive Infinity is: " << Global_Functions::Check_For_Exceptions_Zeros(NANVAL / INF) << endl;
    cout << "Value of NAN / Negative Infinity is: " << Global_Functions::Check_For_Exceptions_Zeros(NANVAL / NINF) << endl;
    cout << "Value of NAN / NAN is: " << Global_Functions::Check_For_Exceptions_Zeros(NANVAL / NANVAL) << endl;
    cout << "Value of NAN / Positive 0 is: " << Global_Functions::Check_For_Exceptions_Zeros(NANVAL / POSZERO) << endl;
    cout << "Value of NAN / Negative 0 is: " << Global_Functions::Check_For_Exceptions_Zeros(NANVAL / NEGZERO) << endl;
    cout << endl;

    cout << endl;
}

// Constructor
Floating_Operations::Floating_Operations() {

    // Check if positive infinity
    if (Global_Functions::Check_For_Exceptions_Zeros(INF) == "Positive Infinity")
    {
        cout << "Positive Infinity value has been detected and tested after generation" << endl;
    }
    else
    {
        cout << "The number used for testing positive infinity operations is not positive infinity. The program will exit now." << endl;
        exit (EXIT_FAILURE);
    }
    // Check if negative infinity
    if (Global_Functions::Check_For_Exceptions_Zeros(NINF) == "Negative Infinity")
    {
        cout << "Negative Infinity value has been detected and tested after generation" << endl;
    }
    else
    {
        cout << "The number used for testing negative infinity operations is not negative infinity. The program will exit now." << endl;
        exit (EXIT_FAILURE);
    }
    // Check if nan
    if (Global_Functions::Check_For_Exceptions_Zeros(NANVAL) == "NAN") 
    {
        cout << "NAN value has been detected and tested after generation" << endl;
    }
    else
    {
        cout << "The number used for testing NAN operations is not NAN. The program will exit now." << endl;
        exit (EXIT_FAILURE);
    }
    // Check if positive zero
    if (Global_Functions::Check_For_Exceptions_Zeros(POSZERO) == "Positive Zero") 
    {
        cout << "Positive Zero value has been detected and tested after generation" << endl;
    }
    else
    {
        cout << "The number used for Positive Zero operations is not Positive Zero. The program will exit now." << endl;
        exit (EXIT_FAILURE);
    }
    // Check if negative zero
    if (Global_Functions::Check_For_Exceptions_Zeros(NEGZERO) == "Negative Zero") 
    {
        cout << "Negative Zero value has been detected and tested after generation" << endl;
    }
    else
    {
        cout << "The number used for Negative Zero operations is not Negative Zero. The program will exit now." << endl;
        exit (EXIT_FAILURE);
    }

    cout << endl;
}
