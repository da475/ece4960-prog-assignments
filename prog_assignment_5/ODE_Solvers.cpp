/* 
 * Author: Vishisht Tiwari, Deepak Agarwal
 * Netids: vmt28 and da475
 * Copyright @ 2018 Vishisht Tiwari and Deepak Agarwal. All rights reserved

 * Created on May 15, 2018, 7:27 PM
 * File: ODE_Solvers.cpp
 * Desc: Forward Euler, Runge Kutta 34 and 
 *       Time Adaptive Runge Kutta have been implemented here
 */

#include "ODE_Solvers.h"

// Setting the global variable for adaptive time
double rel_tolerance = 1e-7;
double abs_tolerance = 1e-4;
double tolerance1 = 1e-1;
double tolerance2 = 1e-3;
double tolerance3 = 2;
double tolerance4 = 0.5;

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

// Finds k1 for RK34
// Exception handling is done by all the Global_Functions
void ODE_Solvers::rk1(arrayMatCol *k1, arrayMatCol *value, double time)
{
    if (value->rank != k1->rank) throw UNMATCHED_RANK;
    
    this->func(value, time, k1, this->order);
}

// Finds k2 for RK34
// Exception handling is done by all the Global_Functions
void ODE_Solvers::rk2(arrayMatCol *k2, arrayMatCol *value, double time, double delT, arrayMatCol *k1)
{
    if ((k2->rank != value->rank) || (k1->rank != k2->rank)) throw UNMATCHED_RANK;
    
    arrayMatCol *scaledK1 = new arrayMatCol();
    arrayMatCol *newValue = new arrayMatCol();
    
    Global_Functions::column_Scaling(0.5 * delT, k1, scaledK1);
    Global_Functions::column_Addition(value, scaledK1, newValue);
                 
    this->func(newValue, time + (0.5 * delT), k2, this->order);
}

// Finds k3 for RK34
// Exception handling is done by all the Global_Functions
void ODE_Solvers::rk3(arrayMatCol *k3, arrayMatCol *value, double time, double delT, arrayMatCol *k2)
{
    if ((k3->rank != value->rank) || (k2->rank != k3->rank)) throw UNMATCHED_RANK;
    
    arrayMatCol *scaledK2 = new arrayMatCol();
    arrayMatCol *newValue = new arrayMatCol();
    
    Global_Functions::column_Scaling(0.75 * delT, k2, scaledK2);
    Global_Functions::column_Addition(value, scaledK2, newValue);
                 
    this->func(newValue, time + (0.75 * delT), k3, this->order);   
}

// Finds k4 for RK34
// Exception handling is done by all the Global_Functions
void ODE_Solvers::rk4(arrayMatCol *k4, arrayMatCol *value, double time, double delT, arrayMatCol *k3)
{
    if ((k4->rank != value->rank) || (k3->rank != k4->rank)) throw UNMATCHED_RANK;
    
    arrayMatCol *scaledK3 = new arrayMatCol();
    arrayMatCol *newValue = new arrayMatCol();
    
    Global_Functions::column_Scaling(delT, k3, scaledK3);
    Global_Functions::column_Addition(value, scaledK3, newValue);
                 
    this->func(newValue, time + delT, k4, this->order);
}

// Calculates the next delT
// Exception handling is done by all the Global_Functions
double ODE_Solvers::newTimeSteps(arrayMatCol *err_estimate, arrayMatCol *value, double delT, int typeTimeSteps)
{
    if ((err_estimate->rank != value->rank)) throw UNMATCHED_RANK;
    
    if (typeTimeSteps == BISECTION)
    {
        double numerator = Global_Functions::calculate_Norm(err_estimate);
        double denominator = Global_Functions::calculate_Norm(value);
        if ((numerator/denominator) > tolerance1)
        {
            return delT/2;
        }
        else if ((numerator/denominator) < tolerance2)
        {
            return 2*delT;
        }
        else if (((numerator/denominator) <= tolerance1) && ((numerator/denominator) >= tolerance2))
        {
            return delT;
        }
        else 
        {
            throw ERROR;
        }
    }
    else if (typeTimeSteps == CONSTANT_E_H)
    {
        double numerator = Global_Functions::calculate_Norm(err_estimate);
        double valueNorm = Global_Functions::calculate_Norm(value);
        double denominator = (rel_tolerance * valueNorm) + abs_tolerance;
        double r = (numerator/denominator);
        if ((r > tolerance3) || (r < tolerance4))
        {
            return delT/pow(r,0.01);
        }
        else if ((r <= tolerance3) && (r >= tolerance4))
        {
            return delT;
        }
        else 
        {
            throw ERROR;
        }
    }
    else if (typeTimeSteps == USE_O_H)
    {
        double numerator = rel_tolerance;
        double errNorm = Global_Functions::calculate_Norm(err_estimate);
        double valueNorm = Global_Functions::calculate_Norm(value);
        double denominator = errNorm/(valueNorm + abs_tolerance);
        return delT * cbrt(numerator/denominator);
    }
    else
    {
        throw ERROR;
    }
}

