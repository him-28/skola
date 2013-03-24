/* Generování ASCII obrázku s kruhy, čtverci a obdélníky */

#include "util.c"

#define MIN_RSQ 1
#define MAX_RSQ 4
#define MIN_SQUARE 1
#define MAX_SQUARE 4
#define MIN_RECT 1
#define MAX_RECT 4

int main()
{
unsigned char picture[PICTURE_SIZE][PICTURE_SIZE];

unsigned i,j;

/* inicializuj picture (vypíše PBACKGROUND do celého picture) */
//draw_rectangle(picture, PICTURE_SIZE, PICTURE_SIZE, 0, 0, PBACKGROUND);

/*tohle by možná bylo rychlejší*/
memset(&picture, PBACKGROUND, sizeof(unsigned char)*PICTURE_SIZE*PICTURE_SIZE );

/*kresli kosočtverce */
j= random_number(MIN_RSQ, MAX_RSQ);
//printf("počet kosočtverců: %i \n",j);

for (i=0; i<j; i++)
	{
	int r=random_number(1,5);
	draw_rotated_square( picture, 
					  random_number(1,5), 
					  random_number(1, PICTURE_SIZE-2*r-3),
					  random_number(r+3, PICTURE_SIZE-r-3),
					  PSYMBOL);
	}

/*kresli čtverce*/
j= random_number(MIN_SQUARE, MAX_SQUARE);
//printf("počet čtverců: %i \n",j);

for (i=0; i<j; i++)
	{
   unsigned char size = random_number(2,10);
	draw_rectangle( picture,
					 	 size,
						 size,
						 random_number (1, PICTURE_SIZE - size - 1),
						 random_number (1, PICTURE_SIZE - size - 1),
						 PSYMBOL);
	}

/*kresli obdélníky*/
j= random_number(MIN_RECT, MAX_RECT);
//printf("počet obdélníků: %i \n",j);

for (i=0; i<j; i++)
	{
	unsigned height = random_number(2,10);
	unsigned width;
	while ( (width = random_number(2,10))==height ) {} //šířka a výška musí být různé 
	draw_rectangle(picture,
					 height,
					 width,
					 random_number (1, PICTURE_SIZE - height - 1),
					 random_number (1, PICTURE_SIZE - width - 1),
					 PSYMBOL);
	}

/*vykresli picture na výstup*/
for(i=0; i<PICTURE_SIZE; i++)
	{
	for (j=0; j<PICTURE_SIZE; j++)
		{
		putchar(picture[i][j]);
		}
	putchar('\n');
	}


return 0;
}

