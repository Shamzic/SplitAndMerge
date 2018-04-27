#include "includes/Area.h"
using namespace std;

Area *** Area::areaofCase = NULL;

vector<AbstractArea*>* Area::homogeneousAreas = NULL;

int Area::areaId = 0;


int Area::getAreaId()
{
	return Area::areaId++;
}

void Area::areaofCaseInit(int w , int h) // Only leaf
{
	Area::areaofCase = new Area**[h];
	
	for(int i =0 ; i < h ; i++)
	{
		Area::areaofCase[i] = new Area*[w];
		for(int j = 0 ; j < w ; j++ ) 
		{
			Area::areaofCase[i][j]= NULL;
		}
	}
 
}

int Area::getMyId()
{
	return this->myId;
}
 
void Area::homogeneousAreasInit()
{
	homogeneousAreas = new vector<AbstractArea*> ();
}

Area::Area()
{
	this->subArea = NULL;
}

Area::Area(OCTET* data, int w, int h, int x, int y) : AbstractArea(data,w,h,x,y)
{
	this->data2D = data2D;
	this->subArea = new std::vector<AbstractArea*>();	
	this->subArea = new std::vector<AbstractArea*>();
	this->neighbors = new std::vector<AbstractArea*>();
	
	
}

Area::Area(OCTET ** data2D, int w , int h , int x , int y) : AbstractArea(NULL, w , h ,x ,y)
{
	this->data2D = data2D;
	this->subArea = new std::vector<AbstractArea*>();
	this->neighbors = new std::vector<AbstractArea*>();

}

// Area::Area(OCTET** data2D , int w , int h , int x , int y) : AbstracArea(data2D,w,h,x,y)
// {
// 	this->subArea= new std::vector<AbstracArea*>();
// }

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

void Area::split2D(double seuil)
{
	int areas_info[4][4]=
	{
		{w/2, h/2, this->getJ()       , this->getI()},
		{w/2, h/2, this->getJ() + w/2 , this->getI()},
		{w/2, h/2, this->getJ()       , this->getI() + h/2},
		{w/2, h/2, this->getJ() + w/2 , this->getI() + h/2}
	};

	this->meanCompute2D();
	this->varianceCompute2D();
	this->standardDeviationCompute();
	
	
	
	this->showArea2D();

	if(this->getW() > 1 && this->getH() > 1 && !this->isHomogeneousArea2D(seuil))
	{
		cout<<"not homogeneous area"<<endl<<endl;

		for (int i = 0 ; i < 4 ; i++)
		{
			Area * area = new Area(data2D, 
				areas_info[i][0], 
				areas_info[i][1], 
				areas_info[i][2], 
				areas_info[i][3]);
			area->myId = Area::getAreaId();
			subArea->push_back(area);
		}
		for(int i = 0 ; i < 4 ; i ++)
		{

			subArea->at(i)->split2D(seuil);
		}

	}
	else
	{
		Area::homogeneousAreas->push_back(this);
		
		
		
		cout<<"homogenous area"<<endl;
		
		for(int i = this->getI() ; i <this->getI() + h ; i ++)
		{
			for(int j = this->getJ() ; j <this->getJ() + w ; j++)
			{
				Area::areaofCase[i][j] = (this);
				
			}
		}


	}
	cout<<endl<<endl;
}

void Area::merge2D(double seuil)
{
	for(int i= this->getI() ; i <this->getI() + this->getH() ; i++)
	{
		for (int j = this->getJ() ; j <this->getJ() + this->getW() ; j++)
		{
			for(int ii = i - 1 ; ii < i + 2 ; ii++ )
			{
				for(int jj = j - 1 ; jj < j + 2 ; jj++)
				{

					// cout<<i<<","<<j<<" "<<ii<<","<<jj<<endl;
					if(	   ii >= 0 
						&& ii < this->getH() 
						&& jj >=0 
						&& jj < this->getW() 
						&& i != ii && j != jj 
						&& areaofCase[i][j]->getMyId() != areaofCase[ii][jj]->getMyId() 
						&& 
						(abs(areaofCase[i][j]->getMean() - areaofCase[ii][jj]->getMean()) < seuil) )
					{
						cout<<endl;
						cout<<"========================="<<i<<","<<j<<" and "<<ii<<","<<jj<<endl;
						areaofCase[i][j]->showArea2D();
						areaofCase[ii][jj]->showArea2D();

						areaofCase[ii][jj]->voisinMerge->insert(std::pair<int, AbstractArea*> (areaofCase[i][j]->getMyId() , areaofCase[i][j]));

						areaofCase[i][j]->voisinMerge->insert(std::pair<int , AbstractArea*>(areaofCase[ii][jj]->getMyId() , areaofCase[ii][jj]));
					}
				}
			}


		}
	}

}
 
// bool operator==(const Area &a1 , const Area &a2)
// {
//     return a1.getMyId() == a2.getMyId();
// }


// bool operator!=(const Area &a1 , const Area &a2)
// {
//     return ! (a1 == a2); 
// }


// void Area::gatherNeighbors(double seuil)
// {
// 	//Case of an homogeneous area
// 	if(subArea->size() == 0)
// 	{
// 		for(int j = getJ() ; j < this->getW() ; j ++)
// 		{
			
// 		}
// 	}
// }