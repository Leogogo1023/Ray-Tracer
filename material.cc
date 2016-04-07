//
//  material.cc
//  hw1
//
//  Created by liliang on 2/13/16.
//  Copyright © 2016 liliang. All rights reserved.
//

#include "material.h"

void Material:: setDiffuse(float d_r, float d_g, float d_b){
    diffuse.setRGB(d_r, d_g, d_b);
}

void Material:: setReflective(float d_r, float d_g, float d_b){
    reflective.setRGB(d_r, d_g, d_b);
    if(d_r==0 && d_g ==0 && d_b==0)
        this->isReflective =false;
    else
        this->isReflective =true;
}


void Material:: setSpecular(float d_r, float d_g, float d_b){
    specular.setRGB(d_r, d_g, d_b);
}

void Material:: setRoughness(float r){
    this->roughness = r;
}

Color Material:: getDiffuse(){
    return diffuse;
}

Color Material:: getReflective(){
    return reflective;
}

Color Material:: getSpecular(){
    return specular;
}

float Material:: getRoughness(){
    return roughness;
}
