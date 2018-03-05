#include <iostream>
#include <fstream>
#include <math.h>
#include <stdlib.h>
#include <cstdlib>
#include <cmath>

// include the class header file
#include "MatrixOperations.h"

// Allows functions in the std namespace to be used without their prefix
// std::cout becomes cout
using namespace std;

// Function to print a matrix in full-compressed format
void MatrixOperations::printMatrixFull() {

    cout << "Matrix in full-format is" << endl << endl;
    for (int i = 0; i < rank; i++) {
        for (int j = 0; j < rank; j++) {
            cout << arr[i*rank + j] << " ";
        }
        cout << endl;
    }
    cout << endl << endl;
    return;
}

// Function to print a matrix in row-compressed format
void MatrixOperations::printMatrixSparse() {

    cout << "Matrix in row-format is" << endl << endl;
    for (int i = 0; i <= rank; i++) {
        for (int j = rowPtr[i]; j < rowPtr[i+1]; j++) {
            cout << value[j] << " ";
        }
        cout << endl;
    }
    cout << endl << endl;
    return;
}

// Function to convert a matrix to row-compressed format
void MatrixOperations::createMatrix() {
    cout << endl;
    if (nZ == -1) {
        nZ = 0;
        for (int i = 0; i < rank; i++) {
            for (int j = 0; j < rank; j++) {
                if (arr[i * rank + j] != 0) nZ++;
            }
        }
    }

    value = (int *)malloc(nZ * sizeof(int));
    rowPtr = (int *)malloc((rank + 1) * sizeof(int));
    colInd = (int *)malloc(nZ * sizeof(int));
    rowPtr[0] = 0;

    int countNZRow = 0;
    for (int i = 0; i < rank; i++) {
        for (int j = 0; j < rank; j++) {
            if (arr[i * rank + j] != 0) {
                value[countNZRow] = arr[i * rank + j];
                colInd[countNZRow] = j;
                countNZRow++;
            }
        }
        rowPtr[i+1] = countNZRow;
    }
}


// Function to do row-permutation operation in full matrix format
// Input arguments: row i and row j (matrix is part of private member of the class)
// Note: row index starts from 0
void MatrixOperations::rowPermuteFull(int i, int j) {
    cout << endl;
    i--;
    j--;
    int temp;
    // swap the elements
    for (int k = 0; k < rank; k++) {
        temp = arr[i * rank + k];
        arr[i * rank + k] = arr[j * rank + k];
        arr[j * rank + k] = temp;
    }

    cout << "Perumation performed in full-format between " << i+1 << " " << j+1 << endl << endl;
    return;

}

// Function to do row-permutation operation in sparse matrix format
// Input arguments: row i and row j (matrix is part of private member of the class)
void MatrixOperations::rowPermuteSparse(int i, int j) {
    cout << endl;

    int nZSizeOfFirst = rowPtr[i] - rowPtr[i-1];
    int nZSizeOfSecond = rowPtr[j] - rowPtr[j-1];


    int tempFirstArrayValue[nZSizeOfFirst];
    int tempSecondArrayValue[nZSizeOfSecond];
    int tempFirstArrayColInd[nZSizeOfFirst];
    int tempSecondArrayColInd[nZSizeOfSecond];

    int counter = 0;

    // Copy the value and col for first row in a temp array
    for (int k = rowPtr[i-1]; k < rowPtr[i]; k++) {
        tempFirstArrayValue[counter] = value[k];
        tempFirstArrayColInd[counter] = colInd[k];
        counter++;
    }

    counter = 0;

    // Copy the value and col for second row in a temp array
    for (int k = rowPtr[j-1]; k < rowPtr[j]; k++) {
        tempSecondArrayValue[counter] = value[k];
        tempSecondArrayColInd[counter] = colInd[k];
        counter++;
    }


    // shift original col and val array by difference in no of elements of both rows
    // if row1 has more elements than row2, array will shift leftwards
    // if row1 has less elements than row2, array will shift rightwards
    for (int k = rowPtr[i]; k < rowPtr[j] - 1; k++) {
        colInd[k - (nZSizeOfFirst - nZSizeOfSecond)] = colInd[k];
        value[k - (nZSizeOfFirst - nZSizeOfSecond)] = value[k];
    }

    counter = 0;
    for (int k = rowPtr[i - 1]; k < (rowPtr[i - 1] + nZSizeOfSecond); k++) {
        value[k] = tempSecondArrayValue[counter];
        colInd[k] = tempSecondArrayColInd[counter];
        counter++;
    }
    counter = 0;
    for (int k = rowPtr[j - 1]; k < (rowPtr[j - 1] + nZSizeOfFirst); k++) {
        value[k-1] = tempFirstArrayValue[counter];
        colInd[k-1] = tempFirstArrayColInd[counter];
        counter++;
    }

    for (int k = i; k < j; k++) {
        rowPtr[k] -= nZSizeOfFirst - nZSizeOfSecond;
    }

    cout << "Perumation performed in row-compressed format between " << i << " " << j << endl << endl;
    return;
}

