/* Rozpoznávání vzorů v binárním obrázku */

#include "util.c"

char check_rotated_square (unsigned char cpicture[PICTURE_SIZE][PICTURE_SIZE],
		    int i, int j)
	{
	//printf("check_rhombus i:%i j:%i\n",i, j);
	
	int k,l,r=0;

	for(k=0; k<= ( !r ? PICTURE_SIZE : 2*r ) ; k++)
		{
		for (l=0; l<=( !r ? k : 2*r - k) ; l++)
			{

	/* pokud ještě není určeno r a alespoň jeden pixel chybí, tak zkontrolujeme o jedna méňe a 
	pokud tam není ani jeden a ještě o jedna méňe jsou oba, značí to, že se začíná kosočtverec zmenšovat */
			if(cpicture[i+k][j+l] && cpicture[i+k][j-l] ) 
				{
				if( l == ( !r ? k : 2*r - k) ) 
					{					
					if ( cpicture[i+k][j+l+1] || cpicture[i+k][j-l-1])
						{
						return 0;
						}
					}
				}			
			else if ( r==0 && (!cpicture[i+k][j+l] && !cpicture[i+k][j-l]) 
				  && ( cpicture[i+k][j+l-1] && cpicture[i+k][j-l+1]))
				{							 
				r=k-1;
				//printf ("r= %i\n",r);
				break;
				}
			else	{
				//printf("k:%i l:%i \n",k,l);
				return 0;
				}
			//printf("k:%i l:%i \n",k,l);				
			}
		}

	if ( cpicture[i-1][j] || cpicture[i+2*r+1][j] )
		return 0;
		
	printf("Nalezen otočený čtverec: řádek:%i, sloupec:%i, úhlopříčka:%i, obsah:%.0f \n", i , j, 2*r+1, (float)(2*r+1)*(float)(2*r+1)*0.5+ 0.5);
   	
	/*nyní vynulujeme celý kosočtverec v cpicture*/
	draw_rotated_square(cpicture, r, i, j ,0);
	
	return 1;
	
	}

char check_square (unsigned char cpicture[PICTURE_SIZE][PICTURE_SIZE],
		   int i, int j)
	{
	//printf("check_square i:%i j:%i\n",i, j);
	
	int k, l, a=0;
	for (k=0; k< ( !a ? PICTURE_SIZE : a ); k++)
		{
		for (l=0; l < ( !a ? PICTURE_SIZE : a ) ; l++)
			{
			
			if ( cpicture[i+k][j+l] ) 
				{
				if( l==0 && cpicture[i+k][j-1])
					{
					//printf("check fail: left side k:%i l:%i \n",k,l);
					return 0;
					}
				else if ( l == (!a ? PICTURE_SIZE : a-1 ) && cpicture[i+k][j+l+1] )
					{
					//printf("check fail: right side k:%i l:%i \n",k,l);
					return 0;
					}
				else if ( k==0 && cpicture[i-1][j+l])
					{
					//printf("check fail: top side k:%i l:%i \n",k,l);
					return 0;
					}
				else if ( k == (!a ? PICTURE_SIZE : a-1 ) && cpicture[i+k+1][j+l] )
					{
					//printf("check fail: bottom side k:%i l:%i \n",k,l);
					return 0;
					}
				}

			else if ( !a && k==0 && !cpicture[i+k][j+l] && cpicture[i+k][j+l-1] )
				{
					if(l<2)
						return 0;
				a=l;
				//printf("side found: k:%i l:%i a:%i\n",k,l,a);	
				break;
				}			
						
			else 
				{
				//printf("else k:%i l:%i \n",k,l);
				return 0;
				}
			}
		}
	printf ("Nalezen čtverec: řádek:%i sloupec:%i, velikost:%i, obsah:%i \n", i, j, a, a*a);
	
	/*vynuluj nalezený čtverec*/
	draw_rectangle (cpicture, a, a, i, j, 0);

	return 1;
	}


char check_rectangle (unsigned char cpicture[PICTURE_SIZE][PICTURE_SIZE],
		   int i, int j)
	{
	//printf("check_rectangle i:%i j:%i\n",i, j);
	
	int k, l, height=0, width=0;
	
	for (k=0; k < ( height ? height : PICTURE_SIZE ); k++)
		{
		for (l=0; l < ( width ? width : PICTURE_SIZE ) ; l++)
			{
			if ( cpicture[i+k][j+l] ) 
				{
				if( l==0 && cpicture[i+k][j-1])
					{
					//printf("check fail: left side k:%i l:%i \n",k,l);
					return 0;
					}
				else if ( l == (width ?  width-1 : PICTURE_SIZE) && cpicture[i+k][j+l+1] )
					{
					//printf("check fail: right side k:%i l:%i \n",k,l);
					return 0;
					}
				else if ( k==0 && cpicture[i-1][j+l])
					{
					//printf("check fail: top side k:%i l:%i \n",k,l);
					return 0;
					}
				else if ( k == (height ? height-1 : PICTURE_SIZE ) && cpicture[i+k+1][j+l] )
					{
					//		("check fail: bottom side k:%i l:%i \n",k,l);
					return 0;
					}
				}

			else if ( !width && k==0 && !cpicture[i+k][j+l] && cpicture[i+k][j+l-1] )
				{
				if(l<2)
					return 0;
				width=l;
				//printf("width found: k:%i l:%i width:%i\n",k,l,width);	
				break;
				}	
	
			else if ( !height && l==0 && !cpicture[i+k][j] && cpicture[i+k-1][j] )
				{
				if(k<2)
					return 0;
				height=k;
				//printf("height found: k:%i l:%i height:%i\n",k,l,height);	
				break;
				}			
						
			else 
				{
				//printf("else k:%i l:%i \n",k,l);
				return 0;
				}
			}
		}
	printf ("Nalezen obdélník: řádek:%i, sloupec:%i, šířka:%i, výška:%i, obsah:%i \n", i, j, width, height, width*height);
	
	/*vynuluj nalezený obdélník*/
	draw_rectangle (cpicture, height, width, i, j, 0);	
	
	return 1;
	}


