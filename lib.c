#include "lib.h"

const int nb_lig_mask = 3;
const int nb_col_mask = 3;
const OCTET mask[nb_lig_mask][nb_col_mask] = {
	{(unsigned char)255, (unsigned char)255, (unsigned char)255},
	{(unsigned char)255, (unsigned char)255, (unsigned char)255},
	{(unsigned char)255, (unsigned char)255, (unsigned char)255}
};

// void creerMaskComplet(int mask[nb_lig_mask][nb_col_mask])
// {
// 	for (int i = 0 ; i < nb_lig_mask ; i ++ )
// 	{
// 		for (int j = 0 ; j < nb_col_mask ; j++)
// 		{
// 			mask[i][j] = 1;
// 		}
// 	}
// }

void conv1Dvers2D(OCTET * img1D , OCTET ** img2D , int n_lig_im1D, int n_col_im1D)
{
	int i2=0,j2=0;

	for(int i1 =0; i1 < n_lig_im1D * n_col_im1D; i1++)
	{
		if(i1 != 0 && i1 % n_col_im1D == 0)
		{
			i2++;
			j2=0;		
		}
		// printf("i2 = %u , j2 = %u \n" , i2 , j2);
		img2D[i2][j2] = img1D[i1];

		j2++;
	} 
}

void conv1Dvers3D_coul(OCTET * img1D , OCTET *** img3D , int n_lig_im1D, int n_col_im1D)
{
	int i2=0,j2=0;

	for(int i1 =0; i1 < n_lig_im1D * n_col_im1D * 3; i1+=3)
	{
		if(i1 != 0 && i1 % (n_col_im1D*3) == 0)
		{
			i2++;
			j2=0;		
		}
		// printf("i2 = %u , j2 = %u \n" , i2 , j2);
		img3D[i2][j2][0] = img1D[i1];
		img3D[i2][j2][1] = img1D[i1+1];
		img3D[i2][j2][2] = img1D[i1+2];

		j2++;
	} 
}

void conv2Dvers1D(OCTET * img1D , OCTET ** img2D , int n_lig_im1D, int n_col_im1D)
{
	int i2=0,j2=0;

	for(int i1 =0; i1 < n_lig_im1D * n_col_im1D; i1++)
	{
		if(i1 != 0 && i1 % n_lig_im1D == 0)
		{
			i2++;
			j2=0;		
		}
		img1D[i1]= img2D[i2][j2];

		j2++;
	}
}

void conv3Dvers1D_coul(OCTET * img1D , OCTET *** img3D , int nb_lig_im1D, int nb_col_im1D)
{
	int i1=0;

	for(int i= 0 ; i< nb_lig_im1D ; i++)
	{
		for (int j = 0; j < nb_col_im1D ; j++)
		{
			img1D[i1]   = img3D[i][j][0];
			img1D[i1+1] = img3D[i][j][1];
			img1D[i1+2] = img3D[i][j][2];
			// printf("\t(%i,%i,%i)\n" , img3D[i][j][0] , img3D[i][j][1] ,img3D[i][j][2]);
			// printf("img1D %i %i %i\n", img1D[i1] , img1D[i1+1] , img1D[i1+2]);
			i1+=3;
		}
	}
}

