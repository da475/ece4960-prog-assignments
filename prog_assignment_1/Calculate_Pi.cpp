/* 
 * File:   Calculate_Pi.cpp
 * Author: Deepak
 *
 * Created on February 12, 2018
 */

#include "Assignment1_Header.h"

/*
    Using the formula:
    ln (640320^3 + 744) / sqroot(163)
*/

long double Calculate_Pi::precision_30() {
    cout << endl << endl << "Pi Calculation" << endl;
    long double num1 = 640320;
    long double num2 = 744;
    cout.precision(30);
    long double numer = (num1 * num1 * num1) + num2;

    //long double log_value = logcal(numer);
    long double log_value = log(numer);
    long double root_value = sqroot(163);
    long double pi_value = log_value / root_value;
    
    return pi_value;

}


    long double Calculate_Pi::logcal(long double num) {
        long double i = 0;
        cout.precision(30);
        if (num < 0) return -1;
        else if (num == 1) return 0;
        else if (num == 0) return -1;

        int iterations = 5;
        //using the series expansion
        long double y = (num - 1) / (num + 1);
        cout << "num is " << num << endl;
        cout << "y is " << y << endl;
        long double y2 = y * y;
        long double y_val = y * y;
        long double result = 1;        
        long double n1 = 1;

        for (i=1; i<iterations; i++) {
            result += y_val / ((2*i) + 1);
            y_val = y_val * y2;
            //cout << "result is " << result << endl;
        }

        return result * 2 * y;
        
    }


        // using the rough estimation method called Babylonian method to calculate the root
        // x(n+1) = (1/2) * (x(n) + (S/x(n)))
    long double Calculate_Pi::sqroot(long double num) {
        int i = 0;
        if (num < 0) return -1;
        else if (num == 1 || num == 0) return num;

        // loop finds the approximate integer to start
        for (i=1; i<num; i++) {
            if(i*i == num) return i;
            if(i*i < num && i*i > num) break;   // here, square(i) < num < square(i+1)
        }

        long double root = i;       // initial approximation
        int iterations = 20;
        long double n1, n2;

        cout.precision(30);
        for (i=0; i<iterations; i++) {
            n1 = num / root;
            n2 = n1 + root;
            root = n2 / 2;

        }
        return root;

    }


