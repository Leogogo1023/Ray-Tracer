//
//  vector.hpp
//  hw1
//
//  Created by liliang on 2/11/16.
//  Copyright © 2016 liliang. All rights reserved.
//

#ifndef vector_h
#define vector_h

#include <stdio.h>
#include <math.h>
class Vector{
    friend class Triangle;
    friend class Plane;
    friend class Sphere;
    friend class Surface;
    friend class BVHNode;
    friend class Ray;
    float x;
    float y;
    float z;
    
public:
    void setPosition(float x, float y, float z);
    void setPosition(Vector a);
    void setDirection(float x, float y, float z);
    void setDirection(Vector a);
    Vector getPosition();
    float getX();
    float getY();
    float getZ();
    Vector(){};
    Vector(float x, float y, float z){
        this->setPosition(x, y, z);
    }
    Vector &operator+= (Vector v) {
        x = x + v.getX();
        y = y + v.getY();
        z = z + v.getZ();
        
        return *this;
    }
    
    Vector operator+ (Vector v) {
        return Vector (x+v.getX(), y+v.getY(), z+v.getZ());
    }
    
    Vector operator- (Vector v) {
        return Vector (x-v.getX(), y-v.getY(), z-v.getZ());
    }
    
    Vector operator* (const float scale) {
        return Vector (scale * x,scale * y,scale * z);
    }
    
    Vector operator*= (const float scale){
        x = x*scale;
        y = y*scale;
        z = z*scale;
        return *this;
    }
    
    float norm(){
        float norm =sqrtf(x*x+y*y+z*z);
        return norm;
    }
    void normalize(){
        float norm = this->norm();
        *this = *this*(1/norm);
    }
};


#endif /* vector_h */