void erosion(OCTET ** ImgIn, OCTET ** ImgOut , int nb_lig_im , int nb_col_im)
{
	const int nb_lig_mask_div_2 = nb_lig_mask / 2;
	const int nb_col_mask_div_2 = nb_col_mask / 2; 
	OCTET fit;
	OCTET val_im_in_ij, val_mask_ij;

	for (int i_im_in = 0 ; i_im_in < nb_lig_im ; i_im_in ++)
	{
		for( int j_im_in =0 ; j_im_in < nb_col_im ; j_im_in ++)
		{		
			// printf("====> (i_im_in, j_im_in) = (%i,%i)\n",i_im_in,j_im_in);

			fit = (unsigned char)255;
			int i_im_in_comp,j_im_in_comp;
			for (int i_ma = 0 ; i_ma < nb_lig_mask; i_ma ++)
			{
				for (int j_ma = 0 ; j_ma < nb_col_mask ; j_ma ++)
				{
					val_im_in_ij = 1;
					

					i_im_in_comp = (i_im_in - nb_lig_mask_div_2 ) + i_ma;
					j_im_in_comp = (j_im_in - nb_col_mask_div_2 ) + j_ma;

					if(i_im_in_comp < 0 || i_im_in_comp >= nb_lig_im || j_im_in_comp < 0 || j_im_in_comp >= nb_col_im)
					{
						val_im_in_ij = 0;
					}

					if (val_im_in_ij != 0)
					{
						val_im_in_ij = ImgIn[i_im_in_comp][j_im_in_comp];
					}

					val_mask_ij = mask[i_ma][j_ma];
					// printf("	(i_comp,j_comp) = (%i , %i) mask = %i val_im =%i\n" , i_im_in_comp, j_im_in_comp , val_mask_ij , val_im_in_ij);

					if(val_mask_ij != val_im_in_ij)
					{
						fit = 0;
						break;
					}
				}
				if (fit == 0)
				{
					break;
				}	
			}

			// printf("\n");
			if (fit == 255)
			{
				// printf("fit!\n");
			}
			ImgOut[i_im_in][j_im_in] = fit;
			
		}
	}
}

void erosionGrey(OCTET ** ImgIn, OCTET ** ImgOut , int nb_lig_im , int nb_col_im)
{
	const int nb_lig_mask_div_2 = nb_lig_mask / 2;
	const int nb_col_mask_div_2 = nb_col_mask / 2; 
	OCTET max;
	OCTET val_im_in_ij, val_mask_ij;

	for (int i_im_in = 0 ; i_im_in < nb_lig_im ; i_im_in ++)
	{
		for( int j_im_in =0 ; j_im_in < nb_col_im ; j_im_in ++)
		{		
			// printf("====> (i_im_in, j_im_in) = (%i,%i)\n",i_im_in,j_im_in);

			max = (OCTET) 0;
			int i_im_in_comp,j_im_in_comp;
			for (int i_ma = 0 ; i_ma < nb_lig_mask; i_ma ++)
			{
				for (int j_ma = 0 ; j_ma < nb_col_mask ; j_ma ++)
				{
					val_im_in_ij = 1;
					

					i_im_in_comp = (i_im_in - nb_lig_mask_div_2 ) + i_ma;
					j_im_in_comp = (j_im_in - nb_col_mask_div_2 ) + j_ma;

					if(i_im_in_comp < 0 || i_im_in_comp >= nb_lig_im || j_im_in_comp < 0 || j_im_in_comp >= nb_col_im)
					{
						val_im_in_ij = 0;
					}

					if (val_im_in_ij != 0)
					{
						val_im_in_ij = ImgIn[i_im_in_comp][j_im_in_comp];
					}

					val_mask_ij = mask[i_ma][j_ma];
					// printf("	(i_comp,j_comp) = (%i , %i) mask = %i val_im =%i\n" , i_im_in_comp, j_im_in_comp , val_mask_ij , val_im_in_ij);
					
					if(val_mask_ij == 255 &&  val_im_in_ij > max )
					{
						
						max = val_im_in_ij;
						
					}
				}
					
			}

			ImgOut[i_im_in][j_im_in] = max;
			
		}
	}
}

