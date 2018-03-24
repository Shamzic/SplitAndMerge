#include <stdio.h>
#include "includes/Area.h"
#include "includes/image_ppm.h"

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
  std::cout<<"nW = "<<nW<<std::endl;
  std::cout<<"nH = "<<nH<<std::endl;

  Area* a = new Area(ImgIn,nW,nH,0,0);
  a->display();

  a->meanCompute();
  std::cout<<"Mean of the area : "<<a->getMean();
  ecrire_image_pgm(cNomImgEcrite, ImgOut,  nH, nW);
  free(ImgIn);
  
  return 1;
}
