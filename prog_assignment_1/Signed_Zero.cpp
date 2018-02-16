/* 
 * File:   Signed_Zero.cpp
 * Author: Deepak, Vishisht
 *
 * Created on February 12, 2018, 5:15 PM
 */

#include "Assignment1_Header.h"

class Signed_Zero{
private:
    
public:
    void Log_Operations() {
        cout << "Value of log(x) where x is +0 is: " << log(POSZERO) << endl;
        cout << "Value of log(x) where x is -0 is: " << log(NEGZERO) << endl;
        cout << endl;
    }
    
    void Sinc_Operations() {
        cout << "Value of sin(x)/x where x is +0 is: " << sin(POSZERO)/POSZERO << endl;
        cout << "Value of sin(x)/x where x is -0 is: " << sin(NEGZERO)/NEGZERO << endl;
        cout << endl;
    }
    
    void Sinc_With_Absolute_Operations() {
        cout << "Value of sin(x)/|x| where x is +0 is: " << sin(POSZERO)/abs(POSZERO) << endl;
        cout << "Value of sin(x)/|x| where x is -0 is: " << sin(NEGZERO)/abs(NEGZERO) << endl;
        cout << endl;
    }
    
    Signed_Zero() {
        if (Global_Functions::Check_For_Exceptions_Zeros(POSZERO) == "Positive Zero") 
        {
            cout << "Positive Zero value has been detected and tested after generation" << endl;
        }
        else
        {
            cout << "The number used for Positive Zero operations is not Positive Zero. The program will exit now." << endl;
            exit (EXIT_FAILURE);
        }
        
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
};