void erosion_coul(OCTET *** ImgIn, OCTET *** ImgOut , int nb_lig_im , int nb_col_im)
{
	const int nb_lig_mask_div_2 = nb_lig_mask / 2;
	const int nb_col_mask_div_2 = nb_col_mask / 2; 
	OCTET max_R,max_G,max_B;
	OCTET val_im_in_ij,val_im_in_ij_R,val_im_in_ij_G,val_im_in_ij_B, val_mask_ij;

	for (int i_im_in = 0 ; i_im_in < nb_lig_im ; i_im_in ++)
	{
		for( int j_im_in =0 ; j_im_in < nb_col_im ; j_im_in ++)
		{		
			// printf("====> (i_im_in, j_im_in) = (%i,%i)\n",i_im_in,j_im_in);

			max_R = max_G = max_B = (OCTET) 0;
			int i_im_in_comp,j_im_in_comp;
			for (int i_ma = 0 ; i_ma < nb_lig_mask; i_ma ++)
			{
				for (int j_ma = 0 ; j_ma < nb_col_mask ; j_ma ++)
				{
					val_im_in_ij = 1;
					

					i_im_in_comp = (i_im_in - nb_lig_mask_div_2 ) + i_ma;
					j_im_in_comp = (j_im_in - nb_col_mask_div_2 ) + j_ma;

					if(i_im_in_comp < 0 || i_im_in_comp >= nb_lig_im || j_im_in_comp < 0 || j_im_in_comp >= nb_col_im)
					{
						val_im_in_ij = 0;
						val_im_in_ij_R = 0;
						val_im_in_ij_G = 0;
						val_im_in_ij_B = 0;
					}

					if (val_im_in_ij != 0)
					{
						val_im_in_ij_R = ImgIn[i_im_in_comp][j_im_in_comp][0];
						val_im_in_ij_G = ImgIn[i_im_in_comp][j_im_in_comp][1];
						val_im_in_ij_B = ImgIn[i_im_in_comp][j_im_in_comp][2];

					}

					val_mask_ij = mask[i_ma][j_ma];
					// printf("	(i_comp,j_comp) = (%i , %i) mask = %i val_im =%i\n" , i_im_in_comp, j_im_in_comp , val_mask_ij , val_im_in_ij);
					
					if(val_mask_ij == 255 &&  val_im_in_ij_R > max_R )
					{
						
						max_R = val_im_in_ij_R;
						
					}

					if(val_mask_ij == 255 &&  val_im_in_ij_G> max_G)
					{
						
						max_G= val_im_in_ij_G;
						
					}

					if(val_mask_ij == 255 &&  val_im_in_ij_B> max_B)
					{
						
						max_B= val_im_in_ij_B;
						
					}
					
				}
					
			}

			ImgOut[i_im_in][j_im_in][0] = max_R;
			ImgOut[i_im_in][j_im_in][1] = max_G;
			ImgOut[i_im_in][j_im_in][2] = max_B;
			
		}
	}
}



void dilatation_coul(OCTET *** ImgIn, OCTET *** ImgOut , int nb_lig_im , int nb_col_im)
{
	const int nb_lig_mask_div_2 = nb_lig_mask / 2;
	const int nb_col_mask_div_2 = nb_col_mask / 2; 
	OCTET min_R,min_G,min_B;
	OCTET val_im_in_ij,val_im_in_ij_R,val_im_in_ij_G,val_im_in_ij_B, val_mask_ij;

	for (int i_im_in = 0 ; i_im_in < nb_lig_im ; i_im_in ++)
	{
		for( int j_im_in =0 ; j_im_in < nb_col_im ; j_im_in ++)
		{		
			// printf("====> (i_im_in, j_im_in) = (%i,%i)\n",i_im_in,j_im_in);

			min_R = min_G = min_B = (OCTET) 255;
			int i_im_in_comp,j_im_in_comp;
			for (int i_ma = 0 ; i_ma < nb_lig_mask; i_ma ++)
			{
				for (int j_ma = 0 ; j_ma < nb_col_mask ; j_ma ++)
				{
					val_im_in_ij = 1;
					

					i_im_in_comp = (i_im_in - nb_lig_mask_div_2 ) + i_ma;
					j_im_in_comp = (j_im_in - nb_col_mask_div_2 ) + j_ma;

					if(i_im_in_comp < 0 || i_im_in_comp >= nb_lig_im || j_im_in_comp < 0 || j_im_in_comp >= nb_col_im)
					{
						val_im_in_ij = 0;
						val_im_in_ij_R = 0;
						val_im_in_ij_G = 0;
						val_im_in_ij_B = 0;
					}

					if (val_im_in_ij != 0)
					{
						val_im_in_ij_R = ImgIn[i_im_in_comp][j_im_in_comp][0];
						val_im_in_ij_G = ImgIn[i_im_in_comp][j_im_in_comp][1];
						val_im_in_ij_B = ImgIn[i_im_in_comp][j_im_in_comp][2];

					}

					val_mask_ij = mask[i_ma][j_ma];
					// printf("	(i_comp,j_comp) = (%i , %i) mask = %i val_im =%i\n" , i_im_in_comp, j_im_in_comp , val_mask_ij , val_im_in_ij);
					
					if(val_mask_ij == 255 &&  val_im_in_ij_R < min_R )
					{
						
						min_R = val_im_in_ij_R;
						
					}

					if(val_mask_ij == 255 &&  val_im_in_ij_G < min_G)
					{
						
						min_G= val_im_in_ij_G;
						
					}

					if(val_mask_ij == 255 &&  val_im_in_ij_B < min_B)
					{
						
						min_B= val_im_in_ij_B;
						
					}
					
				}
					
			}

			ImgOut[i_im_in][j_im_in][0] = min_R;
			ImgOut[i_im_in][j_im_in][1] = min_G;
			ImgOut[i_im_in][j_im_in][2] = min_B;
			
		}
	}
}

