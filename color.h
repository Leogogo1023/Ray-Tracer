//
//  color.h
//  hw1
//
//  Created by liliang on 2/13/16.
//  Copyright © 2016 liliang. All rights reserved.
//

#ifndef color_h
#define color_h

#include <stdio.h>
class Color{
    friend class AreaLight;
    float r;
    float g;
    float b;
    public :
    void setRGB(float r, float g, float b);
    float getR();
    float getG();
    float getB();
    
};


#endif /* color_h */
