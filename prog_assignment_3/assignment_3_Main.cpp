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
/*
 * 
 */
int main(int argc, char** argv) {
    
    double matrix2[3][3] = {{9,3,1},{3,2,8},{0.5,6,2.25}};
    double *matrix1 = (double *)malloc(3 * 3 * sizeof(double));
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            matrix1[(i * 3) + j] = matrix2[i][j];
        }
    }
    full_Matrix *matrix = new full_Matrix();
    if (Global_Functions::Create_Pointer_From_Matrix(matrix1, matrix, 3)) return ERROR;
    
    double vector2[3] = {3,8,4};
    double *vector1 = (double *)malloc(3 * sizeof(double));
    for (int i = 0; i < 3; i++) {
        vector1[i] = vector2[i];
    }
    full_Vector *vector = new full_Vector();
    if (Global_Functions::Create_Pointer_From_Vector(vector1, vector, 3)) return ERROR;
    
    Global_Functions::printMatrixFull(matrix);
    Global_Functions::printVectorFull(vector);
    
    full_Matrix_Solver *solver = new full_Matrix_Solver(matrix, vector);
    solver->l_U_Decomposition();
    double *answer1 = (double *)malloc(3 * sizeof(double));
    for (int i = 0; i < 3; i++) {
        answer1[i] = 0;
    }
    full_Vector *answer = new full_Vector();
    if (Global_Functions::Create_Pointer_From_Vector(answer1, answer, 3)) return ERROR;
    solver->back_Substitution(answer);
    
    Global_Functions::printMatrixFull(matrix);
    Global_Functions::printVectorFull(vector);
    Global_Functions::printVectorFull(answer);

    return 0;
}

