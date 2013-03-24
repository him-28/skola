#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>
#include "string.h"

/*velikost generovaného obrázku */
#define PICTURE_SIZE 100

/*jakým znakem budou reprezentovány obrazce (ASCII hodnota) (120 == 'x')*/
#define PSYMBOL 120

/*jakým znakem bude reprezentováno pozadí*/
#define PBACKGROUND 45

#define MAX_OBJECTS 100



/* generovani nahodnych cisel, jako seed pro funkci (srand) je použit systémový čas */
int random_number ( int from, int to )
	{
	struct timeval time;
	gettimeofday(&time, NULL);

	srand(time.tv_usec*time.tv_sec);
	return (from + rand()%(to - from + 1));
	}

/*sečte hodnoty všech buňek v poli */
int count_pixels(unsigned char cpicture[PICTURE_SIZE][PICTURE_SIZE])
	{
	int i, j, pcount=0;
	for (i=0; i<PICTURE_SIZE; i++)
		{
		for (j=0; j<PICTURE_SIZE; j++)
			{
			pcount += cpicture[i][j];
			}
		}
	return pcount;
	}


/*kreslí otočený čtverec: zadáme obrázek polohu středu a polovinu uhlopricky, funkce nastaví odpovídající
  buňky v poli na hodnotu kterou taktéž zadáme ve funkci */
void draw_rotated_square (unsigned char picture[PICTURE_SIZE][PICTURE_SIZE], int r , 
						 int top_line, int top_column, int letter)
	{
	
	//printf("otočený čtverec: x:%i y:%i r:%i \n",top_line, top_column, r);

	int i,j;
	for (i=0; i<= 2*r ; i++)
		{
		for (j=(-r); j<=r; j++)
			{
			int distance;
			
			distance = ( abs(r-i) + abs(j) );
			if(distance <= r)
				picture[top_line+i][top_column+j]=letter;
			}
		}
	}


void draw_rectangle (unsigned char picture[PICTURE_SIZE][PICTURE_SIZE], unsigned height,
						 	unsigned width, unsigned corner_line, unsigned corner_column, unsigned letter)
	{
	unsigned i;
	for (i=0; i<height; i++)
		{
		unsigned j;
		for (j=0; j<width; j++)
			{
			picture[corner_line+i][corner_column+j]=letter;
			}
		}
	}

char compare (unsigned char cpicture[PICTURE_SIZE][PICTURE_SIZE], unsigned char picture[PICTURE_SIZE][PICTURE_SIZE])
	{
	unsigned i;
	for (i=0; i<PICTURE_SIZE; i++)
		{
		unsigned j;
		for (j=0; j<PICTURE_SIZE; j++)
			{
			if (cpicture[i][j]==2)
				{
				if (picture[i][j]==0)
					return 0;
				}
			}
		}
	return 1;
	}

/*prvnímu přiřadí hodnotu druhého*/
void sync_pictures(unsigned char picture1[PICTURE_SIZE][PICTURE_SIZE], unsigned char picture2[PICTURE_SIZE][PICTURE_SIZE] )
	{
	int i,j;
	for (i=0; i<PICTURE_SIZE; i++)
		{
		for (j=0; j<PICTURE_SIZE; j++)
			{
			picture1[i][j]=picture2[i][j];
			}
		}
	}

void save_object( int objects[MAX_OBJECTS][5], int type, int corner_line, int corner_column, int height, int width)
	{
	/*najdeme první prázdný řádek, případně přepíšeme řádek na kterém je zapsán obrazec se stejnou pozicí*/
	int i;
	for (i=0; i<MAX_OBJECTS; i++)
		{
		if ( objects[i][1]==corner_line && objects[i][2]==corner_column){break;}
		if ( objects[i][0]!=1 && objects[i][0]!=2){break;}
		}
	objects[i][0]=type;
	objects[i][1]=corner_line;
	objects[i][2]=corner_column;
	objects[i][3]=height;
	objects[i][4]=width;	
	//printf("save object: uloženo na pozici i:%i, typ:%i , řádek:%i, sloupec:%i, výška:%i, šířka:%i \n",
	//			 i, type , corner_line, corner_column, height, width );
	}


void draw_last_object (unsigned char cpicture[PICTURE_SIZE][PICTURE_SIZE], int objects[MAX_OBJECTS][5], int letter)
	{
	int i;
	for (i=0; i<MAX_OBJECTS; i++)
		{
		if ( objects[i][0]!=1 && objects[i][0]!=2) break;	
		}
	if(objects[i-1][0]==1)
		{
		draw_rotated_square(cpicture, objects[i-1][3], objects[i-1][1], objects[i-1][2], letter);
		//printf("draw_last_object: kreslím kosočtverec\n");
		}
	else
		{
		draw_rectangle(cpicture, objects[i-1][3], objects[i-1][4], objects[i-1][1], objects[i-1][2], letter);
		//printf("draw_last_object: kreslím obdélník, výška:%i, šířka:%i, řádek:%i, sloupec:%i, znak:%i\n", 
		//			objects[i-1][3], objects[i-1][4], objects[i-1][1], objects[i-1][2], letter);		
		}
	}

void display_objects (int objects[MAX_OBJECTS][5], unsigned *nmrhombus, unsigned *nmsquare, unsigned *nmrectangle)
	{
	int i;
	for (i=0; i<MAX_OBJECTS; i++)
		{
		if ( objects[i][0]==1)
			{
			printf("Nalezen otočený čtverec: řádek:%i, sloupec:%i, úhlopříčka:%i, objem:%.0f\n", objects[i][1], objects[i][2], 2*objects[i][3]+1, (float)(2*objects[i][3]+1)*(float)(2*objects[i][3]+1)*0.5 + 0.5 );
			*nmrhombus += 1;
			}
	else if (objects[i][0]==2)
			{
			if(objects[i][3]==objects[i][4])
				{
				printf("Nalezen čtverec: řádek:%i, sloupec:%i, velikost:%i, objem:%i \n", objects[i][1], objects[i][2], objects[i][3], objects[i][3]*objects[i][3]);
				*nmsquare += 1;
				}
			else
				{
				printf("Nalezen obdélník: řádek:%i, sloupec:%i, výška:%i, šířka:%i, objem:%i \n", 
							objects[i][1], objects[i][2], objects[i][3], objects[i][4], objects[i][3]*objects[i][4]);
				*nmrectangle += 1;
				}
			}	
		}
	}

