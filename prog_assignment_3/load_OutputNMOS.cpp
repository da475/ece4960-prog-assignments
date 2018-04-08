/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   load_OutputNMOS.cpp
 * Author: Vishisht
 * 
 * Created on April 6, 2018, 6:39 PM
 */

#include "load_OutputNMOS.h"

int sizeOfOutputNMOS = 1009;

load_OutputNMOS::load_OutputNMOS() {
    ifstream myReadFile;
    myReadFile.open("outputNMOS.txt");
    this->Vgs = (double *)calloc(sizeOfOutputNMOS, sizeof(double));
    this->Vds = (double *)calloc(sizeOfOutputNMOS, sizeof(double));
    this->Ids = (double *)calloc(sizeOfOutputNMOS, sizeof(double));
    int counter = 0, counter1 = 0;
    string temp = "";
    if (myReadFile.is_open()) {
        while (!myReadFile.eof()) {
            myReadFile >> temp;
            if (counter > 0 && counter < (sizeOfOutputNMOS + 2)) {
                if (counter1 == 0) Vgs[counter - 1] = stof(temp);
                else if (counter1 == 1) Vds[counter - 1] = stof(temp);
                else if (counter1 == 2) Ids[counter - 1] = stof(temp);
            }
            

            counter1++;
            if (counter1 == 3) {
                counter++;
                counter1 = 0;
            }
       }
   }
    cout << Ids[0] << endl;
   myReadFile.close();
}

void load_OutputNMOS::getVgsPointer(double *Vgs) {
    Vgs = this->Vgs;
}

void load_OutputNMOS::getVdsPointer(double *Vds) {
    Vds = this->Vds;
}

void load_OutputNMOS::getIdsPointer(double *Ids) {
    cout << this->Ids[0] << endl;
    Ids = this->Ids;
    cout << Ids[0] << endl;
}

load_OutputNMOS::~load_OutputNMOS() {
}