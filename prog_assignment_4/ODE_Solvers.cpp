/* 
 * Author: Vishisht, Deepak
 * Netids: vmt28 and da475
 * Copyright @ 2018 Vishisht and Deepak. All rights reserved

 * Created on April 18, 2018, 5:19 PM
 * File: ODE_Solvers.cpp
 * Desc: Forward Euler, Runge Kutta 34 and 
 *       Time Adaptive Runge Kutta have been implemented here
 */

#include "ODE_Solvers.h"

// Setting the global variable for adaptive time
double rel_tolerance = 1e-7;
double abs_tolerance = 1e-4;

// Initializes the first value according to the initial Value
// Exception handling is done by all the Global_Functions
void ODE_Solvers::initializeValue(arrayMat *values)
{
    Global_Functions::column_Shifting(this->initialValue, values->arr[0], values->arr[0]);
    #if EXCEPTION_HANDLING
        for (int i = 0; i < values->rank; i++)
        {
            if (isinf(values->arr[0]->col[i])) return IS_INF_NINF;
            if (isnan(values->arr[0]->col[i])) return IS_NAN;
        }
    #endif  
}

// Implements the forward Euler ODE Solver
// Exception handling is done by all the Global_Functions
void ODE_Solvers::forward_Euler(arrayMat *values)
{
    if (values->dim != this->time->dim) throw UNMATCHED_DIM;
    
    int dim = values->dim;
    
    // Initialize the first values
    initializeValue(values);
    
    // Finds phi and uses the to calculate the next xValue.
    // Exception handling is done by all the Global_Functions
    for (int i = 0; i < dim - 1; i++)
    {
        arrayMatCol *temp = new arrayMatCol();
        arrayMatCol *temp1 = new arrayMatCol();
        arrayMatCol *temp2 = new arrayMatCol();
        
        this->func(values->arr[i], this->time->arr[i], temp);
        Global_Functions::column_Scaling(this->delT->arr[i], temp, temp1);
        Global_Functions::column_Addition(temp1, values->arr[i], temp2);
        values->arr[i + 1] = temp2;
    } 
}

// Finds k1 for RK34
// Exception handling is done by all the Global_Functions
void ODE_Solvers::rk34_K1(arrayMatCol *k1, arrayMatCol *value, double time)
{
    if (value->rank != k1->rank) throw UNMATCHED_RANK;
    
    this->func(value, time, k1);
}

// Finds k2 for RK34
// Exception handling is done by all the Global_Functions
void ODE_Solvers::rk34_K2(arrayMatCol *k2, arrayMatCol *value, double time, double delT, arrayMatCol *k1)
{
    if ((k2->rank != value->rank) || (k1->rank != k2->rank)) throw UNMATCHED_RANK;
    
    arrayMatCol *scaledK1 = new arrayMatCol();
    arrayMatCol *newValue = new arrayMatCol();
    
    Global_Functions::column_Scaling(0.5 * delT, k1, scaledK1);
    Global_Functions::column_Addition(value, scaledK1, newValue);
                 
    this->func(newValue, time + (0.5 * delT), k2);
}

// Finds k3 for RK34
// Exception handling is done by all the Global_Functions
void ODE_Solvers::rk34_K3(arrayMatCol *k3, arrayMatCol *value, double time, double delT, arrayMatCol *k2)
{
    if ((k3->rank != value->rank) || (k2->rank != k3->rank)) throw UNMATCHED_RANK;
    
    arrayMatCol *scaledK2 = new arrayMatCol();
    arrayMatCol *newValue = new arrayMatCol();
    
    Global_Functions::column_Scaling(0.75 * delT, k2, scaledK2);
    Global_Functions::column_Addition(value, scaledK2, newValue);
                 
    this->func(newValue, time + (0.75 * delT), k3);   
}

// Finds k4 for RK34
// Exception handling is done by all the Global_Functions
void ODE_Solvers::rk34_K4(arrayMatCol *k4, arrayMatCol *value, double time, double delT, arrayMatCol *k3)
{
    if ((k4->rank != value->rank) || (k3->rank != k4->rank)) throw UNMATCHED_RANK;
    
    arrayMatCol *scaledK3 = new arrayMatCol();
    arrayMatCol *newValue = new arrayMatCol();
    
    Global_Functions::column_Scaling(delT, k3, scaledK3);
    Global_Functions::column_Addition(value, scaledK3, newValue);
                 
    this->func(newValue, time + delT, k4);
}

// Calculates the next delT
// Exception handling is done by all the Global_Functions
double ODE_Solvers::new_TimeSteps(arrayMatCol *err_estimate, arrayMatCol *value, double delT)
{
    if ((err_estimate->rank != value->rank)) throw UNMATCHED_RANK;
    
    double numerator = rel_tolerance;
    double errNorm = Global_Functions::calculate_Norm(err_estimate);
    double valueNorm = Global_Functions::calculate_Norm(value);
    double denominator = errNorm/(valueNorm + abs_tolerance);
    return delT * cbrt(numerator/denominator);
}

