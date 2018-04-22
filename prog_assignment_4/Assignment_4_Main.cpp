/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Assignment_4_Main.cpp
 * Author: Vishisht
 *
 * Created on April 18, 2018, 5:54 PM
 */

#include "Assignment_4_Header.h"
#include "ODE_Solvers.h"
#include "Validation.h"
#include "Circuit_Sim_1.h"
#include "Circuit_Sim_2.h"


int main(int argc, char** argv) {    
    cout.precision(2);
    cout.setf(ios::fixed);
    
    cout << endl << endl << "####################################################Validating ODE Solvers####################################################" << endl << endl;
    Validation *validate = new Validation();
    
    cout.precision(4);
    
    cout << endl << endl << "####################################################Circuit Simulation 1 with 0.2ns steps####################################################" << endl << endl;
    Circuit_Sim_1 *sim1_02 = new Circuit_Sim_1(0.2);
    cout << endl << endl << "####################################################Circuit Simulation 1 with 1ns steps####################################################" << endl << endl;
    Circuit_Sim_1 *sim1_1 = new Circuit_Sim_1(1);
    
    cout << endl << endl << "####################################################Circuit Simulation 2 with 0.2ns steps####################################################" << endl<< endl;
    Circuit_Sim_2 *sim2_02 = new Circuit_Sim_2(0.2);
    cout << endl << endl << "####################################################Circuit Simulation 2 with 1ns steps####################################################" << endl << endl;
    Circuit_Sim_2 *sim2_1 = new Circuit_Sim_2(1);
    
    return 0;
}