int main()
{
unsigned z, nsquare, nrectangle, nrhombus, nmsquare, nmrectangle, nmrhombus;
unsigned char cpicture[PICTURE_SIZE][PICTURE_SIZE], picture[PICTURE_SIZE][PICTURE_SIZE];
unsigned char cpicture2[PICTURE_SIZE][PICTURE_SIZE];

int i,j;

nsquare = nrectangle = nrhombus = nmsquare = nmrectangle = nmrhombus = 0;

/*inicializuj pole*/
//draw_rectangle(picture, PICTURE_SIZE, PICTURE_SIZE, 0, 0, 0);
//draw_rectangle(cpicture, PICTURE_SIZE, PICTURE_SIZE, 0, 0, 0);
//draw_rectangle(cpicture2, PICTURE_SIZE, PICTURE_SIZE, 0, 0, 0);

memset(&picture, 0, sizeof(unsigned char)*PICTURE_SIZE*PICTURE_SIZE );
memset(&cpicture, 0, sizeof(unsigned char)*PICTURE_SIZE*PICTURE_SIZE );
memset(&cpicture2, 0, sizeof(unsigned char)*PICTURE_SIZE*PICTURE_SIZE );

/*TODO: kontrola validity vstupu*/

i=0;
j=0;

/*načti vstup do cpicture*/
z = getchar();
while(z!=EOF)
{
	if(z == '\n') 
		{
		i++;
		j = 0;
		}
	else
		{
		picture[i][j]  = ( z == 'x' ? 1 : 0 );
		cpicture[i][j] = ( z == 'x' ? 1 : 0 );
		j++;
		}
	putchar (z);
	z=getchar();	
}


/*main loop*/
for (i=0; i<PICTURE_SIZE; i++)
	{
	for (j=0; j<PICTURE_SIZE; j++)
		{
		if( cpicture[i][j]==1)
			{
			if( check_rotated_square(cpicture, i, j) ) {nrhombus++;}
			else if (check_square(cpicture, i , j)) {nsquare++;}
			else if (check_rectangle(cpicture, i, j)) {nrectangle++;}
			}
		}
	}

/*spočítej zbývající pixely*/
int pixelcount=0;
pixelcount=count_pixels(cpicture);
//printf("zbývá nerozpoznaných pixelů: %i\n",pixelcount);

/* synchronizuj picture and cpicture, rozpoznané obrazce nás už nezajímají */
sync_pictures(picture, cpicture);

/*rozpoznávání překrývajících se obrazců*/
int objects[MAX_OBJECTS][5];
int k,l,t;

for (i=0; i<PICTURE_SIZE; i++)
	{
	for (j=0; j<PICTURE_SIZE; j++)
		{
		if( cpicture[i][j]==1 )
			{
			//printf ("main: testuji řádek:%i, sloupec:%i\n",i,j);
			sync_pictures(cpicture2, cpicture);
			
			/*zkoušíme otočené čtverce*/
			for(k=1; k<=15; k++)
				{
				draw_rotated_square (cpicture, k, i, j, 2);
				if ( compare(cpicture,picture) ) 
					{
					draw_rotated_square (cpicture, k, i, j, 0);
					if( ( t=count_pixels(cpicture) ) < pixelcount )
						{
						pixelcount=t;
						//printf("main-testing_rhombus: zbývá nerozpoznaných pixelů: %i\n",actual_count);
						save_object(objects, 1, i, j, k, k); //uloží, pokud už tam je tak přepíše
						}
					}
				sync_pictures(cpicture,cpicture2);
				}
			
			/*zkoušíme obdélníky a čtverce dohromady*/
			for(k=2; k<=15; k++)
				{
				for(l=2; l<=15; l++)
					{
					draw_rectangle(cpicture, k, l, i, j, 2);
					if ( compare(cpicture,picture) ) 
						{
						draw_rectangle(cpicture, k, l, i, j, 0);
						if( ( t=count_pixels(cpicture) ) < pixelcount )
							{
							pixelcount=t;
							//printf("main-testing_rectagle: zbývá nerozpoznaných pixelů: %i\n",actual_count);
							save_object(objects, 2, i, j, k, l); //uloží, pokud už tam je tak přepíše
							}
						}
					sync_pictures(cpicture,cpicture2);
					}
				}
			
			draw_last_object(cpicture, objects, 0);
			}
		}
	}
display_objects(objects, &nmrhombus, &nmsquare, &nmrectangle);	

printf("\nVÝSLEDKY\n");
printf("Samostatné obrazce:\n");
printf("Nalezeno otočených čtverců:%i, čtverců:%i, obdélníků:%i\n", nrhombus,nsquare,nrectangle);

printf("Překrývající se obrazce:\n");
printf("Nalezeno otočených čtverců:%i, čtverců:%i, obdélníků:%i\n", nmrhombus,nmsquare,nmrectangle);
	

return 0;
}

