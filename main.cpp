#include <stdio.h>
#include <iostream>
#include "includes/Area.h"

using namespace std;



int main(int argc, char* argv[])
{
  char cNomImgLue[250], cNomImgEcrite[250];
  int nH=0, nW=0, nTaille;

/*  if (argc == 3) 
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
*/
  

  // for(int i = O; i < this->h; i++)
  // {
    
  // }
/*  else*/ 
  if(argc == 3)
  {

    sscanf (argv[1],"%s",cNomImgLue) ;
    sscanf (argv[2],"%s",cNomImgEcrite);
    OCTET *ImgIn, *ImgOut; 
    lire_nb_lignes_colonnes_image_pgm(cNomImgLue, &nH, &nW);
    nTaille = nH * nW;
    cout<<"Taille = "<<nH<<"*"<<nW<<endl;
    allocation_tableau(ImgIn, OCTET, nTaille);
    lire_image_pgm(cNomImgLue, ImgIn, nH * nW);
    allocation_tableau(ImgOut, OCTET, nTaille);

    Area* a_split_test_2 = new Area(ImgIn,nW,nH,0,0); // Total area image
    
    // a_split_test_2->showArea();
    a_split_test_2->conv1Dvers2D();
    // a_split_test_2->showArea2D();

    a_split_test_2->meanCompute2D();
    //cout<<(float)a_split_test_2->getMean();
    a_split_test_2->varianceCompute2D();
    
    cout<<" "<<(float)a_split_test_2->getVariance();
    a_split_test_2->standardDeviationCompute();
/*    cout<<" "<<(float)a_split_test_2->getStandardDeviation();
    cout<<endl;*/
    Area::areaofCaseInit(nW,nH);
    Area::homogeneousAreasInit();
    a_split_test_2->split2D(22);

    for(unsigned int k = 0 ; k < Area::homogeneousAreas->size();  k++) 
    {
      //cout<<"Airehomogene "<<k<<endl;
      int x = Area::homogeneousAreas->at(k)->getI(); // coordonées du coin haut gauche
      int y = Area::homogeneousAreas->at(k)->getJ(); // de l'aire homogène en cours de traitement

      int w =  Area::homogeneousAreas->at(k)->getW();
      int h =  Area::homogeneousAreas->at(k)->getH();

      for(int i = x; i< x+h; i++)
      {
        for(int j = y; j<y+w; j++)
        {
          ImgOut[j*nW+i] = Area::homogeneousAreas->at(k)->getMean();
         // cout<<"i : "<<i<<" j : "<<j<<endl;
        }
      }
     
    }
    ecrire_image_pgm(cNomImgEcrite, ImgOut,  nH, nW);
    free(ImgIn);
  }

    // if(a_split_test_2->isHomogeneousArea() )
    // {
    //   cout<<"it is an HomogeneousArea"<<endl;    
    // }

    // a_split_test->split2D(1);
    // cout<<"end split"<<endl;
    
    // cout<<"showing area of cases"<<endl;
    
    // for (int i = 0 ; i < 4 ; i++)
    // {
    //   for (int j = 0 ; j < 4 ; j++)
    //   {
    //     cout<<i<<" , "<<j<<endl;
    //     Area::areaofCase[i][j]->showArea2D();
    //   }
    //   cout<<endl;
    // } 
    // cout<<endl;
    // cout<<"showing homogeneousAreas"<<endl;
    // for(unsigned int i = 0 ; i< Area::homogeneousAreas->size() ; i++)
    // {
    //   Area::homogeneousAreas->at(i)->showArea2D();





  else if(argc == 1)
  {
    char cNomImgTest[250] , cNomImgEcrite[250] ;

    strcpy(cNomImgTest , "imgTest.pgm\0");
    strcpy(cNomImgEcrite , "imgTestOut.pgm\0");
    OCTET *imgTest, *imgOut;
    allocation_tableau(imgTest , OCTET , 16) ;
    allocation_tableau(imgOut, OCTET, 16);
    imgTest[0] =1 +200 ; imgTest[1] =1 +20 ; imgTest[2] =3 +100 ; imgTest[3] =2 +100 ;
    imgTest[4] =1 +200 ; imgTest[5] =2 +200 ; imgTest[6] =4 +50 ; imgTest[7] =7 +200 ;
    imgTest[8] =7 +2 ; imgTest[9] =6 +80 ; imgTest[10]=2 +156 ; imgTest[11]=3 +200 ; 
    imgTest[12]=4 +190 ; imgTest[13]=5 +60 ; imgTest[14]=6 +60 ; imgTest[15]=1 +60 ;
    
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

    a_split_test->split2D(4000);
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



    for(unsigned int k = Area::homogeneousAreas->size()-1; k>0 ; k--) 
    {

      cout<<"Airehomogene "<<k<<endl;
      int x = Area::homogeneousAreas->at(k)->getI(); // coordonées du coin haut gauche
      int y = Area::homogeneousAreas->at(k)->getJ(); // de l'aire homogène en cours de traitement

      int w =  Area::homogeneousAreas->at(k)->getW();
      int h =  Area::homogeneousAreas->at(k)->getH();

      for(int i = y; i< y+h; i++)
      {
        for(int j = x; j<x+w; j++)
        {
          imgOut[i*4+j] = Area::homogeneousAreas->at(k)->getMean();
         // cout<<"i : "<<i<<" j : "<<j<<endl;
        }
      }
    }

    ecrire_image_pgm(cNomImgTest , imgTest, 4 , 4);
    ecrire_image_pgm(cNomImgEcrite, imgOut,  4, 4);

  }
  

  else

  {
    printf("Usage: ImageIn.pgm ImageOut.pgm \n \t pour question1"); 
    printf("Usage:  pour question2 test");
    exit (1) ;

  }
  return 1;
}
