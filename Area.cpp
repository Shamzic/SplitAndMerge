#include "includes/Area.h"
using namespace std;
Area::Area()
{
	this->subArea = NULL;
}

Area::Area(OCTET* data, int w, int h, int x, int y) : AbstractArea(data,w,h,x,y)
{
	this->subArea = new std::vector<AbstractArea*>();	
}

Area::~Area()
{
		
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

   // Upper right corner
	for(int i=0; i<this->w/2; i++)
		for(int j = 0; j<this->h/2; j++)
			temp [i + j*(w/2)] = data[(i+(w/2))+j*w];
	Area* b = new Area(temp, w/2, h/2, w/2, 0);	
	subArea->push_back(b);
	meanCorner(b, ImgOut);

    // lower right corner
	for(int i=0; i<this->w/2; i++)
		for(int j = 0; j<this->h/2; j++)
			temp [i + j*(w/2)] = data[(i+(w/2))+(j+(w/2))*w];
	Area* c = new Area(temp, w/2, h/2, w/2, h/2);	
	subArea->push_back(c);
	meanCorner(c, ImgOut);

	// lower left corner
	for(int i=0; i<this->w/2; i++)
		for(int j = 0; j<this->h/2; j++)
			temp [i + j*(w/2)] = data[(i)+(j+(w/2))*w];
	Area* d = new Area(temp, w/2, h/2, 0, h/2);	
	subArea->push_back(d);
	meanCorner(d, ImgOut);
}

void Area::meanCorner(Area* a, OCTET* ImgOut) {
	a->meanCompute();
	std::cout<<"mean corner = "<<a->getMean()<<std::endl;
	a->varianceCompute();
	std::cout<<"variance corner = "<<a->getVariance()<<std::endl;
	for(int i = a->x ; i < a->x + a->w; i++)
		for(int j = a->y; j< a->y + a->h; j++)
			ImgOut[i + j*w] = a->mean;
}

void Area::showArea()
{
	cout<<"=====>"<<endl;
	for(int i = this->getI() ; i < this->getH() ; i++)
	{
		for(int j = this->getJ() ; j < this->getW() ; j++)
		{
			cout<<setw(5)<<(int)data[getIndex(this->getW() , this->getI() , this->getJ())];
		}
		cout <<endl;
	}
	cout<<"=====>"<<endl;
}

void Area::split()
{
	int areas_info[4][4]=
	{
		{w/2, h/2, 0, 0},
		{w/2, h/2, w/2, 0},
		{w/2, h/2, w/2, h/2},
		{w/2, h/2, 0, h/2}
	};

	this->showArea();
	if(this->getW() > 1 && this->getH() > 1 && !this->isHomogeneousArea())
	{
		cout<<"not homogeneous area"<<endl<<endl;

		for (int i = 0 ; i < 4 ; i++)
		{
			subArea->push_back(new Area(data, areas_info[i][0], areas_info[i][1], areas_info[i][2], areas_info[i][3]));
		}
		for(int i = 0 ; i < 4 ; i ++)
		{
			subArea->at(i)->split();
		}
	}
	else if(this->getW() > 1 && this->getH() > 1)
	{
		cout<<"homogenous area"<<endl;
	}
	else
	{
		cout<<"small area"<<endl;
	}
}
