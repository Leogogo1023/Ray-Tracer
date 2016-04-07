//
//  calculation.h
//  hw1
//
//  Created by liliang on 2/11/16.
//  Copyright © 2016 liliang. All rights reserved.
//

#ifndef calculation_h
#define calculation_h
#include "vector.h"

#include <stdio.h>
#include <math.h>
class Calculation{
public:
    float dot_product(Vector a, Vector b);
    Vector addThree(Vector a, Vector b, Vector c);
    Vector minus(Vector a, Vector b);
    Vector cross_product(Vector a, Vector b);
    
};

#endif /* calculation_h */
