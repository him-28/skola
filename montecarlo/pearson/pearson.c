#include <stdio.h>
#include <stdlib.h>
#include <gsl/gsl_rng.h>
#include <gsl/gsl_cdf.h>
#include <unistd.h>
#include <math.h>

#define NPOINTS 30000
#define PERIOD 10

/*compare function for qsort*/
static int compared( const void *A, const void *B)
{
	const double *a = A;
	const double *b = B;

	if (*a < *b)
		return -1;
	else if (*a > *b)
		return 1;
	else 
		return 0;
}

int main (int argc, char* argv[])
{

	/*Initialize random number generator*/
	const gsl_rng_type * T;
   gsl_rng * r;
   gsl_rng_env_setup();
   T = gsl_rng_default;
   r = gsl_rng_alloc (T);

	double x[NPOINTS] = { 0 };

	/* fill the array with random numbers */
	for(int i = 0; i < NPOINTS ; i++) {
		for (int j=0; j<12; j++) {
			x[i] += gsl_rng_uniform (r);
		}
		x[i] -= 6;
	}

	gsl_rng_free (r);

	/*sort array*/
	qsort (x, NPOINTS, sizeof(x[1]), compared );
	
	/*Number of intervals for the Pearson test*/
	//int intervals = round( pow( NPOINTS, 0.5 )); FIXME: changing with the interval numbers, but how?
	int intervals = 30; 
	printf ("Počet intervalů je: %d\n", intervals);

	/*   */
	int N[intervals];
	
	int i, j = 0;
	double limit;

	for( i = 0; i < intervals - 1; i++ ) {
		N[i] = 0;
		limit = gsl_cdf_gaussian_Pinv( (i+1) / (double)intervals, 1.0);
		while ( x[j] < limit ) {
			N[i]++;
			j++;
		}
	}
	/*Rest is from the last interval */
	N[i] = 0;
	N[i] += NPOINTS - j;

	/*Number of expected points in each interval*/
	double expected = NPOINTS*1.0/(double)intervals;

	/*Compute chi squared*/
	double chisq = 0.0;
	for ( int i = 0; i < intervals; i++ ) {
		chisq += ( N[i] - expected )*( N[i] - expected ) / expected;
	}
	
	printf("Chi^2: %f\n", chisq);

	printf ( "+-----------+-----------+----------+----------+----------+\n");
	printf ( "|    from   |     to    | observed | expected |  chi_i   |\n");	
	for ( int i = 0; i < intervals; i++ ) 
	printf ( "| %2.6f | %2.6f | %8i | %8f | %8f |\n" , 
				gsl_cdf_gaussian_Pinv( i / (double)intervals, 1.0),
				gsl_cdf_gaussian_Pinv( (i+1) / (double)intervals, 1.0),
				N[i],
				expected,
				( N[i] - expected )*( N[i] - expected ) / expected );
	printf ( "+-----------+-----------+----------+----------+----------+\n");


	printf ("Hypotézu o normálním rozdělení můžeme zamítnout s jistotou %f \n", gsl_cdf_chisq_P (chisq, intervals - 1 ) );


	/*output histogram*/
	FILE *graf;
	graf = fopen ("graf.txt", "w");
	int Nb[NPOINTS] = { 0 };
	int h = 0;

	for (double i = -4.0; i < 3.99; i += 0.25) {
		
		for (int j = 0; j< NPOINTS; j++) {
			if ( x[j] > i &&  x[j] < (i + 0.25) )
				Nb[h]++;
			}
		double p = ( gsl_cdf_gaussian_P ( i + 0.25 , 1.0 ) - gsl_cdf_gaussian_P ( i , 1.0 ) ) * NPOINTS;
		fprintf (graf, "%f %f %i\n", i + 0.125, p, Nb[h] );
		h++;
		}



	/* Kolmogorov FIXME
	double exp_cdf = 0;
	double maxdif = 0;
	double dif;
	
	for(int k = 0; k < NPOINTS ; k++) {
		exp_cdf += 1.0/(double)NPOINTS;
		if ( ( dif = abs( exp_cdf - gsl_cdf_gaussian_P ( x[k], 1.0) ) ) > maxdif )
			maxdif = dif;
	}

	maxdif = sqrt( (double)NPOINTS * maxdif );

	printf ("Kolmogorův test: %f\n", maxdif);
	*/	


	return 0;
} 
