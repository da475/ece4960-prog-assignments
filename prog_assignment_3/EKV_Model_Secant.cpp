/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   EKV_Model_Secant.cpp
 * Author: Vishisht
 * 
 * Created on April 8, 2018, 11:55 AM
 */

#include "EKV_Model_Secant.h"

void EKV_Model_Secant::recurrence_Relation() {
    double V_0 = EKV_Model_Secant::calculate_V(this->Parameters0[0], this->Parameters0[1], this->Parameters0[2]);
    double V_1 = EKV_Model_Secant::calculate_V(this->Parameters1[0], this->Parameters1[1], this->Parameters1[2]);
    for (int i = 0; i < this->rank; i++) {
        this->Parameters2[i] = ((this->Parameters0[i] * V_1) - (this->Parameters1[i] * V_0)) / (V_1 - V_0);
    }
}

double EKV_Model_Secant::calculate_Id_Model(double Vgs, double Vds, double K, double Vth, double Is) {
    return (Is * pow(log(1.0 + exp(K * (Vgs - Vth) / (2.0 * VT))), 2.0) - 
            Is * pow(log(1.0 + exp((K * (Vgs - Vth) - Vds) / (2.0 * VT))), 2.0));
}

double EKV_Model_Secant::calculate_V(double K, double Vth, double Is) {
    double idModel, idMeasured, V = 0;
    for (int i = 0; i < sizeOfOutputNMOS; i++) {
        idModel = EKV_Model_Secant::calculate_Id_Model(Vgs[i], Vds[i], K, Vth, Is);
        idMeasured = Ids[i];
        V += (idModel - idMeasured) * (idModel - idMeasured);
    }
    return V;
}


double EKV_Model_Secant::calculate_V_K(double K_Current, double Vth_Current, double Is_Current, 
        double K_Previous, double Vth_Previous, double Is_Previous) {
    double V_2 = EKV_Model_Secant::calculate_V(K_Current, Vth_Current, Is_Current);
    double V_1 = EKV_Model_Secant::calculate_V(K_Previous, Vth_Previous, Is_Previous);
    return (V_2 - V_1) / (K_Current - K_Previous);
}

double EKV_Model_Secant::calculate_V_Vth(double K_Current, double Vth_Current, double Is_Current, 
        double K_Previous, double Vth_Previous, double Is_Previous) {
    double V_2 = EKV_Model_Secant::calculate_V(K_Current, Vth_Current, Is_Current);
    double V_1 = EKV_Model_Secant::calculate_V(K_Previous, Vth_Previous, Is_Previous);
    return (V_2 - V_1) / (Vth_Current - Vth_Previous);
}

double EKV_Model_Secant::calculate_V_Is(double K_Current, double Vth_Current, double Is_Current, 
        double K_Previous, double Vth_Previous, double Is_Previous) {
    double V_2 = EKV_Model_Secant::calculate_V(K_Current, Vth_Current, Is_Current);
    double V_1 = EKV_Model_Secant::calculate_V(K_Previous, Vth_Previous, Is_Previous);
    return (V_2 - V_1) / (Is_Current - Is_Previous);
}


double EKV_Model_Secant::num_Hesian() {
    double V_2 = EKV_Model_Secant::calculate_V(this->Parameters2[0], this->Parameters2[1], this->Parameters2[2]);
    double V_1 = EKV_Model_Secant::calculate_V(this->Parameters1[0], this->Parameters1[1], this->Parameters1[2]);
    double V_0 = EKV_Model_Secant::calculate_V(this->Parameters0[0], this->Parameters0[1], this->Parameters0[2]);
    return (V_2 - 2 * V_1 + V_0);
}

void EKV_Model_Secant::create_Hesian() {
    this->Hessian[0] = EKV_Model_Secant::num_Hesian() / ((this->Parameters2[0] - this->Parameters1[0]) * (this->Parameters1[0] - this->Parameters0[0]));
    this->Hessian[4] = EKV_Model_Secant::num_Hesian() / ((this->Parameters2[1] - this->Parameters1[1]) * (this->Parameters1[1] - this->Parameters0[1]));
    this->Hessian[8] = EKV_Model_Secant::num_Hesian() / ((this->Parameters2[2] - this->Parameters1[2]) * (this->Parameters1[2] - this->Parameters0[2]));    
}

void EKV_Model_Secant::create_Del_V() {
    this->DelV[0] = calculate_V_K(this->Parameters2[0], this->Parameters2[1], this->Parameters2[2],
            this->Parameters1[0], this->Parameters1[1], this->Parameters1[2]);
    this->DelV[1] = calculate_V_Vth(this->Parameters2[0], this->Parameters2[1], this->Parameters2[2],
            this->Parameters1[0], this->Parameters1[1], this->Parameters1[2]);
    this->DelV[2] = calculate_V_Is(this->Parameters2[0], this->Parameters2[1], this->Parameters2[2],
            this->Parameters1[0], this->Parameters1[1], this->Parameters1[2]);
}