void dilatationGrey(OCTET ** ImgIn, OCTET ** ImgOut , int nb_lig_im , int nb_col_im)
{
	const int nb_lig_mask_div_2 = nb_lig_mask / 2;
	const int nb_col_mask_div_2 = nb_col_mask / 2; 
	OCTET min;
	OCTET val_im_in_ij, val_mask_ij;

	for (int i_im_in = 0 ; i_im_in < nb_lig_im ; i_im_in ++)
	{
		for( int j_im_in =0 ; j_im_in < nb_col_im ; j_im_in ++)
		{		
			// printf("====> (i_im_in, j_im_in) = (%i,%i)\n",i_im_in,j_im_in);

			min = (OCTET) 255;
			int i_im_in_comp,j_im_in_comp;
			for (int i_ma = 0 ; i_ma < nb_lig_mask; i_ma ++)
			{
				for (int j_ma = 0 ; j_ma < nb_col_mask ; j_ma ++)
				{
					val_im_in_ij = 1;
					

					i_im_in_comp = (i_im_in - nb_lig_mask_div_2 ) + i_ma;
					j_im_in_comp = (j_im_in - nb_col_mask_div_2 ) + j_ma;

					if(i_im_in_comp < 0 || i_im_in_comp >= nb_lig_im || j_im_in_comp < 0 || j_im_in_comp >= nb_col_im)
					{
						val_im_in_ij = 0;
					}

					if (val_im_in_ij != 0)
					{
						val_im_in_ij = ImgIn[i_im_in_comp][j_im_in_comp];
					}

					val_mask_ij = mask[i_ma][j_ma];
					// printf("	(i_comp,j_comp) = (%i , %i) mask = %i val_im =%i\n" , i_im_in_comp, j_im_in_comp , val_mask_ij , val_im_in_ij);
					
					if(val_mask_ij == 255 &&  val_im_in_ij < min )
					{
						
						min = val_im_in_ij;
						
					}
				}
					
			}

			ImgOut[i_im_in][j_im_in] = min;
			
		}
	}
}

