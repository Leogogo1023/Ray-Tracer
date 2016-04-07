//
//  triangle.c
//  hw1
//
//  Created by liliang on 2/20/16.
//  Copyright © 2016 liliang. All rights reserved.
//

#include "triangle.h"


Triangle:: Triangle(float xa, float ya, float za, float xb, float yb, float zb, float xc, float yc, float zc){
    a.setPosition(xa, ya, za);
    b.setPosition(xb, yb, zb);
    c.setPosition(xc, yc, zc);
    this->setSurfaceNormal(a, b, c);
    Point A = this->a;
    Point B = this->b;
    Point C = this->c;

    ta = A.x-B.x;
    tb = A.y-B.y;
    tc = A.z-B.z;
    td = A.x-C.x;
    te = A.y-C.y;
    tf = A.z-C.z;
}

Point Triangle:: getA(){
    return this->a;
}

Point Triangle:: getB(){
    return this->b;
}


Point Triangle:: getC(){
    return this->c;
}

float Triangle:: intersection(Ray& r){
        Point A = this->a;
        float tg = r.getDir().x;
        float th = r.getDir().y;
        float ti = r.getDir().z;
        float tj = A.x-r.getOrigin().x;
        float tk = A.y-r.getOrigin().y;
        float tl = A.z-r.getOrigin().z;
        
        float gamma, beta, M, t;
        float ei_hf = te*ti-th*tf;
        float gf_di = tg*tf-td*ti;
        float dh_eg = td*th-te*tg;
        float bl_kc = tb*tl-tk*tc;
        float ak_jb = ta*tk-tj*tb;
        float jc_al = tj*tc-ta*tl;
        M = ta*ei_hf + tb*gf_di + tc* dh_eg;
        
        if(M == 0) return -1;
        
        t = -1. * (tf*ak_jb+te*jc_al+td*bl_kc) / M;
        if(t<=0.) return -1;
        
        gamma = (ti*ak_jb + th*jc_al + tg*bl_kc)/M;
        if(gamma < 0 || gamma >1) return -1;
        
        beta = (tj*ei_hf + tk*gf_di + tl*dh_eg)/M;
        if(beta<0 || beta > (1-gamma)) return -1;
        
        return t;

}

void Triangle:: setSurfaceNormal(Point a, Point b, Point c) {
    Vector a_b = a*(-1)+ b;
    Vector a_c = a*(-1)+ c;
    this->normal.setDirection(cross_product(a_b, a_c));
}

std::vector<Ray* > Triangle:: getRayToLight(Point& intersect, Light *light, int shadowRayNum){
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

Ray Triangle:: getNormalAtIntersect(Point& intersect){
        return std::move(this->normal);
}


