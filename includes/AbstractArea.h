#ifndef __ABSTRACTAREA_H__
#define __ABSTRACTAREA_H__

#include <iostream>
#include <vector>
#include <cmath>

typedef unsigned char OCTET;

class AbstractArea
{
  protected: 
    int x,y;
    int w,h;
    OCTET* data;
    double mean;

  public:
    //Accessors
    void setX(int x);
    void setY(int y);
    int getX() const;
    int getY() const;
    int getMean() const;

    // Other methods
    void display() const;
    virtual int getNbSubArea();
    virtual std::vector<AbstractArea>* getTabSubArea();

    virtual void meanCompute(OCTET* data);
    virtual void varianceCompute();
};

#endif