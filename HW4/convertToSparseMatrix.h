/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   convertToSparseBetter.h
 * Author: Vishisht
 *
 * Created on February 25, 2018, 8:54 PM
 */

#ifndef CONVERTTOSPARSEBETTER_H
#define CONVERTTOSPARSEBETTER_H

class convertToSparseBetter {
public:
    convertToSparseBetter();
    convertToSparseBetter(const convertToSparseBetter& orig);
    virtual ~convertToSparseBetter();
    void rowPermuteMatrix(int i, int j, double a);
    void rowPermuteSparse(int i, int j);
    void rowScaleMatrix(int i, int j, double a);
    void rowScaleSparse(int i, int j, double a);
private:

};

#endif /* CONVERTTOSPARSEBETTER_H */

