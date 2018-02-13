/* 
 * File:   Gradual_Underflow.cpp
 * Author: Vishisht
 *
 * Created on February 12, 2018, 7:17 PM
 */

#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <cstdlib>
#include <cmath>

using namespace std;

class Gradual_Underflow{
private:
    double INF;
    double POSZERO;
    double NEGZERO;
    double temp;
    
public:
    void third() {
        cout << "Value of sin(1.23456789012345x)/x where x is +0 is: " << sin(temp*POSZERO)/POSZERO << endl;
    }
    
    Gradual_Underflow() {
        INF = numeric_limits<double>::infinity();
        POSZERO = 1/INF;
        NEGZERO = 1/-INF;
        temp = 1.234567890123456;
    }

};

int mhjhj(int argc, char** argv) {
    
    // Create the first object
    Gradual_Underflow *gradualUnderflowTesting = new Gradual_Underflow();
    
    gradualUnderflowTesting->third();


    return 0;
}

