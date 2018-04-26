#include <stdio.h>
#include <iostream>
#include "includes/Area.h"

using namespace std;



int main(int argc, char* argv[])
{
  char cNomImgLue[250], cNomImgEcrite[250];
  int nH=0, nW=0, nTaille;

  if (argc == 3) 
  {
    
    sscanf (argv[1],"%s",cNomImgLue) ;
    sscanf (argv[2],"%s",cNomImgEcrite);
    //sscanf (argv[3],"%d",&S);

    OCTET *ImgIn, *ImgOut; 

    lire_nb_lignes_colonnes_image_pgm(cNomImgLue, &nH, &nW);
    nTaille = nH * nW;

    allocation_tableau(ImgIn, OCTET, nTaille);
    lire_image_pgm(cNomImgLue, ImgIn, nH * nW);
    allocation_tableau(ImgOut, OCTET, nTaille);
    

    Area* a = new Area(ImgIn,nW,nH,0,0); // Total area image
    a->meanCompute();
    std::cout<<"Mean of the image : "<<a->getMean()<<std::endl;
    a->getTabSubArea(ImgOut); // Division in 4 mean corner : OK
    ecrire_image_pgm(cNomImgEcrite, ImgOut,  nH, nW);
    free(ImgIn);
  }

  

  // for(int i = O; i < this->h; i++)
  // {
    
  // }
  else if(argc == 1)
  {
    OCTET * imgTest;
    allocation_tableau(imgTest , OCTET , 16) ;
    imgTest[0] =1 ; imgTest[1] =1 ; imgTest[2] =3 ; imgTest[3] =2 ;
    imgTest[4] =1 ; imgTest[5] =2 ; imgTest[6] =4 ; imgTest[7] =7 ;
    imgTest[8] =7 ; imgTest[9] =6 ; imgTest[10]=2 ; imgTest[11]=3 ; 
    imgTest[12]=4 ; imgTest[13]=5 ; imgTest[14]=6 ; imgTest[15]=1 ;
    
    Area* a_split_test = new Area(imgTest,4,4,0,0); // Total area image
    
    a_split_test->showArea();
    a_split_test->conv1Dvers2D();
    a_split_test->showArea2D();
    
    a_split_test->meanCompute2D();
    cout<<(float)a_split_test->getMean();
    a_split_test->varianceCompute2D();
    
    cout<<" "<<(float)a_split_test->getVariance();
    a_split_test->standardDeviationCompute();
    cout<<" "<<(float)a_split_test->getStandardDeviation();
    cout<<endl;
    Area::areaofCaseInit(4,4);
    Area::homogeneousAreasInit();
    if(a_split_test->isHomogeneousArea() )
    {
      cout<<"it is an HomogeneousArea"<<endl;    
    }

    a_split_test->split2D(1);
    cout<<"end split"<<endl;
    
    cout<<"showing area of cases"<<endl;
    
    for (int i = 0 ; i < 4 ; i++)
    {
      for (int j = 0 ; j < 4 ; j++)
      {
        cout<<i<<" , "<<j<<endl;
        Area::areaofCase[i][j]->showArea2D();
      }
      cout<<endl;
    } 
    cout<<endl;
    cout<<"showing homogeneousAreas"<<endl;
    for(unsigned int i = 0 ; i< Area::homogeneousAreas->size() ; i++)
    {
      Area::homogeneousAreas->at(i)->showArea2D();
    }
  }

  else

  {
    printf("Usage: ImageIn.pgm ImageOut.pgm \n \t pour question1"); 
    printf("Usage:  pour question2 test");
    exit (1) ;

  }
  return 1;
}
