#ifndef __AREA_H__
#define __AREA_H__

#include <iostream>
#include <vector>
#include <cmath>
#include "AbstractArea.h"
#include "image_ppm.h"
#include <iostream>
#include <iomanip>


class Area : public AbstractArea
{
  protected:
    std::vector<AbstractArea*>* subArea;

  public:
    // Constructors
    Area();
    Area(OCTET* data, int w, int h, int x, int y);
    ~Area();
    int getNbSubArea();
    void getTabSubArea(OCTET* ImgOut);
    void meanCorner(Area* a, OCTET* ImgOut);
    void showArea();
    virtual void split();
};

#endif