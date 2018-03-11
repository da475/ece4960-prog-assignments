/* 
 * File:   Load_Mat1.cpp
 * Author: Vishisht, Deepak
 *
 * Created on March 4, 2018, 10:16 PM
 */

#include "Assignment2_Header.h"

void Load_Mat1::find_Number_Of_NonZero_Elements()
{
    matrix->nZ = 0;
    
    string line;
    ifstream matfile;
    matfile.open("colInd.csv");
    if (!matfile) {
        cout << "Couldn't open the file" << endl;
        exit(1);
    }

    while (getline(matfile, line)) ++matrix->nZ;
}

void Load_Mat1::find_Rank()
{
    matrix->rank = 0;
    
    string line;
    ifstream matfile;
    matfile.open("rowPtr.csv");
    if (!matfile) {
        cout << "Couldn't open the file" << endl;
        exit(1);
    }
    while (getline(matfile, line)) ++matrix->rank;
    matrix->rank -= 1;
}


void Load_Mat1::load_ColInd() 
{
    matrix->colInd = (int *)malloc(matrix->nZ * sizeof(int));
    
    string line;
    ifstream matfile;
    matfile.open("colInd.csv");
    if (!matfile) {
        cout << "Couldn't open the file" << endl;
        exit(1);
    }
    int counter = 0;
    while (getline(matfile, line)) {
        matrix->colInd[counter] = stoi(line) - 1;
        counter++;
    }
}

void Load_Mat1::load_RowPtr()
{
    matrix->rowPtr = (int *)malloc((matrix->rank + 1) * sizeof(int));
    
    string line;
    ifstream matfile;
    matfile.open("rowPtr.csv");
    if (!matfile) {
        cout << "Couldn't open the file" << endl;
        exit(1);
    }
    int counter = 0;
    while (getline(matfile, line)) {
        matrix->rowPtr[counter] = stoi(line) - 1;
        counter++;
    }
}

void Load_Mat1::load_Value() 
{
    matrix->value = (double *)malloc(matrix->nZ * sizeof(double));
    
    string line;
    ifstream matfile;
    matfile.open("value.csv");
    if (!matfile) {
        cout << "Couldn't open the file" << endl;
        exit(1);
    }
    int counter = 0;
    while (getline(matfile, line)) {
        matrix->value[counter] = stof(line);
        counter++;
    }
}

int Load_Mat1::get_Number_Of_NonZero_Elements()
{
    return matrix->nZ;
}

int Load_Mat1::get_Rank()
{
    return matrix->rank;
}

int* Load_Mat1::get_ColInd() 
{
    return matrix->colInd;
}

int* Load_Mat1::get_RowPtr() 
{
    return matrix->rowPtr;
}

double* Load_Mat1::get_Value() 
{
    return matrix->value;
}

sparse_Matrix* Load_Mat1::get_Sparse_Matrix() 
{
    return matrix;
}

Load_Mat1::Load_Mat1() {
    matrix = new sparse_Matrix();
    
    find_Number_Of_NonZero_Elements();
    find_Rank();
    load_ColInd();
    load_RowPtr();
    load_Value();
}

// Destructor
Load_Mat1::~Load_Mat1() {
    if (this->matrix->value) free(this->matrix->value);
    if (this->matrix->rowPtr) free(this->matrix->rowPtr);
    if (this->matrix->colInd) free(this->matrix->colInd);
    
    if (this->matrix) free(this->matrix);
}
