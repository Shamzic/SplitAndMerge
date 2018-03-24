#ifndef __AREA_H__
#define __AREA_H__

#include <iostream>
#include <vector>
#include <cmath>
#include "AbstractArea.h"


class Area : public AbstractArea
{
  protected:
    std::vector<AbstractArea>* subArea;

  public:
    // Constructors
    Area();
    Area(OCTET* data, int w, int h, int x, int y);

    int getNbSubArea();
    std::vector<AbstractArea>* getTabSubArea();
    void meanCompute();
    void varianceCompute();
};

#endif