void EKV_Model_Secant::find_Parameters() { 
    
    full_Matrix *HessianStruct = new full_Matrix();
    full_Vector *DelVStruct = new full_Vector();
    full_Vector *ParametersStruct = new full_Vector();
    
    double absoluteResidual = 1.0, relativeResidual = 1.0, V = 0;
    int counter = 0;
    do {
        EKV_Model_Secant::create_Hesian();
        EKV_Model_Secant::create_Del_V();        
        
        Global_Functions::create_Struct_From_Matrix(this->Hessian, HessianStruct, this->rank);
        Global_Functions::create_Struct_From_Vector(this->DelV, DelVStruct, this->rank);
        Global_Functions::create_Struct_From_Vector(this->DelParameters, ParametersStruct, this->rank);

        full_Matrix_Solver *solver = new full_Matrix_Solver(HessianStruct, DelVStruct);
        solver->l_U_Decomposition();
        solver->back_Substitution(ParametersStruct);
        
        for (int i = 0; i < this->rank; i++) {
            this->Parameters0[i] = this->Parameters1[i];
            this->Parameters1[i] = this->Parameters2[i];
            this->Parameters2[i] -= ParametersStruct->arr[i];
        }
        
        absoluteResidual =  ((ParametersStruct->arr[0] * ParametersStruct->arr[0]) + 
        (ParametersStruct->arr[1] * ParametersStruct->arr[1]) + 
        (ParametersStruct->arr[2] * ParametersStruct->arr[2]));
        
        relativeResidual = 
        ((ParametersStruct->arr[0] * ParametersStruct->arr[0]) / (this->Parameters2[0] * this->Parameters2[0])) + 
        ((ParametersStruct->arr[1] * ParametersStruct->arr[1]) / (this->Parameters2[1] * this->Parameters2[1])) + 
        ((ParametersStruct->arr[2] * ParametersStruct->arr[2]) / (this->Parameters2[2] * this->Parameters2[2]));

        cout << relativeResidual << endl;
        
        counter++;
        
        V = EKV_Model_Secant::calculate_V(this->Parameters2[0], this->Parameters2[1], this->Parameters2[2]);
    } while (relativeResidual > 1e-8);
    cout << "--------Secant Covergence---------" << endl;
    cout << "Iterations: " << counter << endl;
    cout << "Kappa(K): " << this->Parameters2[0] << endl;
    cout << "Threshold Voltage(Vth): " << this->Parameters2[1] << endl;
    cout << "Source Current(Is): " << this->Parameters2[2] << endl;
    cout << "Absolute Residual: " <<  absoluteResidual << endl;
    cout << "Relative Residual: " <<  relativeResidual << endl;
    cout << "V: " <<  V << endl;
}


EKV_Model_Secant::EKV_Model_Secant(double K1, double Vth1, double Is1) {
    this->VT = 0.026;
    this->rank = 3;
    
    this->Vgs = (double *)calloc(sizeOfOutputNMOS, sizeof(double));
    this->Vds = (double *)calloc(sizeOfOutputNMOS, sizeof(double));
    this->Ids = (double *)calloc(sizeOfOutputNMOS, sizeof(double));
    load_OutputNMOS *load = new load_OutputNMOS();
    load->getIdsPointer(&(this->Ids));
    load->getVdsPointer(&(this->Vds));
    load->getVgsPointer(&(this->Vgs));
    
    
    this->Parameters0 = (double *)calloc(this->rank, sizeof(double));
    this->Parameters1 = (double *)calloc(this->rank, sizeof(double));
    this->Parameters2 = (double *)calloc(this->rank, sizeof(double));
    this->DelParameters = (double *)calloc(this->rank, sizeof(double));
    this->Parameters0[0] = K1 + 0.1;
    this->Parameters0[1] = Vth1 - 0.1;
    this->Parameters0[2] = 2.5 * Is1;
    this->Parameters1[0] = K1;
    this->Parameters1[1] = Vth1;
    this->Parameters1[2] = Is1;
    EKV_Model_Secant::recurrence_Relation();
    
    this->Hessian = (double *)calloc(this->rank * this->rank, sizeof(double));
    this->DelV = (double *)calloc(this->rank, sizeof(double));

    EKV_Model_Secant::find_Parameters();
}

EKV_Model_Secant::~EKV_Model_Secant() {
}

