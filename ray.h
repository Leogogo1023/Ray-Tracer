//
//  ray.h
//  hw1
//
//  Created by liliang on 2/9/16.
//  Copyright © 2016 liliang. All rights reserved.
//

#ifndef ray_h
#define ray_h

#include <stdio.h>
#include <vector>
#include <math.h>
#include "vector.h"
#include "point.h"

class Ray{
    Point origin;
    Vector dir;
    float len;
    std::vector< Vector > boxSurfaceNormal;
    void setBoxSurfaceNormal(){
        Vector zero(-1,0,0);
        Vector one(1,0,0);
        Vector two(0,-1,0);
        Vector three(0,1,0);
        Vector four(0,0,-1);
        Vector five(0,0,1);
        boxSurfaceNormal.push_back(zero);
        boxSurfaceNormal.push_back(one);
        boxSurfaceNormal.push_back(two);
        boxSurfaceNormal.push_back(three);
        boxSurfaceNormal.push_back(four);
        boxSurfaceNormal.push_back(five);
    }

public:
    void setLen(float len){
        this->len = len;
    }
    void setOrigin(float x, float y, float z);
    void setOrigin(Vector a);
    void setDirection(float x, float y, float z);
    void setDirection(Vector a);
    
    
    Ray  reverse();
    Point getOrigin();
    Vector  getDir();
    float getLen(){
        return len;
    }
};

#endif /* ray_h */
