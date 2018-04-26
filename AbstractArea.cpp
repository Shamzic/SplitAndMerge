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
    this->meanR = 0;
    this->meanG = 0;
    this->meanB = 0;
    this->varianceR = 0;
    this->varianceG = 0;
    this->varianceB = 0;
    this->data2D = NULL;
    this->data3D = NULL;
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
    this->meanR = 0;
    this->meanG = 0;
    this->meanB = 0;
    this->varianceR = 0;
    this->varianceG = 0;
    this->varianceB = 0;
    //TODO fuite memoire 
    this->data2D = new OCTET*[h];

    for(int i =0 ; i < h ; i++)
    {
        this->data2D[i]= new OCTET[h];
    } 



    this->data3D = new OCTET**[h];
    
    for(int i =0 ; i < h ; i++)
    {
        this->data3D[i]= new OCTET*[w];
    }
    for(int i =0 ; i < h ; i++)
        for(int j =0 ; j < w ; j++)
        {
            this->data3D[i][j]= new OCTET[3];
        }
}


void AbstractArea::showArea()
{
    // cout<<"=====>"<<endl;
    // for(int i = this->getI() ; i <this->getI() + this->getH() ; i++)
    // {
    //     for(int j = this->getJ() ; j < this->getJ() + this->getW() ; j++)
    //     {

    //         cout<<setw(10)<<getIndex(this->getW(), i , j)<<"="<<(int)data[getIndex(this->getW() , i , j)];
    //     }
    //     cout <<endl;
    // }
    // cout<<"=====>"<<endl;
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

float AbstractArea::getStandardDeviationR() const
{
    return this->standardDeviationR;
}

float AbstractArea::getStandardDeviationG() const
{
    return this->standardDeviationG;
}

float AbstractArea::getStandardDeviationB() const
{
    return this->standardDeviationB;
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
    
    return (this->getStandardDeviation() <= seuil);

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


bool operator==(const AbstractArea &a1 , const AbstractArea &a2)
{
    return a1.getH() == a2.getH() &&
           a1.getW() == a2.getW() &&
           a1.getI() == a2.getI() &&
           a1.getJ() == a2.getI();
}

bool operator!=(const AbstractArea &a1 , const AbstractArea &a2)
{
    return ! (a1 == a2); 
}


///////////////// 3D ////////////////////

void AbstractArea::conv1Dvers3D()
{
    int i2=0,j2=0;

    for(int i1 =0; i1 < w * h * 3; i1+=3)
    {
        if(i1 != 0 && (i1 % (w*3)) == 0)
        {
            i2++;
            j2=0;       
        }
        data3D[i2][j2][0] = this->data[i1];
        data3D[i2][j2][1] = this->data[i1];
        data3D[i2][j2][2] = this->data[i1];
        j2++;
    } 
}


void AbstractArea::varianceCompute3D_R() {
    
    float temp = 0.0;
    for(int i = this->getX() ; i < this->getX() + this->getW(); i++)
    {   
        for(int j = this->getY(); j< this->getY() + this->getH(); j++)
        {
            temp+=(float) (this->data3D[i][j][0] - (this->mean)) * (this->data3D[i][j][0] - (this->mean)) ;
        }
    }
    //std::cout<<"(this->data2D[10+10*this->w] - (this->mean) : "<<(float)this->data2D[10+10*this->w] <<" - "<< (this->mean)<<std::endl;
    this->varianceR = (float)( (float)temp/(float)((this->size)));
}


void AbstractArea::varianceCompute3D_G() {
    
    float temp = 0.0;
    for(int i = this->getX() ; i < this->getX() + this->getW(); i++)
    {   
        for(int j = this->getY(); j< this->getY() + this->getH(); j++)
        {
            temp+=(float) (this->data3D[i][j][1] - (this->mean)) * (this->data3D[i][j][1] - (this->mean)) ;
        }
    }
    //std::cout<<"(this->data2D[10+10*this->w] - (this->mean) : "<<(float)this->data2D[10+10*this->w] <<" - "<< (this->mean)<<std::endl;
    this->varianceG = (float)( (float)temp/(float)((this->size)));
}

void AbstractArea::varianceCompute3D_B() {
    
    float temp = 0.0;
    for(int i = this->getX() ; i < this->getX() + this->getW(); i++)
    {   
        for(int j = this->getY(); j< this->getY() + this->getH(); j++)
        {
            temp+=(float) (this->data3D[i][j][2]- (this->mean)) * (this->data3D[i][j][2] - (this->mean)) ;
        }
    }
    //std::cout<<"(this->data2D[10+10*this->w] - (this->mean) : "<<(float)this->data2D[10+10*this->w] <<" - "<< (this->mean)<<std::endl;
    this->varianceB = (float)( (float)temp/(float)((this->size)));
}

void AbstractArea::meanCompute3D_R() {

    float temp = 0.0;
    for(int i = this->getX() ; i < this->getX() + this->getW(); i++)
    {   
        for(int j = this->getY(); j< this->getY() + this->getH(); j++)
        {
            temp+=(float)this->data3D[i][j][0];
        }
    }
    this->meanR = (float)( (float)temp/(float)(this->size));
}

void AbstractArea::meanCompute3D_G() {

    float temp = 0.0;
    for(int i = this->getX() ; i < this->getX() + this->getW(); i++)
    {   
        for(int j = this->getY(); j< this->getY() + this->getH(); j++)
        {
            temp+=(float)this->data3D[i][j][1];
        }
    }
    this->meanG = (float)( (float)temp/(float)(this->size));
}

void AbstractArea::meanCompute3D_B() {

    float temp = 0.0;
    for(int i = this->getX() ; i < this->getX() + this->getW(); i++)
    {   
        for(int j = this->getY(); j< this->getY() + this->getH(); j++)
        {
            temp+=(float)this->data3D[i][j][2];
        }
    }
    this->meanB = (float)( (float)temp/(float)(this->size));
}

void AbstractArea::standardDeviationCompute_R(){
    this->standardDeviationR = (float)sqrt(this->varianceR);
}

void AbstractArea::standardDeviationCompute_G(){
    this->standardDeviationG = (float)sqrt(this->varianceG);
}

void AbstractArea::standardDeviationCompute_B(){
    this->standardDeviationB = (float)sqrt(this->varianceB);
}

bool AbstractArea::isHomogeneousArea3D(double seuil)
{
    return ((this->getStandardDeviationR() <= seuil) &&
            (this->getStandardDeviationG() <= seuil) &&
            (this->getStandardDeviationB() <= seuil));
}

float AbstractArea::getMeanR() const
{
    return this->meanR;
} 
float AbstractArea::getMeanG() const
{
    return this->meanG;
} 
float AbstractArea::getMeanB() const
{
    return this->meanB;
} 
