#include "util.c"
#include <gsl/gsl_rng.h>

#define MAXRUN 100000000
#define REPEAT 10

int main ()
{
	int i,j;
	double x, y, pi[REPEAT];
	double av_pi = 0.0;
	double r_sum = 0.0;
	double stdev_pi = 0.0;
	unsigned success;

	const gsl_rng_type * T;
   gsl_rng * r;
     
   gsl_rng_env_setup();
     
   T = gsl_rng_default;
   r = gsl_rng_alloc (T);

	for (i = 0; i < REPEAT; i++)
	{
		success = 0;

		for ( j = 0; j < MAXRUN; j++)
		{
			x = gsl_rng_uniform (r);
			y = gsl_rng_uniform (r);
		
			if ( (x*x + y*y) <= 1.0 )
				success++;		
		}

		pi[i] = 4.0 * (double)success / (double)MAXRUN;
		printf ("%2i: PI je %2.5f\n", i, pi[i]);
	
		av_pi += pi[i];

	}
	
	av_pi /= (double)REPEAT;

	printf ("Průměrná hodnota PI je : %f\n", av_pi);
	
	for ( i = 0; i < REPEAT; i++)
	{
		r_sum += pow (pi[i] - av_pi, 2);
	}
	
	stdev_pi = sqrt( 1/(double)(REPEAT-1) * r_sum );
	
	printf ("Interval spolehlivosti 95%% : %f +- %f\n", av_pi, stdev_pi*1.833 );

	gsl_rng_free (r);

	return 0;
} 
