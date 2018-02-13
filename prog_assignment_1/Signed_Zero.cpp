/* 
 * File:   Signed_Zero.cpp
 * Author: Vishisht
 *
 * Created on February 12, 2018, 5:15 PM
 */

#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <cstdlib>
#include <cmath>

using namespace std;

class Signed_Zero{
private:
    double INF;
    double POSZERO;
    double NEGZERO;
    
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
        INF = numeric_limits<double>::infinity();
        POSZERO = 1/INF;
        NEGZERO = 1/-INF;
    }
};

int callingFunction3(int argc, char** argv) {
    
    // Create the first object
    Signed_Zero *signedZeroTesting = new Signed_Zero();
    signedZeroTesting->Log_Operations();
    signedZeroTesting->Sinc_Operations();
    signedZeroTesting->Sinc_With_Absolute_Operations();

    return 0;
}