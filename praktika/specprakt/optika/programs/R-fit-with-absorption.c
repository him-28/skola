#include <gsl/gsl_rng.h> 
#include <gsl/gsl_vector.h>
#include <gsl/gsl_blas.h>
#include <gsl/gsl_multifit_nlin.h>
#include <gsl/gsl_complex.h>
#include <gsl/gsl_complex_math.h>
#include "sidata.c"
#include "shared.c"

#define N 811


/* calls Refl for all wavelenghts */
int reflectance (const gsl_vector * x, void *data, gsl_vector * f)
{
	gsl_complex imunit, one;
	imunit = gsl_complex_rect (0.0, 1.0);
	one = gsl_complex_rect (1.0, 0.0);

	double A = gsl_vector_get (x, 0);
	double B = gsl_vector_get (x, 1);
	double d = gsl_vector_get (x, 2);
	double alpha = gsl_vector_get (x, 3);
	double beta = gsl_vector_get (x, 4);

	double l[1500], y[1500], R; //FIXME: more hardcoded size stuff

	get_r (l , y);

	int n;	
	for (n=0; l[n]; n++) {}

	size_t i;

	for (i = 0; i < N; i++)
	{
		R = Refl(A, B, d , l[i], alpha, beta );
		//printf ("R: %e %e \n", l[i], R);
		gsl_vector_set (f, i, R - y[i]); 
	}

	return GSL_SUCCESS;
}


double reflectance_for_dA (double A, void * p)
{
	struct my_f_params { double a; double b; double c; double d; double e; };
	struct my_f_params * params
		= (struct my_f_params *)p;
	double B = params->a;
	double d = params->b;
	double l = params->c;
	double alpha = params->d;
	double beta = params->e;
	
	return Refl (A, B, d, l, alpha, beta);
}

double reflectance_for_dB (double B, void * p)
{
	struct my_f_params { double a; double b; double c; double d; double e; };
	struct my_f_params * params
		= (struct my_f_params *)p;
	double A = params->a;
	double d = params->b;
	double l = params->c;
	double alpha = params->d;
	double beta = params->e;
	
	return Refl (A, B, d, l, alpha, beta);
}

double reflectance_for_dd (double d, void * p)
{
	struct my_f_params { double a; double b; double c; double d; double e; };
	struct my_f_params * params
		= (struct my_f_params *)p;
	double A = params->a;
	double B = params->b;
	double l = params->c;
	double alpha = params->d;
	double beta = params->e;
	
	return Refl (A, B, d, l, alpha, beta);
}

double reflectance_for_dalpha (double alpha, void * p)
{
	struct my_f_params { double a; double b; double c; double d; double e; };
	struct my_f_params * params
		= (struct my_f_params *)p;
	double A = params->a;
	double B = params->b;
	double d = params->c;
	double l = params->d;
	double beta = params->e;
	
	return Refl (A, B, d, l, alpha, beta);
}

double reflectance_for_dbeta (double beta, void * p)
{
	struct my_f_params { double a; double b; double c; double d; double e; };
	struct my_f_params * params
		= (struct my_f_params *)p;
	double A = params->a;
	double B = params->b;
	double d = params->c;
	double l = params->d;
	double alpha = params->e;
	
	return Refl (A, B, d, l, alpha, beta);
}

int reflectance_df (const gsl_vector * x, void *data, gsl_matrix * J)
{
	struct my_f_params { double a; double b; double c; double d; double e; };

	double A = gsl_vector_get (x, 0);
	double B = gsl_vector_get (x, 1);
	double d = gsl_vector_get (x, 2);
	double alpha = gsl_vector_get (x, 3);
	double beta = gsl_vector_get (x, 4);
	double result, abserr;

	double l[1500], y[1500];

	get_r (l , y);

	int i;
	for (i = 0; i < N; i++) //FIXME: hardcoded
	{
		//numerická derivace
		gsl_function FA;
		struct my_f_params paramsA = { B, d, l[i], alpha, beta };
	 
		FA.function = &reflectance_for_dA;
		FA.params = &paramsA;
	
		gsl_deriv_central (&FA, A, 1e-4, &result, &abserr);
		
		//printf ("dR/dA: %e %e\n" , l[i], result ); 
		gsl_matrix_set (J, i, 0, result);


		gsl_function FB;
		struct my_f_params paramsB = { A, d, l[i], alpha, beta };
	 
		FB.function = &reflectance_for_dB;
		FB.params = &paramsB;
	
		gsl_deriv_central (&FB, B, 1e-20, &result, &abserr);
		
		//printf ("dR/dB: %e %e\n" , l[i], result ); 
		gsl_matrix_set (J, i, 1, result);


		gsl_function Fd;
		struct my_f_params paramsd = { A, B, l[i], alpha, beta };
	 
		Fd.function = &reflectance_for_dd;
		Fd.params = &paramsd;
	
		gsl_deriv_central (&Fd, d, 1e-1, &result, &abserr);
		
		//printf ("dR/dd: %e %e\n" , l[i], result ); 
		gsl_matrix_set (J, i, 2, result);


		gsl_function Falpha;
		struct my_f_params paramsalpha = { A, B, d, l[i], beta };
	 
		Falpha.function = &reflectance_for_dalpha;
		Falpha.params = &paramsalpha;
	
		gsl_deriv_central (&Falpha, alpha, 1.0e-1, &result, &abserr);
		
		//printf ("dR/dd: %e %e\n" , l[i], result ); 
		gsl_matrix_set (J, i, 3, result);


		gsl_function Fbeta;
		struct my_f_params paramsbeta = { A, B, d, l[i], alpha };
	 
		Fbeta.function = &reflectance_for_dbeta;
		Fbeta.params = &paramsbeta;
	
		gsl_deriv_central (&Fbeta, beta, 1.0, &result, &abserr);
		
		//printf ("dR/dd: %e %e\n" , l[i], result ); 
		gsl_matrix_set (J, i, 4, result);
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
printf ("iter: %3u x = % 15.8e % 15.8e % 15.8e % 15.8e % 15.8e "
"|f(x)| = %g\n",
iter,
gsl_vector_get (s->x, 0), 
gsl_vector_get (s->x, 1),
gsl_vector_get (s->x, 2), 
gsl_vector_get (s->x, 3), 
gsl_vector_get (s->x, 4), 
gsl_blas_dnrm2 (s->f));
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

	const gsl_multifit_fdfsolver_type *T;
	gsl_multifit_fdfsolver *s;
	int status;
	unsigned int i, iter = 0;
	const size_t n = N;
	const size_t p = 5;	

	const gsl_rng_type * type;
	gsl_rng * r;

	gsl_matrix *covar = gsl_matrix_alloc (p, p);
	
	double x_init[5] = { A, B, d, a, b };
	gsl_vector_view x = gsl_vector_view_array (x_init, 5);
	
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
	 printf ("aplha = %.5e +/- %.5e\n", FIT(3), c*ERR(3));
	 printf ("beta = %.5e +/- %.5e\n", FIT(4), c*ERR(4));	 
}

printf ("status = %s\n\n", gsl_strerror (status));

printf ("You can plot your data with \"R-compute -A %.3e -B %.3e -d %.3e -a %.3e -b %.3e\"\n\n", FIT(0), FIT(1), FIT(2), FIT(3), FIT(4) );

gsl_multifit_fdfsolver_free (s);
gsl_matrix_free (covar);
gsl_rng_free (r);

return 0;
}

