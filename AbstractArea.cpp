#include "includes/AbstractArea.h"

AbstractArea::AbstractArea()
{
    this->w = w;
    this->h = h;
    this->x = 0;
    this->y = 0;    
    this->size = w*h;
    this->mean = 0;
    this->variance = 0;
}


AbstractArea::AbstractArea(OCTET * data , int w, int h, int x, int y)
{
    this->w = w;
    this->h = h;
    this->size = w*h;
    this->x = x;
    this->y = y;
    this->data = data
    this->mean = 0;
    this->variance = 0;
}

AbstractArea::~AbstractArea() {
 	free(data);
 }
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

int AbstractArea::getW() const
{
    return this->w;
} 

int AbstractArea::getH() const
{
    return this->h;
}

int AbstractArea::setW(int w)
{
    return this->w=w;
} 

int AbstractArea::setH(int h)
{
    return this->h=h;
}  

int AbstractArea::getMean() const
{
    return this->mean;
} 

int AbstractArea::getVariance() const
{
    return this->variance;
} 

int AbstractArea::getStandardDeviation() const
{
    return this->standardDeviation;
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


void  AbstractArea::getTabSubArea() { // TODO
    ;
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

void AbstractArea::meanCompute() {

    int temp = 0;
    for(int i = this->getX() ; i < this->getX() + this->getW(); i++)
    {   
        for(int j = this->getY(); j< this->getY() + this->getH(); j++)
        {
            temp+=this->data[i+j*this->w];
        }
    }
    this->mean = (double)( (double)temp/(double)(this->size));
}

void AbstractArea::varianceCompute() {
    this->meanCompute();
    int temp = 0;
    for(int i = this->getX() ; i < this->getX() + this->getW(); i++)
    {   
        for(int j = this->getY(); j< this->getY() + this->getH(); j++)
        {
            temp += (this->data[i+j*this->w] - (this->mean)) * (this->data[i+j*this->w] - (this->mean)) ;
        }
    }
    //std::cout<<"(this->data[10+10*this->w] - (this->mean) : "<<(double)this->data[10+10*this->w] <<" - "<< (this->mean)<<std::endl;
    this->variance = (double)( (double)temp/(double)((this->size)));
}

void AbstractArea::standardDeviationCompute(){
    this->standardDeviation = sqrt(this->variance);
}


bool AbstractArea::isHomogeneousArea(int w , int h , int x , int y)
{
    
    for(int i = x ; i < x + w; i++)
    {   
        for(int j = y; j< y + h; j++)
        {
            if(!((data[getIndex(w , i , j)] < this->getMean() + this->getStandardDeviation()) + 1
                && 
                ( data[getIndex(w , i , j)] > this->getMean() + this->getStandardDeviation()) - 1) )
            {
                return false;
            }
            
        }
    }
    return true;
}