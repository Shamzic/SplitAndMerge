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
    std::vector<AbstractArea*>* neighbors;
  public:
    static std::vector<AbstractArea*>* homogeneousAreas;
    static Area***areaofCase ;
    // Constructors
    static void areaofCaseInit(int w, int h);
    static void homogeneousAreasInit();
    Area();
    Area(OCTET* data, int w, int h, int x, int y);
    Area(OCTET ** data2D, int w , int h , int x , int y);
    ~Area();
    
    int getNbSubArea();
    void getTabSubArea(OCTET* ImgOut);
    void meanCorner(Area* a, OCTET* ImgOut);
    void merge2D(double seuil);
    virtual void split2D(double seuil);
    virtual void split2Dtest(double seuil, int i);
};

#endif