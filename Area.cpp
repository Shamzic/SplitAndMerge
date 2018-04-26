#include "includes/Area.h"
using namespace std;

Area *** Area::areaofCase = NULL;
Area **** Area::areaofCase3D = NULL;

vector<AbstractArea*>* Area::homogeneousAreas = NULL;

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

void Area::areaofCaseInit3D(int w , int h) // Only leaf
{
	Area::areaofCase3D = new Area***[h];
	
	for(int i =0 ; i < h ; i++)
	{
		Area::areaofCase3D[i] = new Area**[w];
		for(int j = 0 ; j < w ; j++ ) 
		{
			Area::areaofCase3D[i][j] = new Area*[3];
			for(int k= 0; k<3; k++)
				Area::areaofCase3D[i][j][k]= NULL;
		}
	}
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
	this->subArea = new std::vector<AbstractArea*>();
		
	
}

Area::Area(OCTET ** data2D, int w , int h , int x , int y) : AbstractArea(NULL, w , h ,x ,y)
{
	this->data2D = data2D;
	this->subArea = new std::vector<AbstractArea*>();
	this->neighbors = new std::vector<AbstractArea*>();
}

Area::Area(OCTET *** data3D, int w , int h , int x , int y, int troisD) : AbstractArea(NULL, w , h ,x ,y)
{
	this->data3D = data3D;
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
		{w/2, h/2, 0   +this->getJ(),this->getI() + 0},
		{w/2, h/2, w/2 +this->getJ(),this->getI() + 0},
		{w/2, h/2, 0   +this->getJ(),this->getI() + h/2},
		{w/2, h/2, w/2 +this->getJ(),this->getI() + h/2}
	};

	this->meanCompute2D() ;
//	cout<<(float)this->getMean();
	this->varianceCompute2D() ;
//	cout<<" "<<(float)this->getVariance();
	this->standardDeviationCompute();
/*	cout<<" "<<(float)this->getStandardDeviation();
	cout<<endl;*/

	
	//this->showArea2D();
	if(this->getW() > 1 && this->getH() > 1 && !this->isHomogeneousArea2D(seuil))
	{
		//cout<<"not homogeneous area"<<endl<<endl;

		for (int i = 0 ; i < 4 ; i++)
		{
			subArea->push_back(new Area(data2D, 
				areas_info[i][0], 
				areas_info[i][1], 
				areas_info[i][2], 
				areas_info[i][3]));
		}
		for(int i = 0 ; i < 4 ; i ++)
		{

			subArea->at(i)->split2D(seuil);
		}

	}
	else
	{
		Area::homogeneousAreas->push_back(this);
		
		/*cout<<"homogenous area"<<endl;
		cout<<" "<<(float)this->getVariance()<<endl;*/
		for(int i = this->getI() ; i <this->getI() + h ; i ++)
		{
			for(int j = this->getJ() ; j <this->getJ() + w ; j++)
			{
				Area::areaofCase[i][j] = (this);
				
			}
		}


	}
//	cout<<endl<<endl;
}

void Area::merge2D(double seuil)
{
	for(int i= 0 ; i < this->getH() ; i++)
	{
		for (int j = 0 ; j < this->getW() ; j++)
		{
			for(int ii = i - 1 ; ii < i + 3 ; ii++ )
			{
				for(int jj = j -1 ; jj < j + 3 ; jj++)
				{
					if(ii >= 0 && ii < this->getH() && jj >=0 && jj < this->getW() )
					{
											
					}
				}
			}


		}
	}
}


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

void Area::split3D(double seuil)
{
	int areas_info[4][4]=
	{
		{w/2, h/2, 0   +this->getJ(),this->getI() + 0},
		{w/2, h/2, w/2 +this->getJ(),this->getI() + 0},
		{w/2, h/2, 0   +this->getJ(),this->getI() + h/2},
		{w/2, h/2, w/2 +this->getJ(),this->getI() + h/2}
	};

	this->meanCompute3D_R();
	this->meanCompute3D_G() ;
	this->meanCompute3D_B() ;
//	cout<<(float)this->getMean();
	this->varianceCompute3D_R();
	this->varianceCompute3D_G();
	this->varianceCompute3D_B();

	this->standardDeviationCompute_R();
	this->standardDeviationCompute_G();
	this->standardDeviationCompute_B();

	cout<<"ok"<<endl;

	if(this->getW() > 1 && this->getH() > 1 && !this->isHomogeneousArea3D(seuil))
	{
		//cout<<"not homogeneous area"<<endl<<endl;

		for (int i = 0 ; i < 4 ; i++)
		{
			this->subArea->push_back(new Area(data3D, 
				areas_info[i][0], 
				areas_info[i][1], 
				areas_info[i][2], 
				areas_info[i][3],1));
		}

		for(int i = 0 ; i < 4 ; i ++)
		{
			this->subArea->at(i)->split3D(seuil);
		}
	}
	else
	{
		Area::homogeneousAreas->push_back(this);
		cout<<"homogeneous"<<endl;
		for(int i = this->getI() ; i <this->getI() + h ; i ++)
		{
			for(int j = this->getJ() ; j <this->getJ() + w ; j++)
			{
				for(int k= 0; k<3; k++)
					Area::areaofCase3D[i][j][k] = (this);
				
			}
		}


	}
//	cout<<endl<<endl;
}