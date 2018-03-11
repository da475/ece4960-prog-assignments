Programming Assignment 2: Modular Testing in Sparse Matrix Solvers

Authors: Vishisht Tiwari and Deepak Agarwal
NetIds: vmt28 and da475

Code Structure:
The main code file and header file is named as Assignment2_Main.cpp and Assignment2_Header.h. There are three more code files: Jacobi.cpp, Load_Mat1.cpp and Matrix_Operations.cpp

1. Assignment2_Header.h:
    It is a global header file included in all code files, containing globally defined functions and other classes declataions.
 
   - Class Global_Functions: Global class defined in the header file containing functions to create dynamically allocated matrix from an array, create dynamic arrays, create full matrix from sparse etc. Exception handling check is added in all functions under a macro EXCEPTION_HANDLING

    - Class Matrix_Operations: Class declared having matrix operations (permute, scaling and product) for full and sparse matrices
    - Class Jacobi: Class implementing iterative solver using Jacobi method on full and sparse matrices
    - Class LoadMat1: Class implementing functions to load csv files and generate sparse matrix from it

2. Assignment2_Main.cpp: 
   Main file loading the sparse matrix from the .csv files, performing Jacobi iterative solver and calculating the norm.

3. Matrix_Operations.cpp:
   Implements the class Matrix_Operations containing the three matrix operations (permute, scaling and product) for sparse and full matrices, with exception handling under EXCEPTION_HANDLING macro.

4. Jacobi.cpp:
   Class implementing functions for iterative solver for full-matrix and row-compressed formats.

5. Load_Mat1.cpp:
   Implements functions for loading the .csv files in different arrays.

Following a modular programming approach, a class of globally defined functions was defined in the header itself, which can be used
It is class defined in the header file itself, so that it can be used by any other classes  


Platforms used:
1. OS: MacOS 
   Editor: netbeans and vim editor
   Compiler: Apple LLVM G++ 9.0.0


2. OS: ECE linux machine
   Editor: vim editor
   Compiler: (GCC) 4.8.5 (RedHat 4.8.5-16)


To compile the program:
1. Compile:
g++ -std=c++0x -o testexe Assignment2_Main.cpp Matrix_Operations.cpp Jacobi.cpp Load_Mat1.cpp 

2. Run
./testexe


