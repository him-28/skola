#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>
#include "string.h"



/* generovani nahodnych cisel, jako seed pro funkci (srand) je použit systémový čas */
int random_int ( int from, int to )
	{
	extern int last_random_number;

	struct timeval time;
	gettimeofday(&time, NULL);

	srand(time.tv_usec*time.tv_sec*rand());
	return (from + rand()%(to - from + 1));
	}

double random_float ( int from, int to, int decimal_size )
	{
	double i,j;
	i = (double)random_int(from, to-1);
	j = (double)random_int(0 , pow(10.0, (double)(decimal_size) ) ) -1.0;

	return i+j/(pow(10.0, (double)(decimal_size)));
	}

double normal_float01 ( )
	{
	double y=0.0;
	int j;

	for(j=1; j<=12; j++)
		{
		y += random_float(0,1,5);
		}

	y -= 6;	

	return y;
	}

void print_help()
	{
	printf ("Argumenty:\n -b [kvadratický člen] (default: 1)\n -a [lineární člen] (default:1 )\n -s [směrodatná odchylka] (default: 1)\n -l [počet cyklů] (default: 10)\n");
	}
