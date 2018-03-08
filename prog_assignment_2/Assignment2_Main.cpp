/* 
 * File:   Assignment2_Main.cpp
 * Author: Vishisht, Deepak
 *
 * Created on March 5, 2018, 12:10 AM
 */

// Including the common header
#include "Assignment2_Header.h"

// Main function of the program
int main(int argc, char** argv) {
    
    Matrix_Operations *operations = new Matrix_Operations();
    
    double array[5][5] = {
                    {1, 2, 0, 0, 3},
                    {4, 5, 6, 0, 0},
                    {0, 0, 0, 7, 8},
                    {0, 9, 0, 10, 0},
                    {11, 0, 0, 0, 12}};
    int rank = sizeof(array)/sizeof(array[0]);
    
    full_Matrix *Full_Matrix = new full_Matrix();
    if (Global_Functions::Create_Pointer_From_Matrix((double *)array, Full_Matrix, rank)) return 1;
    
    full_Matrix *Full_Matrix_Permute = new full_Matrix();
    if (Global_Functions::Create_Pointer_From_Matrix((double *)array, Full_Matrix_Permute, rank)) return 1;
    
    sparse_Matrix *Sparse_Matrix_Permute = new sparse_Matrix();
    Global_Functions::Create_Row_Compressed_Matrix(Full_Matrix, Sparse_Matrix_Permute);
    if(Global_Functions::norm_Full_Sparse_Matrix(Full_Matrix, Sparse_Matrix_Permute)) return 1;
    
    operations->rowPermuteFull(Full_Matrix_Permute,2,5);
    operations->rowPermuteSparse(Sparse_Matrix_Permute,2,5);
    if(Global_Functions::norm_Full_Sparse_Matrix(Full_Matrix_Permute, Sparse_Matrix_Permute)) return 1;
    
    
    
    
    full_Matrix *Full_Matrix_Scale = new full_Matrix();
    if (Global_Functions::Create_Pointer_From_Matrix((double *)array, Full_Matrix_Scale, rank)) return 1;
    
    sparse_Matrix *Sparse_Matrix_Scale = new sparse_Matrix();
    Global_Functions::Create_Row_Compressed_Matrix(Full_Matrix, Sparse_Matrix_Scale);
    if(Global_Functions::norm_Full_Sparse_Matrix(Full_Matrix, Sparse_Matrix_Scale)) return 1;
    
    operations->rowScaleFull(Full_Matrix_Scale,2,5,3);
    operations->rowScaleSparse(Sparse_Matrix_Scale,2,5,3);
    if(Global_Functions::norm_Full_Sparse_Matrix(Full_Matrix_Scale, Sparse_Matrix_Scale)) return 1;
    
    
    
    
    full_Matrix *Full_Matrix_Product = new full_Matrix();
    if (Global_Functions::Create_Pointer_From_Matrix((double *)array, Full_Matrix_Product, rank)) return 1;
    
    sparse_Matrix *Sparse_Matrix_Product = new sparse_Matrix();
    Global_Functions::Create_Row_Compressed_Matrix(Full_Matrix, Sparse_Matrix_Product);
    if(Global_Functions::norm_Full_Sparse_Matrix(Full_Matrix, Sparse_Matrix_Product)) return 1;
    
    double xFull[5] = {5.0, 4.0, 3.0, 2.0, 1.0};
    full_Vector *x = new full_Vector();
    if (Global_Functions::Create_Pointer_From_Vector((double *)xFull, x, rank)) return 1;
    
    full_Vector *b = new full_Vector();
    
    operations->productAxFull(Full_Matrix_Product,x,b);
    operations->productAxSparse(Sparse_Matrix_Product,x,b);
    
    if(Global_Functions::norm_Full_Sparse_Matrix(Full_Matrix_Scale, Sparse_Matrix_Scale)) return 1;
    
    
    /*

    
    
    
     ghgh
    
    double jacobiArray[3][3] = {{5,-2,3},{-3,9,1},{2,-1,-7}};
    int rankJacobi = sizeof(jacobiArray)/sizeof(jacobiArray[0]);
    
    double jacobiB[3] = {-1,2,3};

    full_Matrix *AJacobi = new full_Matrix();
    if (Global_Functions::Create_Pointer_From_Matrix((double *)jacobiArray, AJacobi, rankJacobi)) return 1;

    full_Vector *bJacobi = new full_Vector();
    if (Global_Functions::Create_Pointer_From_Vector((double *)jacobiB, bJacobi, rankJacobi)) return 1;
    
    full_Vector *xJacobi = new full_Vector();

    
    Jacobi *implementation_Jacobi1 = new Jacobi(AJacobi, bJacobi, xJacobi);
     */
    
    Load_Mat1 *load = new Load_Mat1();
    double *b1 = (double *)malloc(load->get_Rank() * sizeof(double));
    double *b2 = (double *)malloc(load->get_Rank() * sizeof(double));
    double *b3 = (double *)malloc(load->get_Rank() * sizeof(double));
    for (int i = 0; i < load->get_Rank(); i++) {
        b1[i] = 0;
        if (i == 4) b2[i] = 1;
        else b2[i] = 0;
        b3[i] = 1;
    }
    
    full_Vector *bJacobi1 = new full_Vector();
    full_Vector *bJacobi2 = new full_Vector();
    full_Vector *bJacobi3 = new full_Vector();
    if (Global_Functions::Create_Pointer_From_Vector((double *)b1, bJacobi1, load->get_Rank())) return 1;
    if (Global_Functions::Create_Pointer_From_Vector((double *)b2, bJacobi2, load->get_Rank())) return 1;
    if (Global_Functions::Create_Pointer_From_Vector((double *)b3, bJacobi3, load->get_Rank())) return 1;
    
    full_Vector *xJacobi1 = new full_Vector();
    full_Vector *xJacobi2 = new full_Vector();
    
    full_Matrix *AJacobi = new full_Matrix();
    Global_Functions::Create_Full_Matrix(AJacobi, load->get_Sparse_Matrix());
    //cout << 1 << endl;
    //cout << Global_Functions::norm_Full_Sparse_Matrix(AJacobi, load->get_Sparse_Matrix()) << endl;
    
    //cout << 1 << endl;
    Jacobi *implementation_Jacobi1 = new Jacobi(AJacobi, bJacobi3, xJacobi1);
    Jacobi *implementation_Jacobi2 = new Jacobi(load->get_Sparse_Matrix(), bJacobi3, xJacobi2);

    //for (int i = 0; i < load->get_Rank(); i++) {
    //    cout << xJacobi1->arr[i] << " " << xJacobi2->arr[i] << endl;
    //}
    
    full_Vector *bResult1 = new full_Vector();
    full_Vector *bResult2 = new full_Vector();
    
    operations->productAxFull(AJacobi,xJacobi1,bResult1);
    operations->productAxSparse(load->get_Sparse_Matrix(),xJacobi2,bResult2);
    
    //for (int i = 0; i < load->get_Rank(); i++) {
    //    cout << bResult1->arr[i] << " " << bResult2->arr[i] << endl;
    //}
    
    
    return 0;
}