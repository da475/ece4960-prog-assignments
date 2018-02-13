/* 
 * File:   Integer_Overflow.cpp
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

class Integer_Overflow{
private:
    
public:
    void TestMult() {
        int num1 = 1000000000;
        int num2 = 3;
        int mult = num1 * num2;
        if(mult < 0)
            cout << "Integer overflow occurred" << endl;
    }

    void TestFact() {
        int n;
        cout << "Enter the number for fact " << endl;
        cin >> n;
        if (n < 0) return;
        if (n == 1 || n == 0) return;

        int fact = 1;
        for(int i=2; i<=n; i++) {
            fact = fact * i;
            if (fact < 0) {
                cout << "Overflow occurred, returning max" << endl;
                return;
            }
        }
        cout << "Factorial of " << n << " is " << fact << endl;
    }


    void TestFibonacci() {
        int n;
        cout << "Enter the number for fibonacci " << endl;
        cin >> n;
        if (n <= 1) return;

        int first = 0;
        int second = 1;
        int fib = 1;

        for(int i=0; i<n; i++) {
            fib = second + first;
            first = second;
            second = fib;
            if (fib < 0) {
                cout << "Overflow occurred, returning max" << endl;
                return;
            }
        }
        cout << "Fib of " << n << " is " << fib << endl;
    }

    void DivbyZero() {
        int x = 0;
        int y = 4/x;
        cout << "4 div 0 is " << y << endl;
    }
    
};


int main(int argc, char** argv) {
    
    // Create the first object
    Integer_Overflow *overflowTesting = new Integer_Overflow();
    overflowTesting->TestMult();
    overflowTesting->TestFibonacci();
    overflowTesting->DivbyZero();

    return 0;
}


