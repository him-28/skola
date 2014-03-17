#include <gsl/gsl_vector.h>
#include <gsl/gsl_blas.h>
#include <gsl/gsl_multifit_nlin.h>
#include <gsl/gsl_complex.h>
#include <gsl/gsl_complex_math.h>
#include "sidata.c"
#include "shared.c"

int reflectance (const gsl_vector * x)
{
	gsl_complex imunit, one;
	imunit = gsl_complex_rect (0.0, 1.0);
	one = gsl_complex_rect (1.0, 0.0);

	double A = gsl_vector_get (x, 0);
	double B = gsl_vector_get (x, 1);
	double d = gsl_vector_get (x, 2);
	double alph = gsl_vector_get (x, 3);
	double beta = gsl_vector_get (x, 4);

	double l[1500], y[1500];

  size_t i;

  gsl_complex ns, n0, nv, r1, r2, alpha, eialpha, r;

  for (i = 0; i < 811; i++)
    {
	 l[i] = 190.0 + (double)i;
		
	 ns = get_ns ( l[i] );

    n0 = gsl_complex_rect (1.0, 0.0); //air, no absorption
    nv = gsl_complex_rect ( A + B/(l[i]*l[i]*1.0e-18) , alph*exp( -beta * l[i] * 1.0e-9 ) ); //2 parameters Cauchy formula, absorption 

    r1 = gsl_complex_div (gsl_complex_sub(n0 , nv) , gsl_complex_add(n0 , nv) );
    r2 = gsl_complex_div (gsl_complex_sub(nv , ns) , gsl_complex_add(nv , ns) );

    alpha = gsl_complex_mul_real( nv , (4.0 * 3.14 * d)/l[i] );

    eialpha = gsl_complex_exp ( gsl_complex_mul ( imunit, alpha ) );

    r = gsl_complex_div (
			gsl_complex_add( r1 , gsl_complex_mul ( r2, eialpha ) ),
			gsl_complex_add( one ,  gsl_complex_mul ( gsl_complex_mul ( r1, r2 ), eialpha ) ) 
			 );

    double R = gsl_complex_abs2 ( r );

    printf ("%e %e \n", l[i], R);
    }

  return GSL_SUCCESS;
}


int main( int argc, char *argv[] )
{
	/*some reasonable defaults*/
	double A = 1.4;
	double B = 4.0e-15;
	double d = 400.0;
	double a = 0.0;
	double b = 1e5;

	if (argv[1]==NULL)
	{
	print_help();
	return 0;
	}

int c;
/* vstup z příkazové řádky */
while ((c = getopt (argc, argv, "A:B:d:a:b:")) != -1)
	switch (c)
		{
		case 'A':
			A = strtod(optarg, 0);
			break;
		case 'B':
		  B = strtod(optarg, 0);
		  break;
		case 'd':
		  d = strtod(optarg, 0);
		  break;
		case 'a':
		  a = strtod(optarg, 0);
		  break;
		case 'b':
		  b = strtod(optarg, 0);
		  break;
		case '?':
		  if (optopt == 'a')
		    fprintf (stderr, "Parametr -%c vyžaduje argument.\n", optopt);
		  else if (isprint (optopt))
		    fprintf (stderr, "Neznámý přepínač `-%c'.\n", optopt);
		  else
		    fprintf (stderr, "Unknown option character `\\x%x'.\n", optopt);
			return 1;
		default:
			print_help();
			return 0;
		}
	
  double x_init[5] = { A, B, d, a, b};
  gsl_vector_view x = gsl_vector_view_array (x_init, 5);
  reflectance ( &x.vector );
  return 0;	
}
