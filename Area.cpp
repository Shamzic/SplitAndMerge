#include "includes/Area.h"

Area::Area()
{
	this->x = 0;
	this->y = 0;	
}

Area::Area(int w, int h, int x, int y) 
{
	this->w = w;
	this->h = h;
	this->size = w*h;
	this->x = x;
	this->y = y;
	this->data = data;
	this->subArea = new std::vector<AbstractArea>();
}


Area::Area(OCTET* data, int w, int h, int x, int y) 
{
	this->w = w;
	this->h = h;
	this->size = w*h;
	this->x = x;
	this->y = y;
	this->data = data;
	this->subArea = new std::vector<AbstractArea>();
}

Area::~Area()
{
	delete(subArea);	
}


int Area::getNbSubArea() { // TODO
    return 0;
}

void Area::getTabSubArea(OCTET* ImgOut) { // TODO

	OCTET* temp;
	allocation_tableau(temp, OCTET, size/4);

	// Upper left corner
	for(int i=0; i<this->w/2; i++)
		for(int j = 0; j<this->h/2; j++)
			temp [i+j*w/2] = data[i+j*w];
	Area a = Area(temp, w/2, h/2, 0, 0);
	subArea->push_back(a);
	this->meanCorner(a, ImgOut);

/*	// Upper right corner
	for(int i=0; i<this->w/2; i++)
		for(int j = 0; j<this->h/2; j++)
			temp [i+j*w/2] = data[(i+w/2)+j*w];
	subArea->push_back(Area(temp, w/2, h/2, 0, w/2));

	// Lower left corner
	for(int i=0; i<this->w/2; i++)
		for(int j = 0; j<this->h/2; j++)
			temp [i+j*w/2] = data[i+(j+(w/2))*w];
	subArea->push_back(Area(temp, w/2, h/2, h/2, 0));

	// Lower right corner
	for(int i=0; i<this->w/2; i++)
		for(int j = 0; j<this->h/2; j++)
			temp [i+j*w/2] = data[(i+w/2)+(j+(w/2))*w];
	subArea->push_back(Area(temp, w/2, h/2, h/2, w/2));*/

	delete(temp);
}

void Area::meanCorner(Area a, OCTET* ImgOut) {
	a.meanCompute();
	std::cout<<"mean corner = "<<a.getMean();
	for(int i = 0 ; i <h/2; i++)
		for(int j = 0; j<w/2; j++)
			ImgOut[i+j*w] = a.mean;
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