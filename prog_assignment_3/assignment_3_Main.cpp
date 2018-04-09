/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   assignment_3_Main.cpp
 * Author: Vishisht
 *
 * Created on April 4, 2018, 6:24 PM
 */

// Including the common header
#include "assignment_3_Header.h"
#include "full_Matrix_Solver.h"
#include "power_Law_Parameter_Extraction.h"
#include "load_OutputNMOS.h"
#include "EKV_Model.h"
#include "EKV_Model_Secant.h"

/*
 * 
 */
int main(int argc, char** argv) {

    // All operations are performed within a try block
    // Internal functions are checking for invalid scenarios
    // and throwing exceptions which are caught by the catch
    // block below the try block
    try {


        // Task 1: Direct full matrix solver with reasonable pivoting checks        
        double matrix2D[3][3] = {{9,3,1},{3,2,8},{0.5,6,2.25}};
        double *matrixPointer = (double *)calloc(3 * 3, sizeof(double));
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                matrixPointer[(i * 3) + j] = matrix2D[i][j];
            }
        }
        full_Matrix *matrix = new full_Matrix();
        Global_Functions::create_Struct_From_Matrix(matrixPointer, matrix, 3);

        double vector1D[3] = {3,8,4};
        double *vectorPointer = (double *)calloc(3, sizeof(double));
        for (int i = 0; i < 3; i++) {
            vectorPointer[i] = vector1D[i];
        }
        full_Vector *vector = new full_Vector();
        Global_Functions::create_Struct_From_Vector(vectorPointer, vector, 3);

        Global_Functions::print_Matrix_Full(matrix);
        Global_Functions::print_Vector_Full(vector);

        // Perform L-U Decomposition
        full_Matrix_Solver *solver = new full_Matrix_Solver(matrix, vector);
        solver->l_U_Decomposition();
        double *answerPointerMatrix = (double *)calloc(3, sizeof(double));
        full_Vector *answerMatrix = new full_Vector();
        Global_Functions::create_Struct_From_Vector(answerPointerMatrix, answerMatrix, 3);
        solver->back_Substitution(answerMatrix);

        Global_Functions::print_Matrix_Full(matrix);
        Global_Functions::print_Vector_Full(vector);
        Global_Functions::print_Vector_Full(answerMatrix);

        // Parameter extraction
        power_Law_Parameter_Extraction *extractor = new power_Law_Parameter_Extraction();
        extractor->find_S_Measured();
        double *answerPointerExtractor = (double *)calloc(2, sizeof(double));
        full_Vector *answerExtractor = new full_Vector();
        Global_Functions::create_Struct_From_Vector(answerPointerExtractor, answerExtractor, 2);
        extractor->find_S_Model(answerExtractor);
        Global_Functions::print_Vector_Full(answerExtractor);
        
        // Secand method        
        double IsInitial[8] = {3e-8, 1e-7, 3e-7, 1e-6, 3e-6, 1e-5, 3e-5};
        double KInitial[5] = {0.5, 0.6, 0.7, 0.8, 0.9};
        double VthInitial[13] = {0.8, 0.9, 1.0, 1.1, 1.2, 1.3, 1.4, 1.5, 1.6, 1.7, 1.8, 1.9, 2.0};
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 5; j++) {
                for (int k = 0; k < 13; k++) {
                    cout << "Is = " << IsInitial[i] << endl;
                    cout << "K = " << KInitial[j] << endl;
                    cout << "Vth = " << VthInitial[k] << endl;
                    EKV_Model *QN = new EKV_Model(KInitial[i], VthInitial[j], IsInitial[k]);
                    EKV_Model_Secant *Secant = new EKV_Model_Secant(KInitial[i], VthInitial[j], IsInitial[k]);
                }
            }
        }
        
        EKV_Model_Secant *Secant = new EKV_Model_Secant(0.5, 0.8, 1e-8);

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