// Function to do row-scaling operation in full matrix format
// Input arguments: row i, row j and scaling factor a (matrix is part of private member of the class)
// Result: row[i] = row[i] + row[j]*a
void MatrixOperations::rowScaleFull(int i, int j, double a) {
    cout << endl;
    i--, j--;

    for (int k= 0; k < rank; k++) {
        arr[i * rank + k] += a * arr[j * rank + k];
    }
    cout << "Scaling performed in full-matrix format between " << i+1 << " " << j+1 << " with scaling factor = " << a  << endl << endl;
}

// Function to do row-scaling operation in sparse matrix format
// Input arguments: row i, row j and scaling factor a (matrix is part of private member of the class)
// Result: row[j] = row[j] + row[i]*a
void MatrixOperations::rowScaleSparse(int i, int j, double a) {
    cout << endl;

    int nZSizeOfFirst = rowPtr[i] - rowPtr[i-1];
    int nZSizeOfSecond = rowPtr[j] - rowPtr[j-1];


    // create the array to store the rows i and j in full-matrix format
    int FirstArrayValue[rank];
    int SecondArrayValue[rank];

    for (int k=0; k<rank; k++) {
        FirstArrayValue[k] = 0;
        SecondArrayValue[k] = 0;
    }

    int counter = 0;

    // Add non-zero elements in the first row
    for (int k = rowPtr[i-1]; k < rowPtr[i]; k++) {
        FirstArrayValue[colInd[k]] = value[k];
    }

    // Add non-zero elements in the second row
    for (int k = rowPtr[j-1]; k < rowPtr[j]; k++) {
        SecondArrayValue[colInd[k]] = value[k];
    }

//junk TODO
/*
    for (int k=0; k<rank; k++) {
        cout << FirstArrayValue[k] << " ";
    }
    cout << endl;
    cout << endl;

    for (int k=0; k<rank; k++) {
        cout << SecondArrayValue[k] << " ";
    }
    cout << endl;
    cout << endl;
*/

    // Do the scaling operation
    int no_of_zeroes = 0;
    for (int k=0; k<rank; k++) {
        FirstArrayValue[k] += (a * SecondArrayValue[k]);
        if(FirstArrayValue[k] != 0)
            no_of_zeroes++;
    }

    cout << endl;

    // check if no of non-zero elements have changed for row j
    int change_in_zeroes = no_of_zeroes - nZSizeOfSecond;

    // update the rowPtr with new entries
    for(int k=i; k<=rank; k++) {
        rowPtr[k] += change_in_zeroes;
    }

    // if zeroes count changed, we free and alloc memory again
    // for value and colInd pointer

    nZ += change_in_zeroes;
    int *value_tmp = (int *)malloc((nZ+change_in_zeroes) * sizeof(int));
    int *colInd_tmp = (int *)malloc((nZ+change_in_zeroes) * sizeof(int));

    // copy till (i-1)th row as it is
    for(int k=0; k<rowPtr[i-1]; k++) {
        value_tmp[k] = value[k];
        colInd_tmp[k] = colInd[k];
    }

    // copy the (i)th row
    counter = rowPtr[i-1];
    for(int k=0; k<rank; k++) {
        cout << FirstArrayValue[k] << " ";
        if(FirstArrayValue[k] != 0) {
            colInd_tmp[counter] = FirstArrayValue[k];
            value_tmp[counter] = k;
            counter++;
        }
    }

    //cout << endl << __func__ << " at line " << __LINE__ << endl;
    // copy rest of the rows
    for(int k=rowPtr[i]; k<rowPtr[rank]; k++) {
        value_tmp[k] = value[k - change_in_zeroes];
        colInd_tmp[k] = colInd[k - change_in_zeroes];
    }

    free(value);
    free(colInd);

    value = value_tmp;
    colInd = colInd_tmp;

    for (int k=0; k<nZ; k++) {
        cout << value_tmp[k] << " ";
    }
    cout << endl;
    cout << "Scaling performed in row-compressed format between " << i << " " << j << " with scaling factor = " << a  << endl << endl;

}

// Function to do product operation in full matrix format
// Input arguments: row i, row j and scaling factor a (matrix is part of private member of the class)
// TODO below code is wrong
void MatrixOperations::productAxFull(int i, int j, double a) {
    i--, j--;

    for (int k= 0; k < rank; k++) {
        arr[j * rank + k] *= arr[i * rank + k];
    }
}

