/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   power_Law_Parameter_Extraction.h
 * Author: Vishisht
 *
 * Created on April 5, 2018, 3:56 PM
 */

#include "assignment_3_Header.h"
#include "full_Matrix_Solver.h"

#ifndef POWER_LAW_PARAMETER_EXTRACTION_H
#define POWER_LAW_PARAMETER_EXTRACTION_H

class power_Law_Parameter_Extraction {
public:
    power_Law_Parameter_Extraction();
    void find_S_Measured();
    void find_S_Model(full_Vector *answer);
    virtual ~power_Law_Parameter_Extraction();
private:
    double X[10];
    double S_Measured[10];
    int rank;
};

#endif /* POWER_LAW_PARAMETER_EXTRACTION_H */

