/* 
 * Author: Vishisht Tiwari, Deepak Agarwal
 * Netids: vmt28 and da475
 * Copyright @ 2018 Vishisht Tiwari and Deepak Agarwal. All rights reserved

 * Created on May 15, 2018, 7:26 PM
 * File:   Assignment_5_Main.cpp
 * Desc: Main file that calls all the necessary classes
 */

#include "Assignment_5_Header.h"
#include "ODE_Solvers.h"
#include "Validation.h"
#include "Circuit_Sim.h"

int main(int argc, char** argv)
{    
    
    // All operations are performed within a try block
    // Internal functions are checking for invalid scenarios
    // and throwing exceptions which are caught by the catch
    // block below the try block
    try
    {
        // Sets the precision for Validation
        cout.precision(10);
        cout.setf(ios::fixed);

        // Calls the validation class that checks all the three types of ODE Solvers
        cout << endl << endl << "#################################################### Validating ODE Solvers ####################################################" << endl;
        Validation *validate = new Validation();
        
        // Sets the precision for Circuit Simulation
        cout.precision(10);

        // Calls the first Circuit Simulation of RC Circuit for all the tree types of ODE Solvers at
        // 1, 0.2 and 0.002 time steps
        cout << endl << endl << "#################################################### Circuit Simulation 1 with 0.2ns steps ####################################################" << endl;
        Circuit_Sim *sim = new Circuit_Sim(0.002, 0.1);
    }    
    catch (int check)
    {
        if (check == ERROR)
        {
            cerr << "Error Observed" << endl;
            return ERROR;
        }
        if (check == UNMATCHED_RANK)
        {
            cerr << "Unmatched Rank Error Observed" << endl;
            return UNMATCHED_RANK;
        }
        if (check == UNMATCHED_DIM)
        {
            cerr << "Unmatched Dimensions Error Observed" << endl;
            return UNMATCHED_DIM;
        }
        if (check == IS_INF_NINF)
        {
            cerr << "NINF/INF Error Observed" << endl;
            return IS_INF_NINF;
        }
        if (check == IS_NAN)
        {
            cerr << "NAN Error Observed" << endl;
            return IS_NAN;
        }
    }
    cout << endl;
    cout << "Completed Successfully" << endl;
    return NO_ERROR;
}