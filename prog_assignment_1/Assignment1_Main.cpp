/* 
 * File:   Assignment1_Main.cpp
 * Author: Vishisht, Deepak
 *
 * Created on February 16, 2018, 1:06 AM
 */

#include "Assignment1_Header.h"

int main(int argc, char** argv) {
    
    // Run integer overflow operations
    Integer_Overflow *overflowIntegerTesting = new Integer_Overflow();
    overflowIntegerTesting->TestMult();
    overflowIntegerTesting->TestFact();
    overflowIntegerTesting->TestFibonacci();
    overflowIntegerTesting->DivbyZero();
    
    // Run floating-point overflow operations
    Floating_Overflow *overflowDoubleTesting = new Floating_Overflow();
    overflowDoubleTesting->TestPowerIterations();
    
    // Run floating-point operations
    Floating_Operations *operationsTesting = new Floating_Operations();
    operationsTesting->INF_Operations();
    operationsTesting->NINF_Operations();
    operationsTesting->NAN_Operations();
    operationsTesting->Prop_And_Interaction();
    
    // Run signed-zero operations
    Signed_Zero *signedZeroTesting = new Signed_Zero();
    signedZeroTesting->Log_Operations();
    signedZeroTesting->Sinc_Operations();
    signedZeroTesting->Sinc_With_Absolute_Operations();
    
    // Run gradual overflow operations
    Gradual_Underflow *gradualUnderflowTesting = new Gradual_Underflow();
    gradualUnderflowTesting->underFlow_Using_Sin();
    gradualUnderflowTesting->x_minus_y();
    gradualUnderflowTesting->x_div_y();

    return 0;
}

