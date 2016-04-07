//
//  camera.h
//  hw1
//
//  Created by liliang on 2/8/16.
//  Copyright © 2016 liliang. All rights reserved.
//

#ifndef camera_h
#define camera_h
#include <vector>
#include "point.h"
#include "vector.h"
#include "calculation.h"


class Camera: public Calculation {

    float d;
    Point eye;
        
    unsigned int nx;
    unsigned int ny;
    
    Vector Orientation;
    
    Vector cu;
    Vector cv;
    Vector cw;
    
    float w,h;
    
public:
    void setEye(float x, float y, float z);
    void setFilm(float w, float h, int nx, int ny);
    void setDistance(float x);
    void setOrientation(float a, float b, float c);
    void setCor(Vector u);
    void normalize(Vector u);
    
    Point getEye();
    float getFilmWidth();
    float getFilmHeight();
    unsigned int getFilmNx();
    unsigned int getFilmNy();
    float getDistance();
    Vector getOrientation();
    Vector getCu();
    Vector getCv();
    Vector getCw();
    
    
};


#endif /* camera_h */
