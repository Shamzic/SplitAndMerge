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
	//this->data = data;
	this->subArea = new std::vector<AbstractArea*>();
}


Area::Area(OCTET* data, int w, int h, int x, int y) 
{
	this->w = w;
	this->h = h;
	this->size = w*h;
	this->x = x;
	this->y = y;
	//this->data = data;
	allocation_tableau(this->data, OCTET, this->size);
	for(int i = 0; i<this->w; i++)
		for(int j = 0; j<this->h; j++)
			this->data[i+j*w] = data[i+j*w];
	this->subArea = new std::vector<AbstractArea*>();
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
			temp [i + j*(w/2)] = data[i+j*w];
	Area* a = new Area(temp, w/2, h/2, 0, 0);
	subArea->push_back(a);
	meanCorner(a, ImgOut);
	delete(a);

   // Upper right corner
	for(int i=0; i<this->w/2; i++)
		for(int j = 0; j<this->h/2; j++)
			temp [i + j*(w/2)] = data[(i+(w/2))+j*w];
	Area* b = new Area(temp, w/2, h/2, w/2, 0);	
	subArea->push_back(b);
	meanCorner(b, ImgOut);
	delete(b);

    // lower right corner
	for(int i=0; i<this->w/2; i++)
		for(int j = 0; j<this->h/2; j++)
			temp [i + j*(w/2)] = data[(i+(w/2))+(j+(w/2))*w];
	Area* c = new Area(temp, w/2, h/2, w/2, h/2);	
	subArea->push_back(c);
	meanCorner(c, ImgOut);
	delete(c);

	// lower left corner
	for(int i=0; i<this->w/2; i++)
		for(int j = 0; j<this->h/2; j++)
			temp [i + j*(w/2)] = data[(i)+(j+(w/2))*w];
	Area* d = new Area(temp, w/2, h/2, 0, h/2);	
	subArea->push_back(d);
	meanCorner(d, ImgOut);
	delete(d);
}

void Area::meanCorner(Area* a, OCTET* ImgOut) {
	a->meanCompute();
	std::cout<<"mean corner = "<<a->getMean();
	for(int i = a->x ; i < a->x + a->w; i++)
		for(int j = a->y; j< a->y + a->h; j++)
			ImgOut[i + j*w] = a->mean;
}


void Area::meanCompute() {

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