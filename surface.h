//
//  surface.h
//  hw1
//
//  Created by liliang on 2/9/16.
//  Copyright © 2016 liliang. All rights reserved.
//

#ifndef surface_h
#define surface_h

#include <stdio.h>
#include <iostream>    // input output
#include "material.h"
#include "ray.h"
#include "light.h"
#include "BBox.h"
#include <math.h>
#include <algorithm>


class Surface {
    friend class BVHNode;
    
    Material material;
    BBox bbox;
    Point _min, _max;
    int index;
public:
    const double e = 0.000001;
    Surface () {}
    virtual ~Surface() {}
    
    virtual float intersection(Ray& r){
        return 0;
    }
    virtual std::vector<Ray* > getRayToLight(Point& intersect, Light *light, int shadowRayNum){
        std::cout<<"This is a virutal function that shouldn't be called"<<std::endl;
        std::vector<Ray* > r;
        return r;
    }
    virtual Ray getNormalAtIntersect(Point& Intersect){
        std::cout<<"This is a virutal function that shouldn't be called"<<std::endl;
        Ray r;
        return r;
    }
    void setIndex(int n){
        index = n;
    }
    void setSurfaceMin(float x, float y, float z){
        _min.setPosition(x,y,z);
    }
    void setSurfaceMax(float x, float y, float z){
        _max.setPosition(x,y,z);

    }
    void setbbox(BBox bbox){
        this->bbox = bbox;
    }
    Point getbboxMin(){
        return bbox.getbboxMin();
    }
    Point getbboxMax(){
        return bbox.getbboxMax();
    }
    BBox getbbox(){
        return bbox;
    }
    
    void setMaterial(Material material){
        this->material = material;
    }
    Material getMaterial(){
        return material;
    }
    
    float bboxIntersect(Ray& r){
        Point eye = r.getOrigin();
        float xmin = bbox.bboxMin.x;
        float xmax = bbox.bboxMax.x;
        float ymin = bbox.bboxMin.y;
        float ymax = bbox.bboxMax.y;
        float zmin = bbox.bboxMin.z;
        float zmax = bbox.bboxMax.z;
        float dx =r.getDir().x, xe = eye.x;
        float dy =r.getDir().y, ye = eye.y;
        float dz =r.getDir().z, ze = eye.z;
        float txmin, txmax, tymin, tymax, tzmin, tzmax;
        float minT=0, maxT= std::numeric_limits<int>::max();
        
        if(xe>=xmin and xe<=ymax and ye>=ymin and ye<=ymax and ze>=zmin and ze<=zmax) return 0;
        
        if(dx>0){
            txmin = (xmin - xe) /dx;
            txmax = (xmax - xe) /dx;
        }
        else{
            txmin = (xmax - xe) /dx;
            txmax = (xmin - xe) /dx;
        }
        if(txmax <= minT or txmin >= maxT) return -1;
        else{
            minT = fmaxf(txmin,minT);
            maxT = fminf(txmax,maxT);
        }

        if(dy>0){
            tymin = (ymin - ye) /dy;
            tymax = (ymax - ye) /dy;
        }
        else{
            tymin = (ymax - ye) /dy;
            tymax = (ymin - ye) /dy;
        }
        if(tymax <= minT or tymin >= maxT) return -1;
        else {
            minT = fmaxf(tymin,minT);
            maxT = fminf(tymax, maxT);
        }

        if(dz>0){
            tzmin = (zmin - ze) /dz;
            tzmax = (zmax - ze) /dz;
        }
        else{
            tzmin = (zmax - ze) /dz;
            tzmax = (zmin - ze) /dz;
        }
        if(tzmax <= minT or tzmin >= maxT) return -1;
        else{
            minT = fmaxf(tzmin,minT);
            //maxT = fminf(tzmax,maxT);
        }
    
        return minT;
    }
    Ray getBboxNormal(Point& intersect){
        Ray normal;
            float x = intersect.x;
            float y = intersect.y;
            float z = intersect.z;
            if(fabs(x-getbboxMin().x)<e){
                normal.setDirection(-1, 0, 0);
            }
            else if(fabsf(x-getbboxMax().x)<e){
                normal.setDirection(1, 0, 0);
            }
            else if(fabsf(y-getbboxMin().y)<e){
                normal.setDirection(0, -1, 0);
            }
            else if(fabsf(y-getbboxMax().y)<e){
                normal.setDirection(0, 1, 0);
            }
            else if(fabsf(z-getbboxMin().z)<e){
                normal.setDirection(0, 0, -1);
            }
            else{
                normal.setDirection(0, 0, 1);
            }
        return normal;
    }
};

#endif /* surface_h */
