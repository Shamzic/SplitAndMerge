#include "includes/Area.h"


Area::Area()
{
	this->x = 0;
	this->y = 0;	
}


Area::Area(OCTET* data, int w, int h, int x, int y) 
{
	this->w = w;
	this->h = h;
	this->x = x;
	this->y = y;
	this->data = data;
	std::cout<<this->x<<std::endl;
	std::cout<<this->y<<std::endl;
}

int Area::getNbSubArea() { // TODO
    return 0;
}

std::vector<AbstractArea>*  Area::getTabSubArea() { // TODO
    return NULL;
}

void Area::meanCompute() { // TODO

	int temp = 0;
	for(int i = 0; i<this->w; i++)
	{
		for(int j=0; j<this->h; j++)
		{
			temp+=this->data[i+j*this->w];
		}
	}
	this->mean = (double)( (double)temp/(double)(this->w*this->h));
}
void Area::varianceCompute() { // TODO
	;
}