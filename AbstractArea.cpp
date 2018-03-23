
#include <cmath>
#include <iostream>
#include "includes/AbstractArea.h"

AbstractArea::AbstractArea() : x(0), y(0)
{}

AbstractArea::AbstractArea(int x, int y) : x(x), y(y)
{}

void AbstractArea::setX(int x)
{
    this->x = x;
}

void AbstractArea::setY(int y)
{
    this->y = y;
}

int AbstractArea::getX() const
{
    return this->x;
} 

int AbstractArea::getY() const
{
    return this->y;
} 

void AbstractArea::display() const
{
    std::cout << "X = " << this->x << std::endl;
    std::cout << "Y = " << this->y << std::endl;
}

int AbstractArea::getNbSubArea() { // TODO
    return 0;
}

std::vector<AbstractArea>*  AbstractArea::getTabSubArea() { // TODO
    return NULL;
}

void AbstractArea::meanCompute() { // TODO

}
void AbstractArea::varianceCompute() { // TODO

}