// Function to do row-scaling operation in full matrix format
// Input arguments: row i, row j and scaling factor a (matrix is part of private member of the class)
// TODO below code is wrong
void MatrixOperations::productAxSparse(int i, int j, double a) {
    cout << endl;

    int nZSizeOfFirst = rowPtr[i] - rowPtr[i-1];
    int nZSizeOfSecond = rowPtr[j] - rowPtr[j-1];

    int counter = 0;
    for (int k = rowPtr[j-1]; k < rowPtr[j-1] + nZSizeOfSecond; k++) {
        rowPtr[k] = value[i*rank - k]*a;
    }
}

// Constructor for small matrices where full-format matrix is known
// It loads the matrix in 'arr' along with other information
MatrixOperations::MatrixOperations(int *arr, int rank, long nZ = -1) {
    cout << endl;
/*
    for(int i=0; i<rank; i++) {
        for(int j=0; j<rank; j++) {
            cout << arr[i * rank + j] << " ";
        }
        cout << endl;
    }*/
    this->arr = arr;
    this->rank = rank;
    this->nZ = nZ;
    this->value = NULL;
    this->rowPtr = NULL;
    this->colInd = NULL;
}

// Constructor for very large matrices which cannot be loaded in full-matrix form
// 'arr' remains null, it loads the three pointers needed in row-compressed format
MatrixOperations::MatrixOperations(int *row, int *col, int *val, int nonzero) {
    this->arr = NULL;
    this->value = val;
    this->rowPtr = row;
    this->colInd = col;
    this->nZ = nonzero;
}

// Destructor
MatrixOperations::~MatrixOperations() {
    if (this->arr) free(this->arr);
    if (this->value) free(this->value);
    if (this->rowPtr) free(this->rowPtr);
    if (this->colInd) free(this->colInd);
}

int main() {

    int arr1[5][5] = {
                    {1, 2, 0, 0, 3},
                    {4, 5, 6, 0, 0},
                    {0, 7, 8, 0, 9},
                    {0, 0, 0, 10, 0},
                    {11,0, 0, 0, 12}
                    };

    int arr2[5][5] = {
                    {1, 2, 0, 0, 3},
                    {4, 5, 6, 0, 0},
                    {0, 7, 8, 0, 9},
                    {0, 0, 0, 10, 0},
                    {11,0, 0, 0, 12}
                    };

    MatrixOperations *first = new MatrixOperations((int*)arr1, 5);
    MatrixOperations *second = new MatrixOperations((int*)arr2, 5);
    first->createMatrix();
    second->createMatrix();

    first->printMatrixFull();
//    first->rowPermuteFull(2,5);
    first->rowScaleFull(2,5,1);
    first->printMatrixFull();

    second->printMatrixSparse();
    //second->rowPermuteSparse(2,5);
    second->rowScaleSparse(2,5,1);
    first->printMatrixSparse();


    // ###########  LOAD MATRIX FILE   #############

#if 0
    ifstream matfile;
    matfile.open("memplus.mtx");
    if (!matfile) {
        cout << "Couldn't open the file" << endl;
        exit(1);
    }

    string firstline;
    getline(matfile, firstline);

    int rowind, colind, nz;
    matfile >> rowind >> colind >> nz;
    cout << "row " << rowind << endl;
    cout << "col " << colind << endl;
    cout << "value " << nz << endl;

    int rank = rowind;
    int *valarr = (int*)malloc (sizeof(int) * nz);
    int *rowarr = (int*)malloc (sizeof(int) * nz);
    int *colarr = (int*)malloc (sizeof(int) * nz);

    int i=0;

    getline(matfile, firstline);
    cout << firstline << endl;

    string delim = " ";
    string token;
    size_t pos = 0;

    i = 0;
    //while(!matfile.eof()) {
    for(i=0; i<nz; i++) {
        getline(matfile, firstline);

        pos = firstline.find(delim);
        token = firstline.substr(0, pos);
        rowarr[i] = stoi(token);
        firstline.erase(0, pos + delim.length());

        pos = firstline.find(delim);
        token = firstline.substr(0, pos);
        colarr[i] = stoi(token);
        firstline.erase(0, pos + delim.length());

        pos = firstline.find(delim);
        token = firstline.substr(0, pos);
        //valarr[i] = stoi(token);      //TODO not working for now
        firstline.erase(0, pos + delim.length());

    }

    matfile.close();

//    for(i=0; i<20; i++)
//        cout << rowarr[i] << endl;

#endif

    return 0;
}


