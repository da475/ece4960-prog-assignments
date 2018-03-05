/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   MatrixOperations.h
 * Author: Vishisht and Deepak
 *
 * Created on February 25, 2018, 8:54 PM
 */

#ifndef MATRIXOPERATIONS_H
#define MATRIXOPERATIONS_H

class MatrixOperations {
private:
    
    int rank;
    long nZ;
    int *arr;
    int *value;
    int *rowPtr;
    int *colInd;
    
public:

    // Constructor for small matrices where full-format matrix is known
    MatrixOperations(int *arr, int rank, long nZ);

    // Constructor for very large matrices which cannot be loaded in full-matrix form
    MatrixOperations(int *row, int *col, int *val, int nonzero);

    // Destructor
    ~MatrixOperations();

    // Function to print a matrix in full-matrix format
    void printMatrixFull();

    // Function to print a matrix in full-matrix format
    void printMatrixSparse();

    // Function to convert a matrix to row-compressed format
    void createMatrix();


    // Function to do row-permutation operation in full matrix format
    void rowPermuteFull(int i, int j);


    // Function to do row-permutation operation in sparse matrix format
    void rowPermuteSparse(int i, int j);


    // Function to do row-scaling operation in full matrix format
    void rowScaleFull(int i, int j, double a);


    // Function to do row-scaling operation in sparse matrix format
    void rowScaleSparse(int i, int j, double a);


    // Function to do product operation in full matrix format
    void productAxFull(int i, int j, double a);


    // Function to do product operation in sparse matrix format
    void productAxSparse(int i, int j, double a);

};

#endif /* MATRIXOPERATIONS */

