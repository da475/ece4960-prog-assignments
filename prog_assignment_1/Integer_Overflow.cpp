/* 
 * File:   Integer_Overflow.cpp
 * Author: Deepak,Vishisht
 *
 * Created on February 12, 2018
 */

#include "Assignment1_Header.h"

void Integer_Overflow::TestMult() 
{
    int num1 = 1000000000;
    int num2 = 3;
    int mult = num1 * num2;
    if((mult/num1 != num2))
        cout << "Integer overflow occurred when " << num1 << " was multiplied with " << num2 <<  endl;
    else
        cout << "Integer overflow did not occur occur when " << num1 << " was multiplied with " << num2 <<  endl;
    cout << endl;
}

void Integer_Overflow::TestFact() 
{
    cout << "All factorials from 1 onwards are being computed. The first factorial for which integer type overflows, will be reported" << endl;
    int prevFactorial = 1;
    int fact = 1;
    int n = 0;
    bool overflown = false;
    while(!overflown) 
    {
        n++;
        fact *= n;
        if ((int)((fact/n)/prevFactorial) != 1) 
        {
            cout << "Integer overflow has occurred while computing factorial of: " << n << endl;
            overflown = true;
        }
        prevFactorial = fact;
    }
    cout << endl;
}


void Integer_Overflow::TestFibonacci() 
{
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

void Integer_Overflow::DivbyZero() {
    string str;
    cout << "The program is going to implement division by zero. This will crash the program. If you want to implement then type 'cont'. Type anything "
            "else to skip this program." << endl;
    cin >> str;
    //if ((!str.compare("cont")) || (!str.compare("Cont")))
    if ((str == "cont") || (str == "Cont"))
    {
        int x = 0;
        int y = 4/x;
        cout << "4 div 0 is " << y << endl;
    }
}