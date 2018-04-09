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
        V += (idModel - idMeasured) * (idModel - idMeasured);
    }
    return V;
}


double EKV_Model::calculate_V_K(double K, double Vth, double Is) {
    return (EKV_Model::calculate_V(K + (K * pert), Vth, Is) - 
            EKV_Model::calculate_V(K, Vth, Is))
            /(K * pert);
}

double EKV_Model::calculate_V_Vth(double K, double Vth, double Is) {
    return (EKV_Model::calculate_V(K, Vth + (Vth * pert), Is) - 
            EKV_Model::calculate_V(K, Vth, Is))
            /(Vth * pert);
}

double EKV_Model::calculate_V_Is(double K, double Vth, double Is) {
    return (EKV_Model::calculate_V(K, Vth, Is + (Is * pert)) - 
            EKV_Model::calculate_V(K, Vth, Is))
            /(Is * pert);
}



double EKV_Model::calculate_V_K_K(double K, double Vth, double Is) {
    return (EKV_Model::calculate_V(K + (2 * K * pert), Vth, Is) - 
            EKV_Model::calculate_V(K, Vth, Is))
            /((K * pert) * (K * pert));
}

double EKV_Model::calculate_V_K_Vth(double K, double Vth, double Is) {
    return (EKV_Model::calculate_V(K + (K * pert), Vth + (Vth * pert), Is) - 
            EKV_Model::calculate_V(K, Vth, Is))
            /((K * pert) * (Vth * pert));
}

double EKV_Model::calculate_V_K_Is(double K, double Vth, double Is) {
    return (EKV_Model::calculate_V(K + (K * pert), Vth, Is + (Is * pert)) - 
            EKV_Model::calculate_V(K, Vth, Is))
            /((K * pert) * (Is * pert));
}


double EKV_Model::calculate_V_Vth_K(double K, double Vth, double Is) {
    return (EKV_Model::calculate_V(K + (K * pert), Vth + (Vth * pert), Is) - 
            EKV_Model::calculate_V(K, Vth, Is))
            /((Vth * pert) * (K * pert));
}

double EKV_Model::calculate_V_Vth_Vth(double K, double Vth, double Is) {
    return (EKV_Model::calculate_V(K, Vth + (2 * Vth * pert), Is) - 
            EKV_Model::calculate_V(K, Vth, Is))
            /((Vth * pert) * (Vth * pert));
}

double EKV_Model::calculate_V_Vth_Is(double K, double Vth, double Is) {
    return (EKV_Model::calculate_V(K, Vth + (Vth * pert), Is + (Is * pert)) - 
            EKV_Model::calculate_V(K, Vth, Is))
            /((Vth * pert) * (Is * pert));
}


double EKV_Model::calculate_V_Is_K(double K, double Vth, double Is) {
    return (EKV_Model::calculate_V(K + (K * pert), Vth, Is + (Is * pert)) - 
            EKV_Model::calculate_V(K, Vth, Is))
            /((Is * pert) * (K * pert));
}

double EKV_Model::calculate_V_Is_Vth(double K, double Vth, double Is) {
    return (EKV_Model::calculate_V(K, Vth + (Vth * pert), Is + (Is * pert)) - 
            EKV_Model::calculate_V(K, Vth, Is))
            /((Is * pert) * (Vth * pert));
}

double EKV_Model::calculate_V_Is_Is(double K, double Vth, double Is) {
    return (EKV_Model::calculate_V(K, Vth, Is + (2 * Is * pert)) - 
            EKV_Model::calculate_V(K, Vth, Is))
            /(Is * pert) * (Is * pert);
}




