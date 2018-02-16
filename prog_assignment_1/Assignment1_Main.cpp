/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Assignment1_Main.cpp
 * Author: Deepak, Vishisht
 *
 * Created on February 16, 2018, 1:06 AM
 */

#include "Assignment1_Header.h"

int main(int argc, char** argv) {
    
    Integer_Overflow *overflowIntegerTesting = new Integer_Overflow();
    overflowIntegerTesting->TestMult();
    overflowIntegerTesting->TestFact();
    overflowIntegerTesting->TestFibonacci();
    overflowIntegerTesting->DivbyZero();
    
    Floating_Overflow *overflowDoubleTesting = new Floating_Overflow();
    overflowDoubleTesting->TestPowerIterations();
    
    Floating_Operations *operationsTesting = new Floating_Operations();
    operationsTesting->INF_Operations();
    operationsTesting->NINF_Operations();
    operationsTesting->NAN_Operations();
    operationsTesting->Prop_And_Interaction();
    
    Signed_Zero *signedZeroTesting = new Signed_Zero();
    signedZeroTesting->Log_Operations();
    signedZeroTesting->Sinc_Operations();
    signedZeroTesting->Sinc_With_Absolute_Operations();

    return 0;
}

