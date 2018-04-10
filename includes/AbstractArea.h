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
    double variance;
    double standardDeviation;
  public:

    //Accessors
    void setX(int x);
    void setY(int y);
    int getX() const;
    int getY() const;
    int getMean() const;
    int getVariance() const;
    int getStandardDeviation() const;
    virtual int getI() const;
    virtual int getJ() const;

    virtual int getW() const;
    virtual int getH() const;
    
    virtual int setW(int w);
    virtual int setH(int h);

    // Other methods
    void display() const;
    
    AbstractArea();
    AbstractArea(OCTET* data , int w, int h, int x, int y);
    virtual ~AbstractArea();
    
    virtual int getNbSubArea();
    virtual void getTabSubArea();
    
    virtual void meanCompute(OCTET* data);
    virtual void meanCompute();
    virtual void varianceCompute();
    virtual void standardDeviationCompute();
    
    virtual bool isHomogeneousArea();
    virtual void split()=0;
    
};

#endif