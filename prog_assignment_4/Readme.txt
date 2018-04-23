Programming Assignment 4: SPICE for ODE Solution

Authors: Vishisht Tiwari and Deepak Agarwal
NetIds: vmt28 and da475

Code Structure:
The main code file and header file is named as Assignment_4_Main.cpp and Assignment_4_Header.h. There are few more code files: ODE_Solvers.cpp, Circuit_Sim_1.cpp, Circuit_Sim_2.cpp, Validation.cpp

- Code Files:
1. Assignment2_Header.h: It is a global header file included in all code files, containing globally defined functions and other classes declataions.
   - Class Global_Functions: Global class defined in the header file containing functions to create dynamically allocated matrix from an array, create dynamic arrays etc. NOTE: Exception handling check is added in all functions under a macro EXCEPTION_HANDLING

2. Assignment2_Main.cpp: Main file performing all tasks: perform validation, call ODE solvers for Simple RC circuit, call ODE solvers for Common-Source amplifier

3. ODE_Solvers.cpp:  Code file containing all ODE solvers – Forward Euler, Runge Kutta 34, and Time Adaptive Runge Kutta

4. Circuit_Sim_1.cpp and Circuit_Sim_2.cpp: Code file to implement the electrical circuit equation and solve it by calling solvers in ODE_Solvers.cpp

5. Validation.cpp: Code file to implement validation equation and it calls ODE solvers


-   Report documents:
1.  Report.pdf and Report.docx: Documentation of code design and testing strategies
2.  Readme.txt: File describing code structure, compilation command and testing platforms
3.  Output_MacOS.txt: Log output on MacOS
4.  Results: A folder containing graph of all solvers and their validation result

Platform used:
    OS: MacOS 
    Editor: netbeans and vim editor
    Compiler: Apple LLVM G++ 9.0.0

