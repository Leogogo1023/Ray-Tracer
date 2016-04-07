//
//  sphere.hpp
//  hw1
//
//  Created by liliang on 2/8/16.
//  Copyright © 2016 liliang. All rights reserved.
//

#ifndef sphere_h
#define sphere_h

#include <stdio.h>
#include "point.h"
#include "surface.h"
#include "camera.h"
#include "calculation.h"
#include "ray.h"
#include "light.h"

class Sphere : public Calculation, public Surface{
    Point origin;
    float radius;
public:
    Sphere();
    Sphere(float x, float y, float z, float r);
    float intersection(Ray& r);
    void setPosition(float x, float y, float z);
    void setRadius(float r);
    std::vector<Ray* > getRayToLight(Point& intersect, Light *light, int shadowNum);
    Ray getNormalAtIntersect(Point& intersect);
    Point getPosition();
    float getRadius();
    
};

#endif /* sphere_h*/