//double EKV_Model::calculate_V_K_K(double K, double Vth, double Is) {
//    return (EKV_Model::calculate_V_K(K + (K * pert), Vth, Is) - 
//            EKV_Model::calculate_V_K(K, Vth, Is))
//            /(K * pert);
//}
//
//double EKV_Model::calculate_V_K_Vth(double K, double Vth, double Is) {
//    return (EKV_Model::calculate_V_Vth(K + (K * pert), Vth, Is) - 
//            EKV_Model::calculate_V_Vth(K, Vth, Is))
//            /(K * pert);
//}
//
//double EKV_Model::calculate_V_K_Is(double K, double Vth, double Is) {
//    return (EKV_Model::calculate_V_Is(K + (K * pert), Vth, Is) - 
//            EKV_Model::calculate_V_Is(K, Vth, Is))
//            /(K * pert);
//}
//
//
//double EKV_Model::calculate_V_Vth_K(double K, double Vth, double Is) {
//    return (EKV_Model::calculate_V_K(K, Vth + (Vth * pert), Is) - 
//            EKV_Model::calculate_V_K(K, Vth, Is))
//            /(Vth * pert);
//}
//
//double EKV_Model::calculate_V_Vth_Vth(double K, double Vth, double Is) {
//    return (EKV_Model::calculate_V_Vth(K, Vth + (Vth * pert), Is) - 
//            EKV_Model::calculate_V_Vth(K, Vth, Is))
//            /(Vth * pert);
//}
//
//double EKV_Model::calculate_V_Vth_Is(double K, double Vth, double Is) {
//    return (EKV_Model::calculate_V_Is(K, Vth + (Vth * pert), Is) - 
//            EKV_Model::calculate_V_Is(K, Vth, Is))
//            /(Vth * pert);
//}
//
//
//double EKV_Model::calculate_V_Is_K(double K, double Vth, double Is) {
//    return (EKV_Model::calculate_V_K(K, Vth, Is + (Is * pert)) - 
//            EKV_Model::calculate_V_K(K, Vth, Is))
//            /(Is * pert);
//}
//
//double EKV_Model::calculate_V_Is_Vth(double K, double Vth, double Is) {
//    return (EKV_Model::calculate_V_Vth(K, Vth, Is + (Is * pert)) - 
//            EKV_Model::calculate_V_Vth(K, Vth, Is))
//            /(Is * pert);
//}
//
//double EKV_Model::calculate_V_Is_Is(double K, double Vth, double Is) {
//    return (EKV_Model::calculate_V_Is(K, Vth, Is + (Is * pert)) - 
//            EKV_Model::calculate_V_Is(K, Vth, Is))
//            /(Is * pert);
//}

void EKV_Model::create_Hesian() {
    this->Hessian[0] = EKV_Model::calculate_V_K_K(this->Parameters[0], this->Parameters[1], this->Parameters[2]);
    this->Hessian[1] = EKV_Model::calculate_V_Vth_K(this->Parameters[0], this->Parameters[1], this->Parameters[2]);
    this->Hessian[2] = EKV_Model::calculate_V_Is_K(this->Parameters[0], this->Parameters[1], this->Parameters[2]);
    this->Hessian[3] = EKV_Model::calculate_V_K_Vth(this->Parameters[0], this->Parameters[1], this->Parameters[2]);
    this->Hessian[4] = EKV_Model::calculate_V_Vth_Vth(this->Parameters[0], this->Parameters[1], this->Parameters[2]);
    this->Hessian[5] = EKV_Model::calculate_V_Is_Vth(this->Parameters[0], this->Parameters[1], this->Parameters[2]);
    this->Hessian[6] = EKV_Model::calculate_V_K_Is(this->Parameters[0], this->Parameters[1], this->Parameters[2]);
    this->Hessian[7] = EKV_Model::calculate_V_Vth_Is(this->Parameters[0], this->Parameters[1], this->Parameters[2]);
    this->Hessian[8] = EKV_Model::calculate_V_Is_Is(this->Parameters[0], this->Parameters[1], this->Parameters[2]);
}

void EKV_Model::create_Del_V() {
    this->DelV[0] = EKV_Model::calculate_V_K(this->Parameters[0], this->Parameters[1], this->Parameters[2]);
    this->DelV[1] = EKV_Model::calculate_V_Vth(this->Parameters[0], this->Parameters[1], this->Parameters[2]);
    this->DelV[2] = EKV_Model::calculate_V_Is(this->Parameters[0], this->Parameters[1], this->Parameters[2]);
}

double EKV_Model::lineSearch(double *parameters, double min, double max, double *tempParameters) {
    double *tempParametersMid = (double *)calloc(this->rank, sizeof(double));
    double *tempParametersMax = (double *)calloc(this->rank, sizeof(double));
    double *tempParametersMin = (double *)calloc(this->rank, sizeof(double));
    for (int i = 0; i < this->rank; i++) {
        tempParametersMid[i] = parameters[i];
        tempParametersMax[i] = parameters[i];
        tempParametersMin[i] = parameters[i];
    }
    double mid = (max + min)/2;
    
    for (int i = 0; i < this->rank; i++) {
        tempParametersMid[i] += mid * tempParameters[i];
        tempParametersMax[i] += max * tempParameters[i];
        tempParametersMin[i] += min * tempParameters[i];
    }
    
    double midValue = 
        ((tempParameters[0] * tempParameters[0]) / (tempParametersMid[0] * tempParametersMid[0])) + 
        ((tempParameters[1] * tempParameters[1]) / (tempParametersMid[1] * tempParametersMid[1])) + 
        ((tempParameters[2] * tempParameters[2]) / (tempParametersMid[2] * tempParametersMid[2]));
    double maxValue =
        ((tempParameters[0] * tempParameters[0]) / (tempParametersMax[0] * tempParametersMax[0])) + 
        ((tempParameters[1] * tempParameters[1]) / (tempParametersMax[1] * tempParametersMax[1])) + 
        ((tempParameters[2] * tempParameters[2]) / (tempParametersMax[2] * tempParametersMax[2]));
    double minValue =
        ((tempParameters[0] * tempParameters[0]) / (tempParametersMin[0] * tempParametersMin[0])) + 
        ((tempParameters[1] * tempParameters[1]) / (tempParametersMin[1] * tempParametersMin[1])) + 
        ((tempParameters[2] * tempParameters[2]) / (tempParametersMin[2] * tempParametersMin[2]));
    
    if ((abs(minValue - midValue) < 1e-7) && (abs(maxValue - midValue) < 1e-7)) {
        //cout << "mid" << endl;
        return mid;
    }
    else if ((midValue < minValue) && (midValue < maxValue)) {
        //cout << "midGreat" << endl;
        return mid;
    }
    else if (minValue < midValue) {
        //cout << "min" << endl;
        return EKV_Model::lineSearch(parameters, min, mid, tempParameters);
    }
        
    else if (maxValue < midValue) {
        //cout << "max" << endl;
        return EKV_Model::lineSearch(parameters, mid, max, tempParameters);
    }
    //cout << "none" << endl;
}