void ODE_Solvers::nextTimeSteps(int rank, arrayMatCol *k1, arrayMatCol *k2, arrayMatCol *k3, arrayMatCol *k4, vector<arrayMatCol*> *values, vector<double> *time, vector<double> *delT, int iter, int typeRK, int typeTimeSteps)
{
    // Initializes the temp values for matrix manipulations
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
    
    if (typeRK == TWOTHREE)
    {
        // Column manipulations for finding next error estimate
        Global_Functions::column_Scaling(-2, k1, k1ErrorScaled);
        Global_Functions::column_Scaling(6, k2, k2ErrorScaled);
        Global_Functions::column_Scaling(-4, k3, k3ErrorScaled);

        Global_Functions::column_Addition(k1ErrorScaled, k2ErrorScaled, kErrorSum1);
        Global_Functions::column_Addition(kErrorSum1, k3ErrorScaled, kErrorSum2);

        // Find the next delT and set push the new values in vector
        Global_Functions::column_Scaling((*delT)[iter] / 9.0, kErrorSum2, err_Estimate);
    }
    else if (typeRK == THREEFOUR)
    {
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
    }
    time->push_back((*time)[iter] + (*delT)[iter]);
    delT->push_back(ODE_Solvers::newTimeSteps(err_Estimate, (*values)[iter + 1], (*delT)[iter], typeTimeSteps));
}

// Runge Kutta with and without time adapt
// Exception handling is done by all the Global_Functions
void ODE_Solvers::rungeKutta(arrayMat *valuesOriginal, fullVect*timeOiginal, int typeRK, int typeTimeSteps, bool adapt)
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
        rk1(k1, (*values)[iter], (*time)[iter]);
        rk2(k2, (*values)[iter], (*time)[iter], (*delT)[iter], k1);
        rk3(k3, (*values)[iter], (*time)[iter], (*delT)[iter], k2);
        rk4(k4, (*values)[iter], (*time)[iter], (*delT)[iter], k3);
        
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
        if (typeRK == TWOTHREE)
        {
            Global_Functions::column_Scaling(2, k1, k1Scaled);
            Global_Functions::column_Scaling(3, k2, k2Scaled);
            Global_Functions::column_Scaling(4, k3, k3Scaled);

            Global_Functions::column_Addition(k1Scaled, k2Scaled, kSum1);
            Global_Functions::column_Addition(kSum1, k3Scaled, kSum2);

            Global_Functions::column_Scaling((*delT)[iter] / 9.0, kSum2, kSumScaled);
        }
        else if (typeRK == THREEFOUR)
        {
            Global_Functions::column_Scaling(7, k1, k1Scaled);
            Global_Functions::column_Scaling(6, k2, k2Scaled);
            Global_Functions::column_Scaling(8, k3, k3Scaled);
            Global_Functions::column_Scaling(3, k4, k4Scaled);

            Global_Functions::column_Addition(k1Scaled, k2Scaled, kSum1);
            Global_Functions::column_Addition(k3Scaled, k4Scaled, kSum2);
            Global_Functions::column_Addition(kSum1, kSum2, kSum3);

            Global_Functions::column_Scaling((*delT)[iter] / 24.0, kSum3, kSumScaled);
        }
        Global_Functions::column_Addition((*values)[iter], kSumScaled, (*values)[iter + 1]);

        // Check if time adaptivity is required
        if (adapt)
        {
            ODE_Solvers::nextTimeSteps(rank, k1, k2, k3, k4, values, time, delT, iter, typeRK, typeTimeSteps);

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
ODE_Solvers::ODE_Solvers(double initialValue, fullVect *time, fullVect *delT, double start, double stop, double step, void(*func)(arrayMatCol*,double,arrayMatCol*,double), double order)
{
    if (time->dim || delT->dim) throw UNMATCHED_DIM;
    
    this->initialValue = initialValue;
    this->time = time;
    this->delT = delT;
    this->start = start;
    this->stop = stop;
    this->step = step;
    this->func = func;
    this->order = order;
}

// Destructor
ODE_Solvers::~ODE_Solvers()
{
    if (this->time != NULL) free(this->time);
    if (this->delT != NULL) free(this->delT);
}