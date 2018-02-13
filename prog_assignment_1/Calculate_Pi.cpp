/* 
 * File:   Calculate_Pi.cpp
 * Author: Deepak
 *
 * Created on February 12, 2018
 */

#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <cstdlib>
#include <cmath>
#include <cfenv>

using namespace std;

#define INT_VAL_MAX 2147483647

class Calc_Pi{
    
public:
    void precision_30() {
        int num1 = 640320;
        int num2 = 3;
        long long mult = (num1 * num1 * num1) + 744;
        cout << "mult value " << mult << endl;
        //long long mult = 30000;
        double log_val = log(mult);
        cout << "log value " << log_val << endl;
        double root_val = sqrt(163);
        double pi_val = log_val / root_val;
        cout << "pi value " << pi_val << endl;
    }

    
};


int main(int argc, char** argv) {
    
    // Create the first object
    Calc_Pi *pi_obj = new Calc_Pi();
    pi_obj->precision_30();

    return 0;
}


