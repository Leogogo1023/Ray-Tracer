//
//  sphere.cc
//  hw1
//
//  Created by liliang on 2/8/16.
//  Copyright © 2016 liliang. All rights reserved.
//

#include "sphere.h"
#include <math.h>

void Sphere:: setPosition(float x, float y, float z){
    this->origin.setPosition(x, y, z);
    
}

void Sphere:: setRadius(float r){
    this->radius = r;
}

Point Sphere:: getPosition(){
    return std::move(this->origin);
}

float Sphere:: getRadius(){
    return std::move(this->radius);
}

Sphere::Sphere(float x, float y, float z, float r){
    this->origin.setPosition(x, y, z);
    this->radius = r;
}

float Sphere:: intersection(Ray& r){
    // judge hit : 1. if hit: 1.1 draw box: return tboxmin 1.2 draw origin 2. not hit: return -1
    float R = this->getRadius();
    Point c = this->getPosition();
    Point e =r.getOrigin();
    Vector d =r.getDir();
    Vector e_minus_c = minus(e, c);
    float part1 = pow(dot_product(d, e_minus_c),2);
    float d_multi_d = dot_product(d, d);
    float part2 = ( dot_product(e_minus_c, e_minus_c) - pow(R,2) )*d_multi_d;
    if(part1 >= part2){
        float t = ( dot_product(d, e_minus_c) + sqrt(part1-part2) )/d_multi_d;
        return -1*t;
    }
    else return -1;

}

std::vector<Ray*> Sphere:: getRayToLight(Point& intersect, Light *light, int shadowRayNum){
    std::vector<Ray* > ray_list;
    std::vector<Point*> point_list = light->getPosition(shadowRayNum);
    for(unsigned int i=0; i<point_list.size(); i++){
        Ray* r_to_light = new Ray();
        Vector temp = point_list[i]->getPosition() -intersect.getPosition();
        r_to_light->setOrigin(intersect);
        r_to_light->setDirection(temp);
        r_to_light->setLen(temp.norm());
        ray_list.push_back(r_to_light);
    }
    for(Point * p : point_list){
        delete p;
    }
    return std::move(ray_list);
}

Ray Sphere:: getNormalAtIntersect(Point& intersect){
    Ray normal;
    Vector temp = intersect.getPosition() - origin;
    normal.setDirection(temp);
    return std::move(normal);
}