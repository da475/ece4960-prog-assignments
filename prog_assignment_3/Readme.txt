Programming Assignment 3: Parameter extraction from Least-Square Fitting

Authors: Vishisht Tiwari and Deepak Agarwal
NetIds: vmt28 and da475

Code Structure:
The main code file and header file is named as Assignment3_Main.cpp and Assignment3_Header.h. There are four more code files: full_Matrix_Solver.cpp, load_OutputNMOS.cpp, EKV_Model.cpp and EKV_Model_Secant.cpp

Code Files:
1. Assignment2_Header.h: It is a global header file included in all code files, containing globally defined functions and other classes declataions.
   - Class Global_Functions: Global class defined in the header file containing functions to create dynamically allocated matrix from an array, create dynamic arrays etc. NOTE: Exception handling check is added in all functions under a macro EXCEPTION_HANDLING
    - Class Matrix_Operations: Class declared having matrix operations (permute, scaling and product) for full and sparse matrices
    - Class Jacobi: Class implementing iterative solver using Jacobi method on full and sparse matrices
    - Class LoadMat1: Class implementing functions to load csv files and generate sparse matrix from it

2. Assignment2_Main.cpp: Main file performing all tasks: direct matrix solver through LU decomposition, EKV solver through quasi-Newton method, EKV solver through secant method 

3. full_Matrix_Solver.cpp: Implements the direct matrix solver through LU decomposition
4. load_OutputNMOS.cpp: Loads the outputNMOS file and stores the three vectors
5. EKV_Model.cpp: Implements the parameter extraction using quasi-Newton method
6. EKV_Model_Secant.cpp: Implements the parameter extraction using Secant method

Other Files:
7. Task-3.png: Plot of Ids vs Vds
8. report.pdf and report.docx: report summary
9. Readme.txt: this file

Platform used:
    OS: MacOS 
    Editor: netbeans and vim editor
    Compiler: Apple LLVM G++ 9.0.0

To compile the program:

Compile command: g++ assignment_3_Main.cpp EKV_Model.cpp full_Matrix_Solver.cpp load_OutputNMOS.cpp power_Law_Parameter_Extraction.cpp EKV_Model_Secant.cpp

Run using: ./a.out