void dilatation(OCTET ** ImgIn, OCTET ** ImgOut , int nb_lig_im , int nb_col_im )
{
	const int nb_lig_mask_div_2 = nb_lig_mask / 2;
	const int nb_col_mask_div_2 = nb_col_mask / 2; 
	OCTET hit;
	OCTET val_im_in_ij, val_mask_ij;
	for (int i_im_in = 0 ; i_im_in < nb_lig_im ; i_im_in ++)
	{
		for( int j_im_in =0 ; j_im_in < nb_col_im ; j_im_in ++)
		{		
			hit = 0;
			int i_im_in_comp,j_im_in_comp;
			for (int i_ma = 0 ; i_ma < nb_lig_mask; i_ma ++)
			{
				for (int j_ma = 0 ; j_ma < nb_col_mask ; j_ma ++)
				{
					val_im_in_ij = 1;
					

					i_im_in_comp = (i_im_in - nb_lig_mask_div_2 ) + i_ma;
					j_im_in_comp = (j_im_in - nb_col_mask_div_2 ) + j_ma;

					if(i_im_in_comp < 0 || i_im_in_comp >= nb_lig_im || j_im_in_comp < 0 || j_im_in_comp >= nb_col_im)
					{
						val_im_in_ij = 0;
					}

					if (val_im_in_ij != 0)
					{
						val_im_in_ij = ImgIn[i_im_in_comp][j_im_in_comp];
					}
					val_mask_ij = mask[i_ma][j_ma];

					if(val_mask_ij == 255 && val_im_in_ij == 255)
					{
						hit = 255;
						break;
					}

				}
				if (hit == 255)
					break;
			}
			ImgOut[i_im_in][j_im_in] = hit;
		}
	}
}

void diference(OCTET ** ImgIn, OCTET** ImgInDil , OCTET ** ImgOut , int nb_lig_im , int nb_col_im )
{
	for (int i = 0 ; i < nb_lig_im ; i++)
	{
		for (int j= 0 ; j < nb_lig_im ; j++)
		{
			if (ImgIn[i][j]==255 && ImgInDil[i][j]==255)
			{
				ImgOut[i][j]=255;
			}
			else if(ImgIn[i][j]==0 && ImgInDil[i][j]==0)
			{
				ImgOut[i][j]=255;
			}
			else if (ImgIn[i][j]==256 && ImgInDil[i][j]==0)
			{
				ImgOut[i][j]=0;
			}
		}
	}
}

OCTET ** allocation_tableau2D( int nb_lig_im , int nb_col_im)
{
	OCTET ** img2D = (OCTET **) malloc(nb_lig_im * sizeof(OCTET *));
	
	for (int i = 0; i< nb_lig_im ; i++)
	{
		img2D[i] = (OCTET *) malloc (nb_col_im * sizeof(OCTET));
	}

	img2D[0][0] = 0;
	for(int i = 0 ; i < nb_lig_im ; i++)
	{
		for (int j = 0 ; j < nb_col_im ; j++)
		{
			img2D[i][j]= 1;
		}
	}
	
	return img2D;
}
	

OCTET *** allocation_tableau3D( int nb_lig_im , int nb_col_im)
{
	OCTET *** img3D = (OCTET ***) malloc(nb_lig_im * sizeof(OCTET **));
	
	for (int i = 0; i< nb_lig_im ; i++)
	{
		img3D[i] = (OCTET **) malloc (nb_col_im * sizeof(OCTET*));

		for (int j = 0 ; j < nb_col_im ; j++)
		{
			img3D[i][j] = (OCTET *) malloc( 3 * sizeof(OCTET));

		}
	}

	
	
	return img3D;
}

void hist(OCTET *imgIn , unsigned int * tab_hist ,int nb_lig_im, int nb_col_im)
{
	for (int i= 0 ; i< 256 ; i++)
	{
		tab_hist[i]=0;
	}
	int nTaille = nb_lig_im * nb_col_im;
	for (int i = 0 ; i< nTaille ; i++)
	{
		tab_hist[imgIn[i]]++;
	}
}
/*TP3 egalisation*/

void hist_cumule(OCTET *imgIn,unsigned int *tab_hist , unsigned long long  *tab_hist_cumule,int nb_lig_im, int nb_col_im)
{

	tab_hist_cumule[0] = tab_hist[0];

	for (int i= 1 ; i< 256 ; i++)
	{
		tab_hist_cumule[i]=tab_hist_cumule[i-1] + tab_hist[i];
	}
} 

void egalisation_im (OCTET *imgIn , OCTET *imgEg , long long unsigned int* tab_hist_cumule , int nb_lig_im, int nb_col_im)
{
	int nTaille = nb_lig_im * nb_col_im;
	for(int i = 0 ; i < nTaille ; i++)
	{
		imgEg[i]=(255.0 / nTaille) * tab_hist_cumule[imgIn[i]];
	}
}

