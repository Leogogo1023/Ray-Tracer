//
//  light.h
//  hw1
//
//  Created by liliang on 2/27/16.
//  Copyright © 2016 liliang. All rights reserved.
//

#ifndef light_h
#define light_h

#include <stdio.h>
#include "calculation.h"
#include "point.h"
#include "color.h"

class Light: public Calculation{
    Point position;
    Color color;
public:
    Light(){}
    virtual ~Light(){}
    Point getPosition(){
        return this->position;
    }
    virtual std::vector<Point *> getPosition(int N){
        std::cout<<"Virtual function shouldn't be called"<<std::endl;
        std::vector<Point*> point_list;
        return point_list;
    };
    Color getColor(){
        return this->color;
    }
    virtual Color getColor(Ray& r, Ray& surfaceNormal){
        std::cout<<"Virtual function shouldn't be called"<<std::endl;
        return this->color;
    }
    void setColor(float r, float g, float b){
        this->color.setRGB(r,g,b);
    }
    void setPosition(float x, float y, float z){
        this->position.setPosition(x,y,z);
    }
    
    virtual void setLightDirection(float x, float y, float z){};
    virtual void setUV(float x, float y, float z){};
    virtual void setCenter(float x, float y, float z){};
    virtual void setLen(int len){};
};

class PointLight: public Light{
public:
    PointLight(){}
    ~PointLight(){}
    std::vector<Point*> getPosition(int N){
     //   std::cout<<"This is PointLight"<<std::endl;
        std::vector<Point* > point_list;
        Point* point = new Point();
        point->setPosition(this->Light::getPosition());
        point_list.push_back(point);
        return std::move(point_list);
    }
    Color getColor(Ray r, Ray surfaceNormal){
        return std::move(this->Light::getColor());
    }

};

class AmbientLight: public Light{
public:
    AmbientLight(){}
    ~AmbientLight(){}
    
};
class AreaLight: public Light{
    Ray lightDir;
    Ray u,v;
    Point center, leftCorner;
    int len;
public:
    AreaLight(){}
    ~AreaLight(){}
    std::vector<Point* > getPosition(int N){
      //  std::cout<<"This is AreaLight"<<std::endl;
        std::vector<Point* > point_list;
        for(int p=0; p<N; p++){
            for(int q=0; q<N; q++){
                double r1 = (double)rand() / RAND_MAX;
                double r2 = (double)rand() / RAND_MAX;
                if(N==1) r1=r2=0.5;
                float len_N = len/N;
                Vector corner = leftCorner.getPosition() + u.getDir()*(p*len_N) + v.getDir()*(q*len_N);
                Vector temp = corner + u.getDir()*(r1*len_N) + v.getDir()*(r2*len_N);
                Point* point = new Point();
                point->setPosition(temp);
                point_list.push_back(point);
            }
        }
        return std::move(point_list);
    }
    
    void setLightDirection(float x, float y, float z){
        this->lightDir.setDirection(x, y, z);
    }
    void setUV(float x, float y, float z){
        u.setDirection(x, y, z);
        Vector temp =cross_product(lightDir.getDir(),u.getDir());
        v.setDirection(temp);
    }
    void setCenter(float x, float y, float z){
        center.setPosition(x, y, z);
        Vector temp = center - u.getDir()*0.5*len -v.getDir()*0.5*len;
        leftCorner.setPosition(temp);
    }
    void setLen(int len){
        this->len = len;
    }
    
    Color getColor(Ray& r, Ray& surfaceNormal){
        Color color = Light::getColor();
        Color new_color;
        float temp = dot_product(r.reverse().getDir(), lightDir.getDir());
        new_color.setRGB(color.r *temp, color.g*temp, color.b*temp);
        return std::move(new_color);
    }
    
    
    
};





#endif /* light_h */
