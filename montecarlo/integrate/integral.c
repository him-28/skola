#include <stdio.h>
#include <stdlib.h>
#include <gsl/gsl_rng.h>
#include <gsl/gsl_cdf.h>
#include <unistd.h>
#include <math.h>

#define M_PI 3.14159265358979323846264338327

int main (int argc, char* argv[])
{

	/*Initialize random number generator*/
	const gsl_rng_type * T;
   gsl_rng * r;
   gsl_rng_env_setup();
   T = gsl_rng_default;
   r = gsl_rng_alloc (T);

	double ra, yi, sum = 0;
	double pi4;

	for (int i = 10; i <= 1e8; i *= 10 ) {

		for (int j = 0; j < i ; j++) {
			ra = gsl_rng_uniform (r);
			sum += sqrt ( 1 - ra*ra );
		}
		pi4 = sum / (double) i ;
		sum = 0;
	printf ("%f %.8f %.8f\n", log10( (double) i ), pi4, log10( fabs (pi4 - M_PI / 4.0) ) ); 
	}

	gsl_rng_free (r);


	return 0;
} 
