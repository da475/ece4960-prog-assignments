/* 
 * File:   Floating_Operations.cpp
 * Author: Vishisht
 *
 * Created on February 12, 2018, 4:53 PM
 */

#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <cstdlib>
#include <cmath>

using namespace std;

class Floating_Operations{
private:
    double INF;
    double NINF;
    
public:
    void Infinity_Operations() {
        cout << "Floating Operations for infinity" << endl;
        cout << "Value of 1/x where x is infinity is: " << 1/INF << endl;
        cout << "Value of sin(x) where x is infinity is: " << sin(INF) << endl;
        cout << "Value of exp(x) where x is infinity is: " << exp(INF) << endl;
        cout << endl;
    }
    
    void Negative_Infinity_Operations() {
        cout << "Floating Operations for -infinity" << endl;
        cout << "Value of 1/x where x is -infinity is: " << 1/NINF << endl;
        cout << "Value of sin(x) where x is -infinity is: " << sin(NINF) << endl;
        cout << "Value of exp(x) where x is -infinity is: " << exp(NINF) << endl;
        cout << endl;
    }
    
    void Not_A_Number_Operations() {
        cout << "Floating Operations for NAN" << endl;
        cout << "Value of 1/x where x is NAN is: " << 1/NAN << endl;
        cout << "Value of sin(x) where x is NAN is: " << sin(NAN) << endl;
        cout << "Value of exp(x) where x is NAN is: " << exp(NAN) << endl;
        cout << endl;
    }
    
    Floating_Operations() {
        INF = numeric_limits<double>::infinity();
        NINF = -numeric_limits<double>::infinity();
    }
};

int callingFunction2(int argc, char** argv) {
    // Create the first object
    Floating_Operations *operationsTesting = new Floating_Operations();
    operationsTesting->Infinity_Operations();
    operationsTesting->Negative_Infinity_Operations();
    operationsTesting->Not_A_Number_Operations();

    return 0;
}

