/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   load_OutputNMOS.h
 * Author: Vishisht
 *
 * Created on April 6, 2018, 6:38 PM
 */

#include "assignment_3_Header.h"

#ifndef LOAD_OUTPUTNMOS_H
#define LOAD_OUTPUTNMOS_H

// Class to load and retrieve the text file outputNMOS
class load_OutputNMOS {
public:
    load_OutputNMOS();
    void getVgsPointer(double **Vgs);
    void getVdsPointer(double **Vds);
    void getIdsPointer(double **Ids);
    virtual ~load_OutputNMOS();
private:
    double *Vgs;
    double *Vds;
    double *Ids;

};

#endif /* LOAD_OUTPUTNMOS_H */