void egalisation(OCTET *imgIn , unsigned int * tab_egalisation , long long unsigned int *tab_hist_cumule , int nb_lig_im , int nb_col_im )
{
	int nTaille = nb_lig_im * nb_col_im;
	for(int i = 0 ; i < 256 ; i++)
	{
		tab_egalisation[i]=round((255.0 / nTaille) * tab_hist_cumule[i]);
		
		
	}
}


void specification(OCTET* imgIn , OCTET* imgSpec ,OCTET* imgOut , int nb_lig_im , int nb_col_im , struct  spec_elems* se)
{
	hist(imgIn , se->tab_hist_im_in , nb_lig_im , nb_col_im);
	hist(imgSpec , se->tab_hist_im_spec,  nb_lig_im , nb_col_im);

	hist_cumule(imgIn , se->tab_hist_im_in , se->tab_hist_cumule_im_in , nb_lig_im , nb_col_im);
	hist_cumule(imgSpec , se->tab_hist_im_spec ,se->tab_hist_cumule_im_spec , nb_lig_im , nb_col_im);

	egalisation(imgIn , se->tab_egalisation_im_in , se->tab_hist_cumule_im_in , nb_lig_im , nb_col_im);
	egalisation(imgSpec , se->tab_egalisation_im_spec , se->tab_hist_cumule_im_spec , nb_lig_im , nb_col_im);

	printf ("val \"hist Image Input\" \"hist Image Spec\" \"hist Cumule Input\" \"hist Cumule Spec\" \"eg In\" \"eg Spec\"\n ");
	for( int i= 0 ; i < 256 ; i++)
	{
		printf("%i %i %i %llu %llu %u %i\n",i ,se->tab_hist_im_in[i],se->tab_hist_im_spec[i],se->tab_hist_cumule_im_in[i],se->tab_hist_cumule_im_spec[i],se->tab_egalisation_im_in[i],se->tab_egalisation_im_spec[i] );
	}
	unsigned int e_in , e_spec;
	unsigned int k=0,i=0;
	
	// for (int i = 0 ; i < 256 ; i ++)
	// {
	// 	se->map[i]=i;
		
	// }
	
	while(k < 256)
	{	
		e_in   = se->tab_egalisation_im_in[k];
		e_spec = se->tab_egalisation_im_spec[i];
		printf("e_in = %u , e_spec = %u" , e_in , e_spec);
		
		if(e_in < e_spec)
		{
			if (i > 0 && abs(e_in - e_spec) <= abs(e_in - se->tab_egalisation_im_spec[i - 1 ]))
			{
				se->map[e_in]=e_spec; printf(" match");
			}
			else if (i > 0)
			{
				se->map[e_in]=se->tab_egalisation_im_spec[i-1]; printf(" match -1 ");
			}
			else //i == 0
			{
				se->map[e_in]=e_spec; printf(" match");
			}
			k++;
			i=0;
		}
		else if (i == 255)
		{
			se->map[e_in]=e_spec;
			k++;
			i=0;

		}
		else
		{
			i++;
		}

		// printf("\n");

	}
	int j;
	OCTET sup,inf;
	

	for (int i = 0 ; i < 256 ; i++)
	{
		j=i , sup = 0 , inf =0;
		if(se->map[i]==0)
		{
			if(i > 0)
				inf = se->map[i-1];
			
			while(j < 256 && se->map[j]==0)
			{
				j++;
			}
			sup= se->map[j];

			se->map[i]= (inf + sup) / 2;
		}
	}

	for (int i = 0 ; i < 256 ; i++)
	{
		printf("#map_%i = %i\n", i ,se->map[i]);
	}
	for (int i = 0 ; i < nb_lig_im * nb_col_im ; i++)
	{
		imgOut[i]= se->map[imgIn[i]];
	}
}



