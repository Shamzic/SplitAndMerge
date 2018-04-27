#ifndef __ABSTRACTAREA_H__
#define __ABSTRACTAREA_H__

#include <iostream>
#include <vector>
#include <cmath>
#include "image_ppm.h"
#include <iomanip>
#include <map>
#include <set>
typedef unsigned char OCTET;
using namespace std;

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
    int myId;
    OCTET** data2D;
    std::map<int , AbstractArea*>* voisinMerge;
    //Accessors
    void setX(int x);
    void setY(int y);
    int getX() const;
    int getY() const;
    float getMean() const;
    float getVariance() const;
    float getStandardDeviation() const;
    void showArea();
    void showArea2D();
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
    virtual void conv1Dvers2D();
    virtual bool isHomogeneousArea();
    virtual int getMyId();
    virtual void split2D(double seuil)=0;
    virtual void merge2DContinue( set <int>* alreadyMerged);
    void meanCompute2D();
    void varianceCompute2D();
    bool isHomogeneousArea2D(double seuil);
    void setMean(float mean);
};

#endif