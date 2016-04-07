//
//  plane.cpp
//  hw1
//
//  Created by liliang on 2/17/16.
//  Copyright © 2016 liliang. All rights reserved.
//

#include "plane.h"

Plane:: Plane(float x, float y, float z, float d){
    this->normal.setDirection(x, y, z);
    this->d=d;
}
Ray Plane:: getSurfaceNormal(){
    return this->normal;
}

float Plane:: getSurfaceD(){
    return  this->d;
}


float Plane:: intersection(Ray r, int option){
  //  std::cout<<"This is plane!" << std::endl;
    Ray normal = this->getSurfaceNormal();
    float d = this->getSurfaceD();
    float part1 = dot_product(r.getOrigin(), normal.getDir())+d;
    float part2 = dot_product(r.getDir(), normal.getDir());
    
    if(part2 !=0){
        return (-1.*part1)/part2;
    }
    
    else return -1;
}

Ray Plane:: getRayToLight(Point intersect, Light light){
  // std::cout<<"This is Plane!" << std::endl;
    Ray r_to_light;
    Vector temp = light.getPosition()-intersect.getPosition();
    r_to_light.setOrigin(intersect);
    r_to_light.setDirection(temp);
    return r_to_light;
}

Ray Plane:: getNormalAtIntersect(Point intersect, int option){
    return this->normal;
}

