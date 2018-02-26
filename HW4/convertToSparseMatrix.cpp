#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <cstdlib>
#include <cmath>

// Allows functions in the std namespace to be used without their prefix
// std::cout becomes cout
using namespace std;

class sparseMatrix{
private:
    
    int rank;
    long nZ;
    int *arr;
    int *value;
    int *rowPtr;
    int *colInd;
    
public:
    void createMatrix() {
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
    
    void rowPermuteMatrix(int i, int j) {
        cout << endl;
        i--, j--;
        int temp;
        
        for (int k= 0; k < rank; k++) {
            temp = arr[i * rank + k];
            arr[i * rank + k] = arr[j * rank + k];
            arr[j * rank + k] = temp;
        }
    }
    
    void rowPermuteSparse(int i, int j) {
        cout << endl;
        int nZSizeOfFirst = rowPtr[i] - rowPtr[i-1];
        int nZSizeOfSecond = rowPtr[j] - rowPtr[j-1];
        
        
        int tempFirstArrayValue[nZSizeOfFirst];
        int tempSecondArrayValue[nZSizeOfSecond];
        int tempFirstArrayColInd[nZSizeOfFirst];
        int tempSecondArrayColInd[nZSizeOfSecond];

        int counter = 0;
        for (int k = rowPtr[i-1]; k < rowPtr[i-1] + nZSizeOfFirst; k++) {
            tempFirstArrayValue[counter] = value[k];
            tempFirstArrayColInd[counter] = colInd[k];
            counter++;
        }
        counter = 0;
        for (int k = rowPtr[j-1]; k < rowPtr[j-1] + nZSizeOfSecond; k++) {
            tempSecondArrayValue[counter] = value[k];
            tempSecondArrayColInd[counter] = colInd[k];
            counter++;
        }
        
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
    }
    
    void rowScaleMatrix(int i, int j, double a) {
        cout << endl;
        i--, j--;
        
        for (int k= 0; k < rank; k++) {
            arr[j * rank + k] += a * arr[i * rank + k];
        }
    }
    
    void rowScaleSparse(int i, int j, double a) {
        cout << endl;

        int nZSizeOfFirst = rowPtr[i] - rowPtr[i-1];
        int nZSizeOfSecond = rowPtr[j] - rowPtr[j-1];
        
        counter = 0;
        for (int k = rowPtr[j-1]; k < rowPtr[j-1] + nZSizeOfSecond; k++) {
            rowPtr[k] = value[i*rank - k]*a;
        }
    }
    
    void productAxMatrix(int i, int j, double a) {
        i--, j--;
        
        for (int k= 0; k < rank; k++) {
            arr[j * rank + k] *= arrX[i * rank + k];
        }
    }
    
    void productAxSparse(int i, int j, double a) {
        cout << endl;

        int nZSizeOfFirst = rowPtr[i] - rowPtr[i-1];
        int nZSizeOfSecond = rowPtr[j] - rowPtr[j-1];
        
        counter = 0;
        for (int k = rowPtr[j-1]; k < rowPtr[j-1] + nZSizeOfSecond; k++) {
            rowPtr[k] = value[i*rank - k]*a;
        }
    }
    
    sparseMatrix(int *arr, int rank, long nZ = -1) {
        cout << endl;
        for(int i=0; i<rank; i++) {
            for(int j=0; j<rank; j++) {
                cout << arr[i * rank + j] << " ";
            }
            cout << endl;
        }
        this->arr = arr;
        this->rank = rank;
        this->nZ = nZ;
    }
};

// Change to main function when implementing this program
int main(){
    // Create the first object
    int arr[5][5] = {{1,2,0,0,3}, {4,5,6,0,0}, {0,7,8,0,9}, {0,0,0,10,0}, {11, 0, 0 , 0, 12}};
    sparseMatrix *first = new sparseMatrix((int*)arr, 5);
    first->createMatrix();
    first->rowPermuteMatrix(2,5);
    first->rowPermuteSparse(2,5);
    
    return 0;
}