void EKV_Model::find_Parameters() { 
    
    full_Matrix *HessianStruct = new full_Matrix();
    full_Vector *DelVStruct = new full_Vector();
    full_Vector *ParametersStruct = new full_Vector();
    
    double absoluteResidual = 1.0, relativeResidual = 1.0, V = 0;
    int counter = 0;
    double t;
    do {
        EKV_Model::create_Hesian();
        EKV_Model::create_Del_V();        

        Global_Functions::create_Struct_From_Matrix(this->Hessian, HessianStruct, this->rank);
        Global_Functions::create_Struct_From_Vector(this->DelV, DelVStruct, this->rank);
        Global_Functions::create_Struct_From_Vector(this->DelParameters, ParametersStruct, this->rank);
        
        full_Matrix_Solver *solver = new full_Matrix_Solver(HessianStruct, DelVStruct);
        solver->l_U_Decomposition();
        solver->back_Substitution(ParametersStruct);
        
        t = EKV_Model::lineSearch(this->Parameters, 0, 100, ParametersStruct->arr);
        for (int i = 0; i < this->rank; i++) 
            this->Parameters[i] += t * ParametersStruct->arr[i];
        
        absoluteResidual =  ((ParametersStruct->arr[0] * ParametersStruct->arr[0]) + 
        (ParametersStruct->arr[1] * ParametersStruct->arr[1]) + 
        (ParametersStruct->arr[2] * ParametersStruct->arr[2]));
        
        relativeResidual = 
        ((ParametersStruct->arr[0] * ParametersStruct->arr[0]) / (this->Parameters[0] * this->Parameters[0])) + 
        ((ParametersStruct->arr[1] * ParametersStruct->arr[1]) / (this->Parameters[1] * this->Parameters[1])) + 
        ((ParametersStruct->arr[2] * ParametersStruct->arr[2]) / (this->Parameters[2] * this->Parameters[2]));

        counter++;
        
        V = EKV_Model::calculate_V(this->Parameters[0], this->Parameters[1], this->Parameters[2]);

    } while (relativeResidual > 5e-9);
    cout << "--------QN Covergence---------" << endl;
    cout << "Iterations: " << counter << endl;
    cout << "Kappa(K): " << this->Parameters[0] << endl;
    cout << "Threshold Voltage(Vth): " << this->Parameters[1] << endl;
    cout << "Source Current(Is): " << this->Parameters[2] << endl;
    cout << "Absolute Residual: " <<  absoluteResidual << endl;
    cout << "Relative Residual: " <<  relativeResidual << endl;
    cout << "V: " <<  V << endl;
}



EKV_Model::EKV_Model(double K, double Vth, double Is) {
    this->VT = 26e-3;
    this->rank = 3;
    
    this->Vgs = (double *)calloc(sizeOfOutputNMOS, sizeof(double));
    this->Vds = (double *)calloc(sizeOfOutputNMOS, sizeof(double));
    this->Ids = (double *)calloc(sizeOfOutputNMOS, sizeof(double));
    this->Parameters = (double *)calloc(this->rank, sizeof(double));
    this->DelParameters = (double *)calloc(this->rank, sizeof(double));
    this->Parameters[0] = K;
    this->Parameters[1] = Vth;
    this->Parameters[2] = Is;
    this->pert = 1e-4;
    
    load_OutputNMOS *load = new load_OutputNMOS();
    load->getIdsPointer(&(this->Ids));
    load->getVdsPointer(&(this->Vds));
    load->getVgsPointer(&(this->Vgs));
    
    this->Hessian = (double *)calloc(this->rank * this->rank, sizeof(double));
    this->DelV = (double *)calloc(this->rank, sizeof(double));

    
    EKV_Model::find_Parameters();
}

EKV_Model::~EKV_Model() {
}