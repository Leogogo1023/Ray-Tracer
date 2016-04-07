//
//  point.h
//  hw1
//
//  Created by liliang on 2/8/16.
//  Copyright © 2016 liliang. All rights reserved.
//

#ifndef point_hpp
#define point_hpp

#include <stdio.h>
#include "vector.h"

class Point :public Vector{
public:
    void setPosition(Vector a);
    void setPosition(float a, float b, float c);
    
};

#endif /* point_h */
