#include <stdlib.h>
#include <stdio.h>
#include <gsl/gsl_rng.h> 
#include <gsl/gsl_vector.h>
#include <gsl/gsl_blas.h>
#include <gsl/gsl_multifit_nlin.h>
#include <gsl/gsl_complex.h>
#include <gsl/gsl_complex_math.h>
#include "sidata.c"
#include <unistd.h>
#include "shared.c"


/* calls Refl for all wavelenghts */
int reflectance (const gsl_vector * x, void *data, gsl_vector * f)
{
	gsl_complex imunit, one;
	imunit = gsl_complex_rect (0.0, 1.0);
	one = gsl_complex_rect (1.0, 0.0);

	double A = gsl_vector_get (x, 0);
	double B = gsl_vector_get (x, 1);
	double d = gsl_vector_get (x, 2);

	double l[1500], y[1500], R;

	get_r (l , y);

	int n;	
	for (n=0; l[n]; n++) {}

	size_t i;

	for (i = 0; i < 811; i++)
	{
		R = Refl(A, B, d , l[i], 0.0, 0.0 );
		//printf ("R: %e %e \n", l[i], R);
		gsl_vector_set (f, i, R - y[i]); 
	}

	return GSL_SUCCESS;
}


double reflectance_pro_dA (double A, void * p)
{
	struct my_f_params { double a; double b; double c; };
	struct my_f_params * params
		= (struct my_f_params *)p;
		double B = params->a;
		double d = params->b;
		double l = params->c;
	return Refl (A, B, d, l, 0.0, 0.0);
}

double reflectance_pro_dB (double B, void * p)
{
	struct my_f_params { double a; double b; double c; };
	struct my_f_params * params
		= (struct my_f_params *)p;
		double A = params->a;
		double d = params->b;
		double l = params->c;
	return Refl (A, B, d, l, 0.0, 0.0);
}

double reflectance_pro_dd (double d, void * p)
{
	struct my_f_params { double a; double b; double c; };
	struct my_f_params * params
		= (struct my_f_params *)p;
		double A = params->a;
		double B = params->b;
		double l = params->c;
	return Refl (A, B, d, l, 0.0, 0.0);
}

int reflectance_df (const gsl_vector * x, void *data, gsl_matrix * J)
{
	struct my_f_params { double a; double b; double c; };

	double A = gsl_vector_get (x, 0);
	double B = gsl_vector_get (x, 1);
	double d = gsl_vector_get (x, 2);
	double result, abserr;

	double l[1500], y[1500];

	get_r (l , y);

	int i;
	for (i = 0; i < 811; i++) //FIXME: hardcoded
	{
		//numerická derivace
		gsl_function FA;
		struct my_f_params paramsA = { B, d, l[i] };
	 
		FA.function = &reflectance_pro_dA;
		FA.params = &paramsA;
	
		gsl_deriv_central (&FA, A, 1e-4, &result, &abserr);
		
		//printf ("dR/dA: %e %e\n" , l[i], result ); 
		gsl_matrix_set (J, i, 0, result);

		gsl_function FB;
		struct my_f_params paramsB = { A, d, l[i] };
	 
		FB.function = &reflectance_pro_dB;
		FB.params = &paramsB;
	
		gsl_deriv_central (&FB, B, 1e-20, &result, &abserr);
		
		//printf ("dR/dB: %e %e\n" , l[i], result ); 
		gsl_matrix_set (J, i, 1, result);

		gsl_function Fd;
		struct my_f_params paramsd = { A, B, l[i] };
	 
		Fd.function = &reflectance_pro_dd;
		Fd.params = &paramsd;
	
		gsl_deriv_central (&Fd, d, 1e-1, &result, &abserr);
		
		//printf ("dR/dd: %e %e\n" , l[i], result ); 
		gsl_matrix_set (J, i, 2, result);
	 }
return GSL_SUCCESS;
}

int
reflectance_fdf (const gsl_vector * x, void *data,
gsl_vector * f, gsl_matrix * J)
{
reflectance (x, NULL, f);
reflectance_df (x, NULL, J);

return GSL_SUCCESS;
}

void
print_state (size_t iter, gsl_multifit_fdfsolver * s)
{
printf ("iter: %3u x = % 15.8e % 15.8e % 15.8e "
"|f(x)| = %g\n",
iter,
gsl_vector_get (s->x, 0), 
gsl_vector_get (s->x, 1),
gsl_vector_get (s->x, 2), 
gsl_blas_dnrm2 (s->f));
}


int main( int argc, char *argv[] )
{

	/*some reasonable defaults*/
	double A = 1.4;
	double B = 4.0e-15;
	double d = 400.0;

	if (argv[1]==NULL)
	{
	print_help();
	return 0;
	}

int c;
/* vstup z příkazové řádky */
while ((c = getopt (argc, argv, "A:B:d:")) != -1)
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

	const gsl_multifit_fdfsolver_type *T;
	gsl_multifit_fdfsolver *s;
	int status;
	unsigned int i, iter = 0;
	const size_t n = 811;
	const size_t p = 3;	

	const gsl_rng_type * type;
	gsl_rng * r;

	gsl_matrix *covar = gsl_matrix_alloc (p, p);
	
	double x_init[3] = { A, B, d };
	gsl_vector_view x = gsl_vector_view_array (x_init, 3);
	
	//reflectance ( &x.vector, NULL, &x.vector );
	//reflectance_df ( &x.vector, NULL , NULL);

	gsl_multifit_function_fdf f;

	gsl_rng_env_setup();

	type = gsl_rng_default;
	r = gsl_rng_alloc (type);

	f.f = &reflectance;
	f.df = &reflectance_df;
	f.fdf = &reflectance_fdf;
	f.n = n;
	f.p = p;
	f.params = NULL;

T = gsl_multifit_fdfsolver_lmsder;
s = gsl_multifit_fdfsolver_alloc (T, n, p);
gsl_multifit_fdfsolver_set (s, &f, &x.vector);

print_state (iter, s);

do
	 {
 iter++;
 status = gsl_multifit_fdfsolver_iterate (s);

 printf ("status = %s\n", gsl_strerror (status));

 print_state (iter, s);

 if (status)
	break;

 status = gsl_multifit_test_delta (s->dx, s->x,
1e-4, 1e-4);
	 }
while (status == GSL_CONTINUE && iter < 500);

gsl_multifit_covar (s->J, 0.0, covar);

#define FIT(i) gsl_vector_get(s->x, i)
#define ERR(i) sqrt(gsl_matrix_get(covar,i,i))

{ 
	 double chi = gsl_blas_dnrm2(s->f);
	 double dof = n - p;
	 double c = chi / sqrt(dof); 

	 printf("chisq/dof = %g\n",pow(chi, 2.0) / dof);

	 printf ("A = %.5e +/- %.5e\n", FIT(0), c*ERR(0));
	 printf ("B = %.5e +/- %.5e\n", FIT(1), c*ERR(1));
	 printf ("d = %.5e +/- %.5e\n", FIT(2), c*ERR(2));

}

printf ("status = %s\n\n", gsl_strerror (status));

printf ("You can plot your data with \"R-compute -A %.5e -B %.5e -d %.5e\"\n\n", FIT(0), FIT(1), FIT(2) );

gsl_multifit_fdfsolver_free (s);
gsl_matrix_free (covar);
gsl_rng_free (r);

return 0;
}

