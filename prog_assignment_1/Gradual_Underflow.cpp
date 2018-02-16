/* 
 * File:   Gradual_Underflow.cpp
 * Author: Vishisht/Deepak
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

    void x_minus_y() {
        float base1 = 4.50;
        float base2 = 4.51;
        //double x = 1.1011 * pow(2, -1020); 
        double x = base1 * pow(10, -300); 
        double y = base2 * pow(10, -300); 
        //double y = 1.1010 * pow(2, -1020);
        
        for(int i=0; i<40; i++) {

            if(x - y == 0)
                cout << "x-y==0 is true for iter " << i << endl;
    
            if(x == y)
                cout << "x==y is true for iter " << i << endl;

            x = x/10;
            y = y/10;

        }
    }

};

int main(int argc, char** argv) {
    
    // Create the first object
    Gradual_Underflow *gradualUnderflowTesting = new Gradual_Underflow();
    
    gradualUnderflowTesting->third();
    gradualUnderflowTesting->x_minus_y();


    return 0;
}

