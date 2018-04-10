#include <stdio.h>
#include <iostream>
#include "includes/Area.h"

using namespace std;



int main(int argc, char* argv[])
{
  char cNomImgLue[250], cNomImgEcrite[250];
  int nH=0, nW=0, nTaille;

  if (argc != 3) 
  {
    printf("Usage: ImageIn.pgm ImageOut.pgm \n"); 
    exit (1) ;
  }

  sscanf (argv[1],"%s",cNomImgLue) ;
  sscanf (argv[2],"%s",cNomImgEcrite);
  //sscanf (argv[3],"%d",&S);

  OCTET *ImgIn, *ImgOut, * imgTest;

  lire_nb_lignes_colonnes_image_pgm(cNomImgLue, &nH, &nW);
  nTaille = nH * nW;

  allocation_tableau(ImgIn, OCTET, nTaille);
  lire_image_pgm(cNomImgLue, ImgIn, nH * nW);
  allocation_tableau(ImgOut, OCTET, nTaille);
  allocation_tableau(imgTest , OCTET , 16)  ;

  Area* a = new Area(ImgIn,nW,nH,0,0); // Total area image
  a->meanCompute();
  std::cout<<"Mean of the image : "<<a->getMean()<<std::endl;
  a->getTabSubArea(ImgOut); // Division in 4 mean corner : OK
  ecrire_image_pgm(cNomImgEcrite, ImgOut,  nH, nW);

  imgTest[0] =1 ; imgTest[1] =1 ; imgTest[2] =1 ; imgTest[3] =2 ;
  imgTest[4] =1 ; imgTest[5] =2 ; imgTest[6] =4 ; imgTest[7] =7 ;
  imgTest[8] =7 ; imgTest[9] =6 ; imgTest[10]=2 ; imgTest[11]=3 ; 
  imgTest[12]=4 ; imgTest[13]=5 ; imgTest[14]=6 ; imgTest[15]=1 ;
  Area* a_split_test = new Area(imgTest,4,4,0,0); // Total area image
  
  a_split_test->split();

  cout<<"end split"<<endl;
  free(ImgIn);
  
  return 1;
}
