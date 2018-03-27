#include <stdio.h>
#include "includes/Area.h"


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

  OCTET *ImgIn, *ImgOut;

  lire_nb_lignes_colonnes_image_pgm(cNomImgLue, &nH, &nW);
  nTaille = nH * nW;

  allocation_tableau(ImgIn, OCTET, nTaille);
  lire_image_pgm(cNomImgLue, ImgIn, nH * nW);
  allocation_tableau(ImgOut, OCTET, nTaille);


  Area* a = new Area(ImgIn,nW,nH,0,0);

  a->meanCompute();
  std::cout<<"Mean of the area : "<<a->getMean();
  a->getTabSubArea(ImgOut);

  // division quart image

/*  OCTET* temp;
  allocation_tableau(temp, OCTET, nTaille/4);
  for(int i=0; i<nW/2; i++)
  {
    for(int j = 0; j<nH/2; j++)
    {
      temp [i+j*(nW/2)] = ImgIn[i+(nW/2)+(j+(nH/2))*nW];
    }
  }
  ecrire_image_pgm(cNomImgEcrite, temp,  nH/2, nW/2);
  free(temp);*/

  ecrire_image_pgm(cNomImgEcrite, ImgOut,  nH, nW);

  a->~Area();
  free(ImgIn);
  
  return 1;
}
