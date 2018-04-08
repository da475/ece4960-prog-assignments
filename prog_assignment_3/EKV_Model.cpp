/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   EKV_Model.cpp
 * Author: Vishisht
 * 
 * Created on April 7, 2018, 7:54 PM
 */

#include "EKV_Model.h"

double EKV_Model::calculate_Id_Model(double Vgs, double Vds, double K, double Vth, double Is) {
    return (Is * pow(log(1.0 + exp(K * (Vgs - Vth) / (2.0 * VT))), 2.0) - 
            Is * pow(log(1.0 + exp((K * (Vgs - Vth) - Vds) / (2.0 * VT))), 2.0));
}

double EKV_Model::calculate_V(double K, double Vth, double Is) {
    
    double idModel, idMeasured, V = 0;
    for (int i = 0; i < sizeOfOutputNMOS; i++) {
        idModel = EKV_Model::calculate_Id_Model(Vgs[i], Vds[i], K, Vth, Is);
        idMeasured = Ids[i];
        V += (idModel - idMeasured);
    }
    return V;
}


double EKV_Model::calculate_V_K(double K, double Vth, double Is) {
    return (EKV_Model::calculate_V(K + h, Vth, Is) - 
            EKV_Model::calculate_V(K, Vth, Is))
            /h;
}

double EKV_Model::calculate_V_Vth(double K, double Vth, double Is) {
    return (EKV_Model::calculate_V(K, Vth + h, Is) - 
            EKV_Model::calculate_V(K, Vth, Is))
            /h;
}

double EKV_Model::calculate_V_Is(double K, double Vth, double Is) {
    return (EKV_Model::calculate_V(K, Vth, Is + h) - 
            EKV_Model::calculate_V(K, Vth, Is))
            /h;
}


double EKV_Model::calculate_V_K_K(double K, double Vth, double Is) {
    return (EKV_Model::calculate_V_K(K + h, Vth, Is) - 
            EKV_Model::calculate_V_K(K, Vth, Is))
            /h;
}

double EKV_Model::calculate_V_K_Vth(double K, double Vth, double Is) {
    return (EKV_Model::calculate_V_Vth(K + h, Vth, Is) - 
            EKV_Model::calculate_V_Vth(K, Vth, Is))
            /h;
}

double EKV_Model::calculate_V_K_Is(double K, double Vth, double Is) {
    return (EKV_Model::calculate_V_Is(K + h, Vth, Is) - 
            EKV_Model::calculate_V_Is(K, Vth, Is))
            /h;
}


double EKV_Model::calculate_V_Vth_K(double K, double Vth, double Is) {
    return (EKV_Model::calculate_V_K(K, Vth + h, Is) - 
            EKV_Model::calculate_V_K(K, Vth, Is))
            /h;
}

double EKV_Model::calculate_V_Vth_Vth(double K, double Vth, double Is) {
    return (EKV_Model::calculate_V_Vth(K, Vth + h, Is) - 
            EKV_Model::calculate_V_Vth(K, Vth, Is))
            /h;
}

double EKV_Model::calculate_V_Vth_Is(double K, double Vth, double Is) {
    return (EKV_Model::calculate_V_Is(K, Vth + h, Is) - 
            EKV_Model::calculate_V_Is(K, Vth, Is))
            /h;
}


double EKV_Model::calculate_V_Is_K(double K, double Vth, double Is) {
    return (EKV_Model::calculate_V_K(K, Vth, Is + h) - 
            EKV_Model::calculate_V_K(K, Vth, Is))
            /h;
}

double EKV_Model::calculate_V_Is_Vth(double K, double Vth, double Is) {
    return (EKV_Model::calculate_V_Vth(K, Vth, Is + h) - 
            EKV_Model::calculate_V_Vth(K, Vth, Is))
            /h;
}

