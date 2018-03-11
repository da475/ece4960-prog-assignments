
/* 
 * Author: Vishisht, Deepak
 * Netids: vmt28 and da475
 * Copyright @ 2018 Vishisht and Deepak. All rights reserved

 * Created on March 4, 2018, 8:23 PM
 * File:   Assignment2_Main.cpp
 * Desc: Main code file to implement matrix solvers and test them
 */

// Including the common header
#include "Assignment2_Header.h"

// Main function of the program
int main(int argc, char** argv) {

    Matrix_Operations *operations = new Matrix_Operations();
    
    Load_Mat1 *load = new Load_Mat1();
    // Mat1 Loaded
    
    // Create arrays for the different types of b
    double *b1 = (double *)malloc(load->get_Rank() * sizeof(double));
    double *b2 = (double *)malloc(load->get_Rank() * sizeof(double));
    double *b3 = (double *)malloc(load->get_Rank() * sizeof(double));
    // Create arrays for the different types of b
    
    // Load the values to the B array
    for (int i = 0; i < load->get_Rank(); i++) {
        if (i == 0) b1[i] = 1;
        else b1[i] = 0;
        if (i == 4) b2[i] = 1;
        else b2[i] = 0;
        b3[i] = 1;
    }
    
    // Create the vectors for all the b
    full_Vector *bJacobi1 = new full_Vector();
    full_Vector *bJacobi2 = new full_Vector();
    full_Vector *bJacobi3 = new full_Vector();
    if (Global_Functions::Create_Pointer_From_Vector((double *)b1, bJacobi1, load->get_Rank())) return ERROR;
    if (Global_Functions::Create_Pointer_From_Vector((double *)b2, bJacobi2, load->get_Rank())) return ERROR;
    if (Global_Functions::Create_Pointer_From_Vector((double *)b3, bJacobi3, load->get_Rank())) return ERROR;
    
    // Create the vector where x will be loaded
    full_Vector *xJacobi1 = new full_Vector();
    full_Vector *xJacobi2 = new full_Vector();
    
    // Create full matrix from the mat1
    full_Matrix *AJacobi = new full_Matrix();
    Global_Functions::Create_Full_Matrix(AJacobi, load->get_Sparse_Matrix());

    // The b that will be created after the product of A and the x received from the result of Jacobi
    full_Vector *bJacobiCheck1 = new full_Vector();
    full_Vector *bJacobiCheck2 = new full_Vector();
    
    cout << "Result for b = [1,0,0,0,....,0]" << endl;
    // Implement full matrix and sparse matrix jacobi with b(all 0s)
    Jacobi *implementation_Jacobi1 = new Jacobi(AJacobi, bJacobi1, xJacobi1);
    Jacobi *implementation_Jacobi2 = new Jacobi(load->get_Sparse_Matrix(), bJacobi1, xJacobi2);
   
    // Check if the result of the result of both Jacobi are same
    if (Global_Functions::norm_Vector_Vector(xJacobi1,xJacobi2)) return ERROR;
    cout << "The X produced by both Full Matrix Jacobi and Sparse Matrix Jacobi are same" << endl;
    operations->productAxFull(AJacobi,xJacobi1,bJacobiCheck1);
    operations->productAxSparse(load->get_Sparse_Matrix(),xJacobi2,bJacobiCheck2);
    // Check the residual Norm for full Matrix Jacobi Result
    cout << "The residual norm in case of the result of full matrix jacobi is " << 
            Global_Functions::normalized_Residual_Norm_Full_Matrix(AJacobi,xJacobi1,bJacobi1,bJacobiCheck1) << endl;
    // Check the residual Norm for sparse Matrix Jacobi Result
    cout << "The residual norm in case of the result of sparse matrix jacobi is " << 
            Global_Functions::normalized_Residual_Norm_Sparse_Matrix(load->get_Sparse_Matrix(),xJacobi1,bJacobi1,bJacobiCheck2) << endl << endl << endl;
    

    cout << "Result for b = [0,0,0,0,1,..,0]" << endl;
    Jacobi *implementation_Jacobi3 = new Jacobi(AJacobi, bJacobi2, xJacobi1);
    Jacobi *implementation_Jacobi4 = new Jacobi(load->get_Sparse_Matrix(), bJacobi2, xJacobi2);
    
    // Check if the result of the result of both Jacobi are same
    if (Global_Functions::norm_Vector_Vector(xJacobi1,xJacobi2)) return ERROR;
    cout << "The X produced by both Full Matrix Jacobi and Sparse Matrix Jacobi are same" << endl;
    operations->productAxFull(AJacobi,xJacobi1,bJacobiCheck1);
    operations->productAxSparse(load->get_Sparse_Matrix(),xJacobi2,bJacobiCheck2);
    // Check the residual Norm for full Matrix Jacobi Result
    cout << "The residual norm in case of the result of full matrix jacobi is " << 
            Global_Functions::normalized_Residual_Norm_Full_Matrix(AJacobi,xJacobi1,bJacobi2,bJacobiCheck1) << endl;
    // Check the residual Norm for sparse Matrix Jacobi Result
    cout << "The residual norm in case of the result of sparse matrix jacobi is " << 
            Global_Functions::normalized_Residual_Norm_Sparse_Matrix(load->get_Sparse_Matrix(),xJacobi1,bJacobi2,bJacobiCheck2) << endl << endl << endl;
    

    cout << "Result for b = [1,1,1,1,....,1]" << endl;
    Jacobi *implementation_Jacobi5 = new Jacobi(AJacobi, bJacobi3, xJacobi1);
    Jacobi *implementation_Jacobi6 = new Jacobi(load->get_Sparse_Matrix(), bJacobi3, xJacobi2);
    
    // Check if the result of the result of both Jacobi are same
    if (Global_Functions::norm_Vector_Vector(xJacobi1,xJacobi2)) return ERROR;
    cout << "The X produced by both Full Matrix Jacobi and Sparse Matrix Jacobi are same" << endl;
    operations->productAxFull(AJacobi,xJacobi1,bJacobiCheck1);
    operations->productAxSparse(load->get_Sparse_Matrix(),xJacobi2,bJacobiCheck2);
    // Check the residual Norm for full Matrix Jacobi Result
    cout << "The residual norm in case of the result of full matrix jacobi is " << 
            Global_Functions::normalized_Residual_Norm_Full_Matrix(AJacobi,xJacobi1,bJacobi3,bJacobiCheck1) << endl;
    // Check the residual Norm for sparse Matrix Jacobi Result
    cout << "The residual norm in case of the result of sparse matrix jacobi is " << 
            Global_Functions::normalized_Residual_Norm_Sparse_Matrix(load->get_Sparse_Matrix(),xJacobi1,bJacobi3,bJacobiCheck2) << endl << endl;
    
    return NO_ERROR;
}
