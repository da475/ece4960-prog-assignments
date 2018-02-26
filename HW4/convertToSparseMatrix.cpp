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
    //void *mat_ptr;
    /*
    int arr[5][5] = {{1,2,0,0,3}, {4,5,6,0,0}, {0,7,8,0,9}, {0,0,0,10,0}, {11, 0, 0 , 0, 12}};
    int value[12] = {1,2,3,4,5,6,7,8,9,10,11,12};
    int rowPtr[6] = {0,3,6,9,10,12};
    int colInd[12] = {0,1,4,0,1,2,1,2,4,3,0,4};
    */
public:
//    void initialise(int )
    void createMatrix() {
        if (nZ == -1) {
            nZ = 0;
            for (int i = 0; i < rank; i++) {
                for (int j = 0; j < rank; j++) {
                    if (arr[i * rank + j] != 0) nZ++;
                }
            }
            cout << nZ <<endl;
        }
        
        int value[nZ];
        int rowPtr[rank + 1];
        int colInd[nZ];
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
        
        for (int i = 0; i < sizeof(value)/sizeof(int); i++) {
            cout << value[i] << " ";
        }
        cout << endl;
        for (int i = 0; i < sizeof(value)/sizeof(int); i++) {
            cout << colInd[i] << " ";
        }
        cout << endl;
        for (int i = 0; i < sizeof(rowPtr)/sizeof(int); i++) {
            cout << rowPtr[i] << " ";
        }
        cout << endl;
        
    }
    
    sparseMatrix(int *arr, int rank, long nZ = -1) {
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
    
/*
    sparseMatrix1(long rank) {
        this->arr = (int **)malloc(sizeof(int *) * rank);
        this->arr[0] = (int *)malloc(sizeof(int) * rank * rank);
      
        for(int i=0; i<rank; i++) {
            this->arr[i] = (*(this->arr) + rank * i);
        }
        
        this->rank = rank;
    }
 * */
};

// Change to main function when implementing this program
int main(){
    // Create the first object
    int arr[5][5] = {{1,2,0,0,3}, {4,5,6,0,0}, {0,7,8,0,9}, {0,0,0,10,0}, {11, 0, 0 , 0, 12}};
    sparseMatrix *first = new sparseMatrix((int*)arr, 5);
    first->createMatrix();
    
    return 0;
}