double EKV_Model::calculate_V_Is_Is(double K, double Vth, double Is) {
    return (EKV_Model::calculate_V_Is(K, Vth, Is + h) - 
            EKV_Model::calculate_V_Is(K, Vth, Is))
            /h;
}


void EKV_Model::create_Hesian() {
    this->Hessian[0] = calculate_V_K_K(this->Parameters[0], this->Parameters[1], this->Parameters[2]);
    this->Hessian[1] = calculate_V_K_Vth(this->Parameters[0], this->Parameters[1], this->Parameters[2]);
    this->Hessian[2] = calculate_V_K_Is(this->Parameters[0], this->Parameters[1], this->Parameters[2]);
    this->Hessian[3] = calculate_V_Vth_K(this->Parameters[0], this->Parameters[1], this->Parameters[2]);
    this->Hessian[4] = calculate_V_Vth_Vth(this->Parameters[0], this->Parameters[1], this->Parameters[2]);
    this->Hessian[5] = calculate_V_Vth_Is(this->Parameters[0], this->Parameters[1], this->Parameters[2]);
    this->Hessian[6] = calculate_V_Is_K(this->Parameters[0], this->Parameters[1], this->Parameters[2]);
    this->Hessian[7] = calculate_V_Is_Vth(this->Parameters[0], this->Parameters[1], this->Parameters[2]);
    this->Hessian[8] = calculate_V_Is_Is(this->Parameters[0], this->Parameters[1], this->Parameters[2]);
}

void EKV_Model::create_Del_V() {
    this->DelV[0] = calculate_V_K(this->Parameters[0], this->Parameters[1], this->Parameters[2]);
    this->DelV[1] = calculate_V_Vth(this->Parameters[0], this->Parameters[1], this->Parameters[2]);
    this->DelV[2] = calculate_V_Is(this->Parameters[0], this->Parameters[1], this->Parameters[2]);
}

void EKV_Model::find_Parameters() {
    
    EKV_Model::create_Hesian();
    EKV_Model::create_Del_V();
    
    full_Matrix *HessianStruct = new full_Matrix();
    Global_Functions::create_Struct_From_Matrix(this->Hessian, HessianStruct, this->rank);
    
    full_Vector *DelVStruct = new full_Vector();
    Global_Functions::create_Struct_From_Vector(this->DelV, DelVStruct, this->rank);
    
    full_Vector *ParametersStruct = new full_Vector();
    Global_Functions::create_Struct_From_Vector(this->Parameters, ParametersStruct, this->rank);
    
    /*
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            cout << this->Hessian[i * 3 + j];
        }
        cout << endl;
    }
    */
    full_Matrix_Solver *solver = new full_Matrix_Solver(HessianStruct, DelVStruct);
    solver->l_U_Decomposition();
    solver->back_Substitution(ParametersStruct);
    
    this->Parameters = ParametersStruct->arr;
}



EKV_Model::EKV_Model(double K, double Vth, double Is) {
    this->VT = 0.026;
    this->h = pow(10, -8);
    this->rank = 3;
    
    this->Vgs = (double *)calloc(sizeOfOutputNMOS, sizeof(double));
    this->Vds = (double *)calloc(sizeOfOutputNMOS, sizeof(double));
    this->Ids = (double *)calloc(sizeOfOutputNMOS, sizeof(double));
    this->Parameters = (double *)calloc(this->rank, sizeof(double));
    this->Parameters[0] = K;
    this->Parameters[1] = Vth;
    this->Parameters[2] = Is;
    
    load_OutputNMOS *load = new load_OutputNMOS();
    load->getIdsPointer(this->Ids);
    load->getVdsPointer(this->Vds);
    load->getVgsPointer(this->Ids);
    
    cout << this->Ids[10] << endl;
    
    this->Hessian = (double *)calloc(this->rank * this->rank, sizeof(double));
    this->DelV = (double *)calloc(this->rank, sizeof(double));
    
    EKV_Model::find_Parameters();
}

EKV_Model::~EKV_Model() {
}