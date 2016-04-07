//
//  point.cc
//  hw1
//
//  Created by liliang on 2/8/16.
//  Copyright © 2016 liliang. All rights reserved.
//

#include "point.h"

void Point:: setPosition(Vector a){
    this->Vector::setPosition(a.getX(), a.getY(), a.getZ());
}


void Point:: setPosition(float x, float y, float z){
    this->Vector::setPosition(x, y, z);
}
