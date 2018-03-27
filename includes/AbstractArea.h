#ifndef __ABSTRACTAREA_H__
#define __ABSTRACTAREA_H__

#include <iostream>
#include <vector>
#include <cmath>
#include "image_ppm.h"

typedef unsigned char OCTET;

class AbstractArea
{
  protected: 
    int x,y;
    int w,h;
    int size;
    OCTET* data;
    double mean;

  public:
    //Accessors
    virtual ~AbstractArea();
    void setX(int x);
    void setY(int y);
    int getX() const;
    int getY() const;
    int getMean() const;

    // Other methods
    void display() const;
    virtual int getNbSubArea();

    /*virtual std::vector<AbstractArea>* getTabSubArea();*/
    virtual void getTabSubArea();

    virtual void meanCompute(OCTET* data);
    virtual void varianceCompute();
};

#endif