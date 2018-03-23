#ifndef ABSTRACTAREA_H
#define ABSTRACTAREA_H

#include <iostream>
#include <vector>

class AbstractArea
{
  private: 
    int x,y;
    int w,h;
    double mean;

  public:
    // Constructors
    AbstractArea();
    AbstractArea(int x, int y);

    //Accessors
    void setX(int x);
    void setY(int y);
    int getX() const;
    int getY() const;

    // Other methods
    void display() const;
    virtual int getNbSubArea();
    virtual std::vector<AbstractArea>* getTabSubArea();

    virtual void meanCompute();
    virtual void varianceCompute();
};

#endif