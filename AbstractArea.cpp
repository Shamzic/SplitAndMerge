#include "includes/AbstractArea.h"


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

int AbstractArea::getMean() const
{
    return this->mean;
} 

void AbstractArea::display() const
{
    std::cout << "X = " << this->x << std::endl;
    std::cout << "Y = " << this->y << std::endl;
    std::cout << "W = " << this->w << std::endl;
    std::cout << "H = " << this->h << std::endl;
}

int AbstractArea::getNbSubArea() { // TODO
    return 0;
}

std::vector<AbstractArea>*  AbstractArea::getTabSubArea() { // TODO
    return NULL;
}

void AbstractArea::meanCompute(OCTET* data) { // TODO
	int temp = 0;
	for(int i = 0; i<w; i++)
	{
		for(int j=0; j<h; j++)
		{
			temp+=data[i+j*w];
		}
	}
	mean = temp/(w*h);
}

void AbstractArea::varianceCompute() { // TODO
	;
}