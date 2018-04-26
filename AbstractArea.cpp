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
    this->data = data;
    this->mean = 0;
    this->variance = 0;
    this->data2D = new OCTET*[h];
    for(int i =0 ; i < w ; i++)
    {
        this->data2D[i]= new OCTET[h];
    } 

}


void AbstractArea::showArea()
{
    cout<<"=====>"<<endl;
    for(int i = this->getI() ; i <this->getI() + this->getH() ; i++)
    {
        for(int j = this->getJ() ; j < this->getJ() + this->getW() ; j++)
        {

            cout<<setw(10)<<getIndex(this->getW(), i , j)<<"="<<(int)data[getIndex(this->getW() , i , j)];
        }
        cout <<endl;
    }
    cout<<"=====>"<<endl;
}

void AbstractArea::showArea2D()
{
    cout<<"=====>"<<endl;
    for(int i = this->getI() ; i <this->getI() + this->getH() ; i++)
    {
        for(int j = this->getJ() ; j < this->getJ() + this->getW() ; j++)
        {

            cout<<setw(10)<< i <<","<< j<<"="<<(int)data2D[i][j]<< " ";;
        }
        cout <<endl;
    }
    cout<<"=====>"<<endl;   
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

int AbstractArea::getI() const
{
    return this->y;
}

int AbstractArea::getJ() const
{
    return this->x;
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

float AbstractArea::getMean() const
{
    return this->mean;
} 

float AbstractArea::getVariance() const
{
    return this->variance;
} 

float AbstractArea::getStandardDeviation() const
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
	float temp = 0.0;
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

    float temp = 0.0;
    for(int i = this->getX() ; i < this->getX() + this->getW(); i++)
    {   
        for(int j = this->getY(); j< this->getY() + this->getH(); j++)
        {
        
            temp+=(float)this->data[i+j*this->w];
        }
    }
    this->mean = (float)( (float)temp/(float)(this->size));
}

void AbstractArea::varianceCompute() {
    
    float temp = 0.0;
    for(int i = this->getX() ; i < this->getX() + this->getW(); i++)
    {   
        for(int j = this->getY(); j< this->getY() + this->getH(); j++)
        {
            temp+=(float) (this->data[i+j*this->w] - (this->mean)) * (this->data[i+j*this->w] - (this->mean)) ;
        }
    }
    //std::cout<<"(this->data[10+10*this->w] - (this->mean) : "<<(float)this->data[10+10*this->w] <<" - "<< (this->mean)<<std::endl;
    this->variance = (float)( (float)temp/(float)((this->size)));
}

void AbstractArea::standardDeviationCompute(){
    this->standardDeviation = (float)sqrt(this->variance);
}


bool AbstractArea::isHomogeneousArea()
{
    
    for(int i = this->getI() ; i < this->getI() + this->getH(); i++)
    {   
        for(int j = this->getJ(); j< this->getJ() + this->getW(); j++)
        {
            if(!((data[getIndex(this->getW() , i , j)] < round( this->getMean() + this->getStandardDeviation())) 
                &&
                ( data[getIndex(this->getW() , i , j)] > round( this->getMean() - this->getStandardDeviation()) ) ))
            {
                return false;
            }
            
        }
    }
    return true;
}



//////////////////////////// 2D///////////////////////////////


void AbstractArea::meanCompute2D() {

    float temp = 0.0;
    for(int i = this->getX() ; i < this->getX() + this->getW(); i++)
    {   
        for(int j = this->getY(); j< this->getY() + this->getH(); j++)
        {
        
            temp+=(float)this->data2D[i][j];
        }
    }
    this->mean = (float)( (float)temp/(float)(this->size));
}

void AbstractArea::varianceCompute2D() {
    
    float temp = 0.0;
    for(int i = this->getX() ; i < this->getX() + this->getW(); i++)
    {   
        for(int j = this->getY(); j< this->getY() + this->getH(); j++)
        {
            temp+=(float) (this->data2D[i][j] - (this->mean)) * (this->data2D[i][j] - (this->mean)) ;
        }
    }
    //std::cout<<"(this->data2D[10+10*this->w] - (this->mean) : "<<(float)this->data2D[10+10*this->w] <<" - "<< (this->mean)<<std::endl;
    this->variance = (float)( (float)temp/(float)((this->size)));
}


bool AbstractArea::isHomogeneousArea2D(double seuil)
{
    
    return (this->getVariance() <= seuil);
    
}

void AbstractArea::conv1Dvers2D()
{
    for(int i1 =0; i1 < h ; i1++)
    {
        for(int j1 = 0 ; j1 < w ; j1++ )
        {
            data2D[i1][j1] = data[getIndex(w,i1,j1)];
            
        }

        
    } 
}


