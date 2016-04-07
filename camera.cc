//
//  camera.cc
//  hw1
//
//  Created by liliang on 2/8/16.
//  Copyright © 2016 liliang. All rights reserved.
//

#include "camera.h"


void Camera:: setEye(float x, float y, float z){
    eye.setPosition(x, y, z);
}

void Camera:: setFilm(float w, float h, int nx, int ny) {
    this->w = w;
    this->h = h;
    this->nx = nx;
    this->ny = ny;
}

void Camera:: setDistance(float x){
    this->d = x;
}

void Camera:: setOrientation(float a, float b, float c) {
    Orientation.setDirection(a, b, c);
}

void Camera:: setCor(Vector D){
    Vector up; up.setDirection(0, 1, 0);
    cu = cross_product(D,up);
    cv = cross_product(cu, D);
    cw.setDirection(-D.getX(), -D.getY(), -D.getZ());
    cu.normalize();
    cv.normalize();
    cw.normalize();
}

void Camera:: normalize(Vector u){
    float first =u.getX()/u.norm();
    float second= u.getY()/u.norm();
    float third = u.getZ()/u.norm();
    u.setDirection(first,second,third);
}




Point Camera:: getEye(){
    return eye;
}

float Camera:: getFilmHeight(){
    return h;
}
float Camera:: getFilmWidth() {
    return w;
}

unsigned int Camera:: getFilmNx(){
    return nx;
}

unsigned int Camera:: getFilmNy() {
    return  ny;
}

float Camera:: getDistance(){
    return d;
}

Vector Camera:: getOrientation(){
    return Orientation;
}

Vector Camera::  getCu(){
    return cu;
}

Vector Camera::  getCv(){
    return cv;
}

Vector Camera::  getCw(){
    return cw;
}

