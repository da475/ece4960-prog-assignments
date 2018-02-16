/* 
 * File:   Gradual_Underflow.cpp
 * Author: Deepak, Vishisht
 *
 * Created on February 12, 2018, 7:17 PM
 */

#include "Assignment1_Header.h"


void Gradual_Underflow::underFlow_Using_Sin() 
{
    cout << "Value of sin(1.23456789012345x)/x where x is +0 is: " << Global_Functions::Check_For_Exceptions_Zeros(sin(temp*POSZERO)/POSZERO) << endl;
}

<<<<<<< HEAD
void Gradual_Underflow::x_minus_y() 
{
    float base1 = 4.90;
    float base2 = 4.91;
    //double x = 1.1011 * pow(2, -1020); 
    double x = base1 * pow(10, -320); 
    double y = base2 * pow(10, -320); 
    //double y = 1.1010 * pow(2, -1020);

    for(int i=0; i<200; i++) 
    {
        
        cout << "x" << x << endl;
        cout << "y" << y << endl;
        cout << "x-y" << x-y << endl;

        if(x - y == 0)
            cout << "x-y==0 is true for iter " << i << endl;

        if(x == y)
            cout << "x==y is true for iter " << i << endl;

        x = base1 * pow(10, -307); 
        y = base2 * pow(10, -307); 
=======
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
>>>>>>> 0df20360e67211b87b54ee47ec8ef00795ae2ffd

        base1 = base1 * 0.9;
        base2 = base2 * 0.9;

        //x = x/5;
        //y = y/5;
        //power = power - 1;

    }
}
    
Gradual_Underflow::Gradual_Underflow() 
{
    temp = 1.234567890123456;
}