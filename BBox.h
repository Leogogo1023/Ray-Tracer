//
//  BBox.h
//  hw1
//
//  Created by liliang on 3/12/16.
//  Copyright © 2016 liliang. All rights reserved.
//

#ifndef BBox_h
#define BBox_h

#include <stdio.h>
#include "surface.h"
//#include "triangle.h"

class BBox {
    friend class BVHNode;
    friend class Surface;
    Point bboxMin, bboxMax;
    int index;
    bool isLeaf =false;
 //   Surface *surface;
public:
    BBox(){};
    BBox(float xmin, float ymin, float zmin, float xmax, float ymax, float zmax){
         bboxMin.setPosition(xmin-0.001, ymin-0.001, zmin-0.001);
         bboxMax.setPosition(xmax+0.001, ymax+0.001, zmax+0.001);
    }
    ~BBox(){};
    
    void setisLeaf(bool isleaf){
        isLeaf = isleaf;
    }
    bool getisLeaf(){
        return std::move(isLeaf);
    }
    void setbboxMin(float x, float y, float z){
        bboxMin.setPosition(x, y, z);
    }
    void setbboxMax(float x, float y, float z){
        bboxMax.setPosition(x, y, z);
    }
    Point getbboxMin(){
        return std::move(bboxMin);
    }
    Point getbboxMax(){
        return std::move(bboxMax);
    }
    void setIndex(int index){
        this->index = index;
    }
    int getIndex(){
        return std::move(index);
    }
};

#endif /* BBox_h */
