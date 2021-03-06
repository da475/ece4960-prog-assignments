/* 
 * File:   Integer_Overflow.cpp
 * Author: Deepak,Vishisht
 *
 * Created on February 12, 2018
 */

// Include common header
#include "Assignment1_Header.h"

// Implement integer overflow using multiplication
void Integer_Overflow::TestMult(int num) 
{
    cout << endl << endl << "Integer Overflow : MULT" << endl;
    int num1 = 1000000000;
    int mult = num1 * num;

    // Check if the division of one term produces the other term
    try{
        if((mult/num1 != num)) {
            throw 1;
        }
        else
            cout << "Integer overflow did not occur occur when " << num1 << " was multiplied with " << num <<  endl;
    }

    catch(int c) {
        cout << "Integer overflow occurred when " << num1 << " was multiplied with " << num <<  endl;
    }
    cout << endl;
}

// Implement integer overflow using factorial
void Integer_Overflow::TestFact() 
{
    cout << endl << endl << "Integer Overflow : FACTORIAL" << endl;
    cout << "All factorials from 1 onwards are being computed. The first factorial for which integer type overflows, will be reported" << endl;
    int prevFactorial = 1;
    int fact = 1;
    int n = 0;
    bool overflown = false;

    while(!overflown) 
    {
        n++;
        fact *= n;

        // Check if the division by previous factorial and the current number produces 0. If it does not then overflow has occurred
        try {
            if ((int)((fact/n)/prevFactorial) != 1) 
                throw 1;
        }
        catch(int c) {
            cout << "Integer overflow has occurred while computing factorial of: " << n << endl;
            overflown = true;
        }
        prevFactorial = fact;
    }
    cout << endl;
}

// Implement integer overflow using fibonacci
void Integer_Overflow::TestFibonacci() 
{
    cout << endl << endl << "Integer Overflow : FIBONACCI" << endl;
    cout << "Fibonacci sequence of lengths from 1 onwards are being computed. The first sequence for which integer type overflows, will be reported" << endl;
    int prevNumber = 0;
    int currNumber = 1;
    int newNumber = 1;
    int n = 0;
    bool overflown = false;
    while(!overflown) 
    {
        n++;
        newNumber = currNumber + prevNumber;
        // Check if the subtraction results in 0
        if (((newNumber < currNumber) && (newNumber < prevNumber)) != 0)
        {
            cout << "Integer overflow has occurred while computing fibonacci of sequence length: " << n << endl;
            overflown = true;
        }
        prevNumber = currNumber;
        currNumber = newNumber;
    }
    cout << endl;
}

// Trying divide by 0
void Integer_Overflow::DivbyZero() {
    string str;
    cout << endl << endl << "Integer Overflow : DIVIDE BY 0" << endl;
    cout << "The program is going to implement division by zero. This will crash the program. If you want to implement then type 'cont'. Type anything "
            "else to skip this program." << endl;
    cin >> str;
    // The following block implements division by 0 and will crash out if implemented
    
    if ((str == "cont") || (str == "Cont"))
    {
        int x = 0;
        int y = 4/x;
        cout << "4 div 0 is " << y << endl;
    }
}
