/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   EKV_Model.h
 * Author: Vishisht
 *
 * Created on April 7, 2018, 7:54 PM
 */

#include "assignment_3_Header.h"
#include "full_Matrix_Solver.h"
#include "load_OutputNMOS.h"

#ifndef EKV_MODEL_H
#define EKV_MODEL_H

class EKV_Model {
public:
    EKV_Model(double K = 1, double Vth = 1, double Is = pow(10, -7));
    virtual ~EKV_Model();
private:
    double VT;
    int rank;
    double pert;
    double pertK;
    double pertVth;
    double pertIs;
    
    double *DelParameters;
    double *Parameters;
    double *Hessian;
    double *DelV;
    double *Vgs;
    double *Vds;
    double *Ids;
    
    double calculate_Id_Model(double Vgs, double Vds, double K, double Vth, double Is);
    double calculate_V(double K, double Vth, double Is);
    
    double calculate_V_K(double K, double Vth, double Is);
    double calculate_V_Vth(double K, double Vth, double Is);
    double calculate_V_Is(double K, double Vth, double Is);
    
    double calculate_V_K_K(double K, double Vth, double Is);
    double calculate_V_K_Vth(double K, double Vth, double Is);
    double calculate_V_K_Is(double K, double Vth, double Is);
    
    double calculate_V_Vth_K(double K, double Vth, double Is);
    double calculate_V_Vth_Vth(double K, double Vth, double Is);
    double calculate_V_Vth_Is(double K, double Vth, double Is);
    
    double calculate_V_Is_K(double K, double Vth, double Is);
    double calculate_V_Is_Vth(double K, double Vth, double Is);
    double calculate_V_Is_Is(double K, double Vth, double Is);
    
    double lineSearch(double *parameters, double min, double max, double *tempParameters);
    
    void create_Hesian();
    void create_Del_V();
    
    void find_Parameters();
};

#endif /* EKV_MODEL_H */

