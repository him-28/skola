#include "util.c"

#define MAXRUN 100000
#define REPEAT 10

int main ()
{
	int i,j;
	double x, y, pi[REPEAT];
	double av_pi = 0.0;
	double r_sum = 0.0;
	double stdev_pi = 0.0;
	unsigned success;

	for (i = 0; i < REPEAT; i++)
	{
		success = 0;

		for ( j = 0; j < MAXRUN; j++)
		{
			x = random_float (0, 1, 6);
			y = random_float (0, 1, 6);
		
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
	
	printf ("Směrodatná odchylka PI je : %f\n", stdev_pi);

	return 0;
} 
