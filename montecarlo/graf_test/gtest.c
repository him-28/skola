#include <stdio.h>
#include <stdlib.h>
#include <gsl/gsl_rng.h>
#include <unistd.h>
#include <math.h>

#define NPOINTS 10000
#define PERIOD 10

int main (int argc, char* argv[])
{

	int c;
	unsigned int n=1;
	
/* vstup z příkazové řádky */
while ((c = getopt (argc, argv, "n:")) != -1)
	switch (c)
		{
		case 'n':
			n = strtol(optarg, 0, 10);
			break;
		default:
			return 0;
		}

	/*Initialize random number generator*/
	const gsl_rng_type * T;
   gsl_rng * r;

   gsl_rng_env_setup();
     
   T = gsl_rng_default;
   r = gsl_rng_alloc (T);

	double x,y;
	int i;

	for(i = 0; i < NPOINTS * n ; i++) {
		x = gsl_rng_uniform (r);
		y = gsl_rng_uniform (r);
		
		if (i % n == 0)
	  		printf("%f %f\n", x, y);
	}

	gsl_rng_free (r);

	return 0;
} 
