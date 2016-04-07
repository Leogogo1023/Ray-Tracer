//
//  calculation.cc
//  hw1
//
//  Created by liliang on 2/11/16.
//  Copyright © 2016 liliang. All rights reserved.
//

#include "calculation.h"



float Calculation::  dot_product(Vector a, Vector b){
    float product = a.getX()*b.getX() + a.getY()*b.getY() + a.getZ()*b.getZ();
    return product;    
}


Vector Calculation:: addThree(Vector a, Vector b, Vector c){
    Vector rlt;
    rlt.setDirection(a.getX()+b.getX()+c.getX(), a.getY()+b.getY()+c.getY(), a.getZ()+b.getZ()+c.getZ());
    return rlt;
}


Vector Calculation:: cross_product(Vector a, Vector b){
    float first = a.getY()*b.getZ()-a.getZ()*b.getY();
    float second = a.getZ()*b.getX()-a.getX()*b.getZ();
    float third = a.getX()*b.getY() - a.getY()*b.getX();
    Vector v;
    v.setDirection(first, second, third);
    return v;
    
}

Vector Calculation:: minus(Vector a, Vector b){
    Vector v;
    v.setDirection(a.getX()-b.getX(), a.getY()-b.getY(), a.getZ()-b.getZ());
    return v;
}