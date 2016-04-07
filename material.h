//
//  material.h
//  hw1
//
//  Created by liliang on 2/13/16.
//  Copyright © 2016 liliang. All rights reserved.
//

#ifndef material_h
#define material_h

#include <stdio.h>
#include "color.h"
class Material {
    Color diffuse;
    Color specular;
    Color reflective;
    float roughness;
    
    public :
    bool isReflective;
    void setDiffuse(float d_r, float d_g, float d_b);
    void setSpecular(float d_r, float d_g, float d_b);
    void setReflective(float d_r, float d_g, float d_b);
    void setRoughness(float r);
    Color getDiffuse();
    Color getReflective();
    Color getSpecular();
    float getRoughness();
};

#endif /* material_h*/
