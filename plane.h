//
//  plane.hpp
//  hw1
//
//  Created by liliang on 2/17/16.
//  Copyright © 2016 liliang. All rights reserved.
//

#ifndef plane_h
#define plane_h

#include <stdio.h>
#include "surface.h"
#include "material.h"
#include "calculation.h"
#include "ray.h"


class Plane: public Calculation, public Surface{
    Ray normal;
    float d;
public:
    Plane(){};
    virtual ~Plane(){};
    Plane(float x, float y, float z, float d);
    
    float intersection(Ray r, int option);
    Ray getRayToLight(Point intersect, Light light);
    Ray getNormalAtIntersect(Point Intersect, int option);
    
    Ray getSurfaceNormal();
    float getSurfaceD();
    
};

#endif /* plane_h */