// Runge Kutta 34 with and without time adapt
// Exception handling is done by all the Global_Functions
void ODE_Solvers::rk34(arrayMat *valuesOriginal, fullVect*timeOiginal, bool adapt)
{
    
    int rank = valuesOriginal->rank;
    
    // Creates a vector for storing the new time, values and delT
    vector<arrayMatCol*> *values = new vector<arrayMatCol*>();
    vector<double> *time = new vector<double>();
    vector<double> *delT = new vector<double>();
    
    // Creates the first initial value
    arrayMatCol *initial = new arrayMatCol();
    initial->rank = rank;
    initial->col = (double *)calloc(rank, sizeof(double));
    for (int i = 0; i < rank; i++) initial->col[i] = this->initialValue;
    
    // pushes the initial value to values
    values->push_back(initial);
    time->push_back(this->start);
    delT->push_back(this->step);
    
    // initializes k1, k2, k3 and k4 for storing values
    arrayMatCol *k1 = new arrayMatCol();
    arrayMatCol *k2 = new arrayMatCol();
    arrayMatCol *k3 = new arrayMatCol();
    arrayMatCol *k4 = new arrayMatCol();
    
    // set the rank of ks
    k1->rank = rank;
    k2->rank = rank;
    k3->rank = rank;
    k4->rank = rank;
    
    // initializes the MatCol of ks
    k1->col = (double *)calloc(rank, sizeof(double));
    k2->col = (double *)calloc(rank, sizeof(double));
    k3->col = (double *)calloc(rank, sizeof(double));
    k4->col = (double *)calloc(rank, sizeof(double));
    
    int iter = 0;
    do
    {
        // Finds the k values
        rk34_K1(k1, (*values)[iter], (*time)[iter]);
        rk34_K2(k2, (*values)[iter], (*time)[iter], (*delT)[iter], k1);
        rk34_K3(k3, (*values)[iter], (*time)[iter], (*delT)[iter], k2);
        rk34_K4(k4, (*values)[iter], (*time)[iter], (*delT)[iter], k3);
        
        // Initializes the temp values for matrix manipulations
        arrayMatCol *k1Scaled = new arrayMatCol();
        arrayMatCol *k2Scaled = new arrayMatCol();
        arrayMatCol *k3Scaled = new arrayMatCol();
        arrayMatCol *k4Scaled = new arrayMatCol();
        arrayMatCol *kSum1 = new arrayMatCol();
        arrayMatCol *kSum2 = new arrayMatCol();
        arrayMatCol *kSum3 = new arrayMatCol();
        arrayMatCol *kSumScaled = new arrayMatCol();
        arrayMatCol *nextValue = new arrayMatCol();
        nextValue->rank = rank;
        nextValue->col = (double *)calloc(rank, sizeof(double));
        values->push_back(nextValue);
        
        // Column manipulations for finding next xValue
        Global_Functions::column_Scaling(7, k1, k1Scaled);
        Global_Functions::column_Scaling(6, k2, k2Scaled);
        Global_Functions::column_Scaling(8, k3, k3Scaled);
        Global_Functions::column_Scaling(3, k4, k4Scaled);
        
        Global_Functions::column_Addition(k1Scaled, k2Scaled, kSum1);
        Global_Functions::column_Addition(k3Scaled, k4Scaled, kSum2);
        Global_Functions::column_Addition(kSum1, kSum2, kSum3);

        Global_Functions::column_Scaling((*delT)[iter] / 24.0, kSum3, kSumScaled);
        Global_Functions::column_Addition((*values)[iter], kSumScaled, (*values)[iter + 1]);

        // Check if time adaptivity is required
        if (adapt)
        {
            // Initilazes the temp values for matrix maniputaions
            arrayMatCol *k1ErrorScaled = new arrayMatCol();
            arrayMatCol *k2ErrorScaled = new arrayMatCol();
            arrayMatCol *k3ErrorScaled = new arrayMatCol();
            arrayMatCol *k4ErrorScaled = new arrayMatCol();
            arrayMatCol *kErrorSum1 = new arrayMatCol();
            arrayMatCol *kErrorSum2 = new arrayMatCol();
            arrayMatCol *kErrorSum3 = new arrayMatCol();
            arrayMatCol *err_Estimate = new arrayMatCol();
            err_Estimate->rank = rank;
            err_Estimate->col = (double *)calloc(rank, sizeof(double));

            // Column manipulations for finding next error estimate
            Global_Functions::column_Scaling(-5, k1, k1ErrorScaled);
            Global_Functions::column_Scaling(6, k2, k2ErrorScaled);
            Global_Functions::column_Scaling(8, k3, k3ErrorScaled);
            Global_Functions::column_Scaling(-9, k4, k4ErrorScaled);

            Global_Functions::column_Addition(k1ErrorScaled, k2ErrorScaled, kErrorSum1);
            Global_Functions::column_Addition(k3ErrorScaled, k4ErrorScaled, kErrorSum2);
            Global_Functions::column_Addition(kErrorSum1, kErrorSum2, kErrorSum3);

            // Find the next delT and set push the new values in vector
            Global_Functions::column_Scaling((*delT)[iter] / 72.0, kErrorSum3, err_Estimate);
            time->push_back((*time)[iter] + (*delT)[iter]);
            delT->push_back(new_TimeSteps(err_Estimate, (*values)[iter + 1], (*delT)[iter]));
        }
        else 
        {
            time->push_back((*time)[iter] + (*delT)[iter]);
            delT->push_back((*delT)[iter]);
        }
        iter++;
    } while((*time)[iter] < this->stop);
    
    // Convert the vectors to fullMat
    Global_Functions::convert_Vector_FullMat(values, valuesOriginal);
    Global_Functions::convert_Vector_Vector(time, timeOiginal);
}

// Constructor
ODE_Solvers::ODE_Solvers(double initialValue, fullVect *time, fullVect *delT, double start, double stop, double step, void(*func)(arrayMatCol*,double,arrayMatCol*))
{
    if (time->dim || delT->dim) throw UNMATCHED_DIM;
    
    this->initialValue = initialValue;
    this->time = time;
    this->delT = delT;
    this->start = start;
    this->stop = stop;
    this->step = step;
    this->func = func;
}

// Destructor
ODE_Solvers::~ODE_Solvers()
{
    if (this->time != NULL) free(this->time);
    if (this->delT != NULL) free(this->delT);
}