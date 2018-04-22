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
    
    // All operations are performed within a try block
    // Internal functions are checking for invalid scenarios
    // and throwing exceptions which are caught by the catch
    // block below the try block
    try {
        cout.precision(3);
        cout.setf(ios::fixed);

        cout << endl << endl << "#################################################### Validating ODE Solvers ####################################################" << endl;
        Validation *validate = new Validation();

        cout.precision(10);

        cout << endl << endl << "#################################################### Circuit Simulation 1 with 0.2ns steps ####################################################" << endl;
        Circuit_Sim_1 *sim1_02 = new Circuit_Sim_1(0.2);
        cout << endl << endl << "#################################################### Circuit Simulation 1 with 1ns steps ####################################################" << endl;
        Circuit_Sim_1 *sim1_1 = new Circuit_Sim_1(1);

        cout << endl << endl << "#################################################### Circuit Simulation 2 with 0.2ns steps ####################################################" << endl;
        Circuit_Sim_2 *sim2_02 = new Circuit_Sim_2(0.2);
        cout << endl << endl << "#################################################### Circuit Simulation 2 with 1ns steps ####################################################" << endl;
        Circuit_Sim_2 *sim2_1 = new Circuit_Sim_2(1);
    }    
    catch (int check){
        if (check == ERROR) {
            cerr << "Error Observed" << endl;
            return ERROR;
        }
        if (check == UNMATCHED_RANK) {
            cerr << "Unmatched Rank Error Observed" << endl;
            return UNMATCHED_RANK;
        }
        if (check == UNMATCHED_DIM) {
            cerr << "Unmatched Dimensions Error Observed" << endl;
            return UNMATCHED_DIM;
        }
        if (check == IS_INF_NINF) {
            cerr << "NINF/INF Error Observed" << endl;
            return IS_INF_NINF;
        }
        if (check == IS_NAN) {
            cerr << "NAN Error Observed" << endl;
            return IS_NAN;
        }
    }
    cout << endl;
    cout << "Completed Successfully" << endl;
    return NO_ERROR;
}