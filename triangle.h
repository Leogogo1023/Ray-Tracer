//
//  triangle.h
//  hw1
//
//  Created by liliang on 2/20/16.
//  Copyright © 2016 liliang. All rights reserved.
//

#ifndef triangle_h
#define triangle_h

#include <stdio.h>
#include "point.h"
#include "ray.h"
#include "material.h"
#include "calculation.h"
#include "surface.h"

class Triangle: public Calculation, public Surface{
    Point a;
    Point b;
    Point c;
    Ray normal;
    float ta,tb,tc,td,te,tf;
public:
    
    void setSurfaceNormal(Point a, Point b, Point c);
    Point getA();
    Point getB();
    Point getC();
    
    Triangle();
    virtual ~Triangle(){};
    Triangle(float xa, float ya, float za, float xb, float yb, float zb, float xc, float yc, float zc);
    
    float intersection(Ray& r);
    std::vector<Ray* > getRayToLight(Point& intersect, Light *light, int shadowRayNum);
    Ray getNormalAtIntersect(Point& Intersect);
    
};

#endif /* triangle_h */