void floutage_coul(OCTET *** ImgIn, OCTET *** ImgOut , int nb_lig_im , int nb_col_im , int voisinage)
{
	double moyR,moyG,moyB;
	unsigned int denom;
	
	for(int i = 0 ; i < nb_lig_im ; i ++)
	{
		for(int j = 0 ; j < nb_col_im ; j++)
		{
			// printf("====> (i_im_in, j_im_in) = (%i,%i)\n",i,j);

			moyR = moyG = moyB = 0;
			denom=0;
			
			for(int i_vois  = i - ((int) voisinage / 2) ; i_vois < i - ((int) voisinage / 2) + voisinage; i_vois++)
			{
				for( int j_vois = j - ((int) voisinage / 2) ; j_vois < j - ((int) voisinage/2) + voisinage; j_vois++)
				{
					// printf("\t(i_vois , j_vois) = (%i , %i)\n" ,i_vois,j_vois);
					
					if(i_vois >= 0 && i_vois < nb_lig_im 
					&& j_vois >= 0 && j_vois < nb_col_im)
					{
						// printf("\tIn\n");
						moyR += ImgIn[i_vois][j_vois][0];
						moyG += ImgIn[i_vois][j_vois][1];
						moyB += ImgIn[i_vois][j_vois][2];
						denom++;
					}

				}
			}
			// printf("denom %i\n=" , denom );
			// printf( " moyR = %lf , " , round(moyR/denom) );
			// printf( " moyG = %lf"    , round(moyG/denom) );
			// printf( " moyB = %lf\n"  , round(moyB/denom) );
			

			ImgOut[i][j][0] = (int)round(moyR / denom);
			ImgOut[i][j][1] = (int)round(moyG / denom);
			ImgOut[i][j][2] = (int)round(moyB / denom);
			
		
			// printf("\n");
		}
	}
}



void floutage_coul(OCTET *** ImgIn, OCTET* ImgBin, OCTET *** ImgOut , int nb_lig_im , int nb_col_im , int voisinage)
{
	double moyR,moyG,moyB;
	unsigned int denom;
	
	for(int i = 0 ; i < nb_lig_im ; i ++)
	{
		for(int j = 0 ; j < nb_col_im ; j++)
		{
			// printf("====> (i_im_in, j_im_in) = (%i,%i)\n",i,j);

			moyR = moyG = moyB = 0;
			denom=0;
			
			if(ImgBin[(nb_col_im * i) + j] == 0)
			{
				for(int i_vois  = i - ((int) voisinage / 2) ; i_vois < i - ((int) voisinage / 2) + voisinage; i_vois++)
				{
					for( int j_vois = j - ((int) voisinage / 2) ; j_vois < j - ((int) voisinage/2) + voisinage; j_vois++)
					{
						// printf("\t(i_vois , j_vois) = (%i , %i)\n" ,i_vois,j_vois);
						
						if(i_vois >= 0 && i_vois < nb_lig_im 
						&& j_vois >= 0 && j_vois < nb_col_im)
						{
							// printf("\tIn\n");
							moyR += ImgIn[i_vois][j_vois][0];
							moyG += ImgIn[i_vois][j_vois][1];
							moyB += ImgIn[i_vois][j_vois][2];
							denom++;
						}

					}
				}
				// printf("denom %i\n=" , denom );
				// printf( " moyR = %lf , " , round(moyR/denom) );
				// printf( " moyG = %lf"    , round(moyG/denom) );
				// printf( " moyB = %lf\n"  , round(moyB/denom) );
				

				ImgOut[i][j][0] = (int)round(moyR / denom);
				ImgOut[i][j][1] = (int)round(moyG / denom);
				ImgOut[i][j][2] = (int)round(moyB / denom);
				 
			}
			else
			{
				ImgOut[i][j][0]=ImgIn[i][j][0];
				ImgOut[i][j][1]=ImgIn[i][j][1];
				ImgOut[i][j][2]=ImgIn[i][j][2];
			}
		
			// printf("\n");
		}
	}
}

unsigned short int _bswap16(unsigned short int a)
{
  a = ((a & 0x00FF) << 8) | ((a & 0xFF00) >> 8);
  return a;
}
