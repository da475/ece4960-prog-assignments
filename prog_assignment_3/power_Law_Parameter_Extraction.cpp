/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   power_Law_Parameter_Extraction.cpp
 * Author: Vishisht
 * 
 * Created on April 5, 2018, 3:56 PM
 */

#include "power_Law_Parameter_Extraction.h"

power_Law_Parameter_Extraction::power_Law_Parameter_Extraction() {
    //srand(time(0));
    for (int i = 0; i < sizeof(X)/sizeof(X[0]); i++) {
        X[i] = (double)(rand() % 500)/100;
    }
}

int power_Law_Parameter_Extraction::find_S_Measured() {
    for (int i = 0; i < sizeof(X)/sizeof(X[0]); i++) {
        double temp = (rand() % 40 + 80);
        if (temp > 90 && temp <= 100) temp -= 10;
        if (temp > 100 && temp < 110) temp += 10;
        temp /= 100;
        S_Measured[i] = 10 * pow(X[i], -0.5);// * temp;
    }
    /*
    for (int i = 0; i < sizeof(X)/sizeof(X[0]); i++) {
        cout << X[i] << " ";
    }
    cout << endl;
    for (int i = 0; i < sizeof(X)/sizeof(X[0]); i++) {
        cout << S_Measured[i] << " ";
    }
    */
}

int power_Law_Parameter_Extraction::find_S_Model(full_Vector *answer) {
    double matrix2[2][2] = {{0,0},{0,0}};
    double *matrix1 = (double *)calloc(2 * 2, sizeof(double));
    
    for (int i = 0; i < sizeof(X)/sizeof(X[0]); i++) {
        matrix1[0] += log(X[i])*log(X[i]);
        matrix1[1] += log(X[i]);
    }
    matrix1[2] = matrix1[1];
    matrix1[3] = 10;
    cout << "sdsds" << endl;
    cout << matrix1[0] << " " << matrix1[1] << " " << matrix1[2] << " " << matrix1[3] << endl;
    cout << "sdsds" << endl;
    full_Matrix *matrix = new full_Matrix();
    if (Global_Functions::Create_Pointer_From_Matrix(matrix1, matrix, 2)) return ERROR;
    
    double vector2[2] = {0,0};
    double *vector1 = (double *)calloc(2, sizeof(double));
    for (int i = 0; i < 2; i++) {
        vector1[0] += log(X[i])*log(S_Measured[i]) ;
        vector1[1] += log(S_Measured[i]);
    }
    full_Vector *vector = new full_Vector();
    if (Global_Functions::Create_Pointer_From_Vector(vector1, vector, 3)) return ERROR;
    
    full_Matrix_Solver *solver = new full_Matrix_Solver(matrix, vector);
    solver->l_U_Decomposition();
    solver->back_Substitution(answer);
}

power_Law_Parameter_Extraction::~power_Law_Parameter_Extraction() {
}

