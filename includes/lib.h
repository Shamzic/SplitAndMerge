
#ifndef LIB_H
#define LIB_H
#include "image_ppm.h"
#include <stdio.h>

struct spec_elems{
	unsigned int * tab_hist_im_in;
	unsigned int * tab_hist_im_spec;
	
	unsigned long long int* tab_hist_cumule_im_in ;
	unsigned long long int* tab_hist_cumule_im_spec;
	
	unsigned int * tab_egalisation_im_in;
	unsigned int * tab_egalisation_im_spec;

	unsigned int *map;
};

void conv1Dvers2D(OCTET * img1D , OCTET ** img2D , int n_lig_im1D, int n_col_im1D);
void conv2Dvers1D(OCTET * img1D , OCTET ** img2D , int n_lig_im1D, int n_col_im1D);
void erosion(OCTET ** ImgIn, OCTET ** ImgOut , int nb_lig_im , int nb_col_im);
void dilatation(OCTET ** ImgIn, OCTET ** ImgOut , int nb_lig_im , int nb_col_im );
OCTET **  allocation_tableau2D( int nb_lig_im , int nb_col_im);
void diference(OCTET ** ImgIn, OCTET** ImgInDil , OCTET ** ImgOut , int nb_lig_im , int nb_col_im );
void erosionGrey(OCTET ** ImgIn, OCTET ** ImgOut , int nb_lig_im , int nb_col_im);
void dilatationGrey(OCTET ** ImgIn, OCTET ** ImgOut , int nb_lig_im , int nb_col_im);
OCTET *** allocation_tableau3D( int nb_lig_im , int nb_col_im);
void conv1Dvers3D_coul(OCTET * img1D , OCTET *** img3D , int n_lig_im1D, int n_col_im1D);
void conv3Dvers1D_coul(OCTET * img1D , OCTET *** img3D , int n_lig_im1D, int n_col_im1D);
void erosion_coul(OCTET *** ImgIn, OCTET *** ImgOut , int nb_lig_im , int nb_col_im);
void dilatation_coul(OCTET *** ImgIn, OCTET *** ImgOut , int nb_lig_im , int nb_col_im);

void hist(OCTET *imgIn , unsigned int * tab_hist ,int nb_lig_im, int nb_col_im);
void hist_cumule(OCTET *imgIn,unsigned int *tab_hist , unsigned long long  *tab_hist_cumule,int nb_lig_im, int nb_col_im);
void egalisation_im (OCTET *imgIn , OCTET *imgEg , long long unsigned int *tab_hist_cumule , int nb_lig_im, int nb_col_im);
void specification(OCTET* imgIn , OCTET* imgSpec ,OCTET* imgOut , int nb_lig_im , int nb_col_im , struct spec_elems* se);

void floutage_coul(OCTET *** ImgIn, OCTET *** ImgOut , int nb_lig_im , int nb_col_im , int voisinage);
void floutage_coul(OCTET *** ImgIn, OCTET* ImgBin, OCTET *** ImgOut , int nb_lig_im , int nb_col_im , int voisinage);

unsigned short int _bswap16(unsigned short int a);
#endif