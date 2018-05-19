Programming Assignment 5: Effects of different Time stepping on stiff equation of CS Amplifier

Authors: Vishisht Tiwari and Deepak Agarwal
NetIds: vmt28 and da475

Code Structure:
The main code file and header file is named as Assignment_5_Main.cpp and Assignment_5_Header.h. There are few more code files: ODE_Solvers.cpp, Circuit_Sim.cpp, Validation.cpp

- Code Files:
1. Assignment_5_Header.h: It is a global header file included in all code files, containing globally defined functions and other classes declataions.
   - Class Global_Functions: Global class defined in the header file containing functions to create dynamically allocated matrix from an array, create dynamic arrays etc. NOTE: Exception handling check is added in all functions under a macro EXCEPTION_HANDLING

2. Assignment_5_Main.cpp: Main file performing all tasks: perform validation, call ODE solvers for validation equation and Common-Source amplifier

3. ODE_Solvers.cpp:  Code file containing ODE solvers such as RK34, RK23 and Time stepping methods such as bisection, constant E.h, O(h) and no time stepping.

4. Circuit_Sim.cpp: Code file to implement the electrical circuit equation and solve it by calling solvers in ODE_Solvers.cpp

5. Validation.cpp: Code file to implement validation equation and it calls ODE solvers


-   Report documents:
1.  Report.pdf and Report.docx: Results of the experiment
2.  Readme.txt: File describing code structure, compilation command and testing platforms
3.  output.rtf: Log output on MacOS
4.  Results: A folder containing results of all solvers and their validation result
5.  SQA.doc and SQA.pdf: Results of tests on validation equation

Platform used:
    OS: MacOS 
    Editor: netbeans and vim editor
    Compiler: Apple LLVM G++ 9.0.0

