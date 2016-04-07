//
//  vector.cpp
//  hw1
//
//  Created by liliang on 2/11/16.
//  Copyright © 2016 liliang. All rights reserved.
//

#include "vector.h"


void Vector:: setDirection(float x, float y, float z){
    this->x = x;
    this->y = y;
    this->z = z;
}

void Vector:: setDirection(Vector a){
    this->x = a.getX();
    this->y = a.getY();
    this->z = a.getZ();
}

void Vector:: setPosition(float x, float y, float z){
    this->x = x;
    this->y = y;
    this->z = z;
}

void Vector:: setPosition(Vector a){
    this->setPosition(a.getX(), a.getY(), a.getZ());
}

Vector Vector:: getPosition(){
    Vector temp;
    temp.setDirection(this->getX(), this->getY(), this->getZ());
    return temp;
}

float Vector:: getX(){
    return x;
}

float Vector:: getY(){
    return y;
}
float Vector:: getZ(){
    return z;
}