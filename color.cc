//
//  color.cc
//  hw1
//
//  Created by liliang on 2/13/16.
//  Copyright © 2016 liliang. All rights reserved.
//

#include "color.h"


void Color:: setRGB(float r, float g, float b){
    this->r = r;
    this->g = g;
    this->b = b;
}

float Color:: getR(){
    return r;
}

float Color:: getG(){
    return g;
}

float Color:: getB(){
    return b;
}