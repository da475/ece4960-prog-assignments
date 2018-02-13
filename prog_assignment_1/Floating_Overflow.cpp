/* 
 * File:   Floating_Overflow.cpp
 * Author: Vishisht
 *
 * Created on February 12, 2018, 4:50 PM
 */

#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <cstdlib>
#include <cmath>
#include <cfenv>

using namespace std;

class Floating_Overflow{
private:
    
public:
    void TestOne() {
        double ten= 10;
        double result;
        int power = 0;
        while (!isinf(result)) {
            power++;
            result = pow(ten,power);
            if (isinf(result)) 
            {
                cout << "Using test number 1" << endl;
                cout << "At " << power << "th iteration, the floating point overflowed" << endl;
                cout << "Hence double overflowed at 10^" << power << " value" << endl;
            }
        }
        cout << endl;
    }
    
    void TestTwo() {
        double ten= 10;
        double result;
        int power = 0;
        feclearexcept(FE_OVERFLOW);
        while (fetestexcept(FE_OVERFLOW) == 0) {
            power++;
            result = pow(ten,power);
            if (fetestexcept(FE_OVERFLOW) != 0) 
            {
                cout << "Using test number 2" << endl;
                cout << "At " << power << "th iteration, the floating point overflowed" << endl;
                cout << "Hence double overflowed at 10^" << power << " value" << endl;
            }
        }
        cout << endl;
    }
    
    // We tested but checking the sign bit did not work
};

int main(int argc, char** argv) {
    
    // Create the first object
    Floating_Overflow *overflowTesting = new Floating_Overflow();
    overflowTesting->TestOne();
    overflowTesting->TestTwo();

    return 0;
}