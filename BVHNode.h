//
//  BVHNode.h
//  hw1
//
//  Created by liliang on 3/12/16.
//  Copyright © 2016 liliang. All rights reserved.
//

#ifndef BVHNode_h
#define BVHNode_h


#include <stdio.h>
#include "surface.h"
#include <math.h>
#include <algorithm>

class BVHNode: public Surface{
    BVHNode *left;
    BVHNode *right;
    Surface *surface;
public:
    
    BVHNode *buildBVH(int axis, std::vector<Surface *> surface_list){
        BBox *bounds = createBounds(surface_list);
        BVHNode *node = new BVHNode();
        int size = (int)surface_list.size();
        if(size == 1){
            node->surface = surface_list[0];
            bounds->setisLeaf(true);
            bounds->setIndex(surface_list[0]->index);
            node->setbbox(*bounds);      // set box for surface boxes
            return node;
        }
        else{
            node->setbbox(*bounds);   // set box for non-surface boxes
            sortBbox(surface_list, axis);
            std::vector<Surface *> surface_list_1(surface_list.begin(), surface_list.begin() + surface_list.size()/2);
            std::vector<Surface *> surface_list_2(surface_list.begin() + surface_list.size()/2, surface_list.end());
            node->left = buildBVH( (axis+1)%3, surface_list_1);
            node->right =buildBVH( (axis+1)%3, surface_list_2);
            return node;
        }
    }
    
    BBox* createBounds(std::vector<Surface *>& surface_list){
        float minX= std::numeric_limits<int>::max(), minY= minX, minZ= minX;
        float maxX= std::numeric_limits<int>::min(), maxY= maxX, maxZ = maxX;
        for(unsigned int i=0; i<surface_list.size(); i++){
            Surface *s = surface_list[i];
            minX = fmin(s->_min.x,minX);
            maxX = fmax(s->_max.x,maxX);
            minY = fmin(s->_min.y,minY);
            maxY = fmax(s->_max.y,maxY);
            minZ = fmin(s->_min.z,minZ);
            maxZ = fmax(s->_max.z,maxZ);
        }
        return new BBox(minX,minY,minZ,maxX,maxY,maxZ);
    }
    

    struct compareX
    {
        bool operator()(  Surface* a,  Surface* b ) const {
            float mid1X = (a->_min.x + a->_max.x) /2;
            float mid2X = (b->_min.x + b->_max.x) /2;
            return mid1X < mid2X;
        }
    };
    struct compareY
    {
        bool operator()(  Surface* a,  Surface* b ) const {
            float mid1Y = (a->_min.y + a->_max.y) /2;
            float mid2Y = (b->_min.y + b->_max.y) /2;
            return mid1Y < mid2Y;
        }
    };
    struct compareZ
    {
        bool operator()(  Surface* a,  Surface* b ) const {
            float mid1Z = (a->_min.z + a->_max.z) /2;
            float mid2Z = (b->_min.z + b->_max.z) /2;
            return mid1Z < mid2Z;
        }
    };
    
    void sortBbox(std::vector<Surface *> &surface_list, int axis){
        if(axis == 0){
            sort(surface_list.begin(),surface_list.end(), compareX());
        }
        else if (axis == 1){
            sort(surface_list.begin(),surface_list.end(), compareY());
        }
        else
            sort(surface_list.begin(),surface_list.end(), compareZ());
    }
    
    void bboxIntersect(Ray& r, float& closeT, int& index){
        float temp = Surface::bboxIntersect(r);
        if(temp >= 0 and temp <closeT){
            if(bbox.isLeaf){
                float myt =surface->intersection(r);
                if(myt>0.001 and myt <closeT){
                    closeT = myt;
                    index  = bbox.index;
                }
            }
            else{
               if(left != NULL)
                   left->bboxIntersect(r, closeT, index);
               if(right != NULL)
                   right->bboxIntersect(r, closeT, index);
            }

        }
        
    }
    
    bool shadowIntersect(Ray& r, float closeT, bool& find){
        if(find) return true;
        float temp = Surface::bboxIntersect(r);
        if(temp >= 0 and temp <closeT){
            if(bbox.isLeaf){
                float myt =surface->intersection(r);
                if(myt>0.001 and myt <closeT){
                    find = true;
                    return true;
                }
            }
            else{
                return left->shadowIntersect(r,closeT,find) || right->shadowIntersect(r,closeT,find);
            }
        }
        return false;
        
    }
    BVHNode * getLeftNode(){
        return left;
    }
    
    BVHNode * getRightNode(){
        return right;
    }


};

#endif /* BVHNode_h */
