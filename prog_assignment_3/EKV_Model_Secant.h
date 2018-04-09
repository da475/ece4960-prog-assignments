/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   EKV_Model_Secant.h
 * Author: Vishisht
 *
 * Created on April 8, 2018, 11:55 AM
 */

#include "assignment_3_Header.h"
#include "full_Matrix_Solver.h"
#include "load_OutputNMOS.h"

#ifndef EKV_MODEL_SECANT_H
#define EKV_MODEL_SECANT_H

class EKV_Model_Secant {
public:    
    EKV_Model_Secant(double K1 = 1, double Vth1 = 1, double Is1 = 1e-7);
    virtual ~EKV_Model_Secant();
private:
    double VT;
    int rank;
    
    double *Parameters0;
    double *Parameters1;
    double *Parameters2;
    double *DelParameters;
    double *Hessian;
    double *DelV;
    double *Vgs;
    double *Vds;
    double *Ids;
    
    double calculate_Id_Model(double Vgs, double Vds, double K, double Vth, double Is);
    double calculate_V(double K, double Vth, double Is);
    
    double calculate_V_K(double K_Current, double Vth_Current, double Is_Current, 
        double K_Previous, double Vth_Previous, double Is_Previous);
    double calculate_V_Vth(double K_Current, double Vth_Current, double Is_Current, 
        double K_Previous, double Vth_Previous, double Is_Previous);
    double calculate_V_Is(double K_Current, double Vth_Current, double Is_Current, 
        double K_Previous, double Vth_Previous, double Is_Previous);
    
    void create_Hesian();
    void create_Del_V();
    
    double num_Hesian();
    
    void find_Parameters();
    
    void recurrence_Relation();

};

#endif /* EKV_MODEL_SECANT_H */

