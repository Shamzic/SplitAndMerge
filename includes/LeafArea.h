#ifndef __LEAFAREA_H__
#define __LEAFAREA_H__

#include <iostream>
#include <vector>
#include <cmath>
#include "AbstractArea.h"


class LeafArea : public AbstractArea
{
  public:
    // Constructors
    LeafArea();
    LeafArea(OCTET* data , int w , int h , int x, int y);
    ~LeafArea();
    virtual void split();

};

#endif