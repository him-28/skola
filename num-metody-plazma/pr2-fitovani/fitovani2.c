#include "util.c"
#include <gsl/gsl_linalg.h>
#include <gsl/gsl_blas.h>
#include <string.h>
#include <unistd.h>

#define NPARAM 2
#define NPOINTS 101
#define MAXLENGTH 100

int main (int argc, char *argv[])
{
int c,i,j,k,run,  suc_a=0, suc_b=0, suc_line=0;
char word[MAXLENGTH];

FILE *intregfunc, *parametersprob;
intregfunc = fopen("probability_of_regresion_funcion.txt","w");
parametersprob = fopen("probability_of_parameters.txt","w");

/* rozumné počáteční parametry*/
int maxrun=10;
double a = 1.0;
double b = 2.0;
double stdev = 5;

if (argv[1]==NULL)
	{
	print_help();
	return 0;
	}

while ((c = getopt (argc, argv, "a:b:l:s:")) != -1)
	switch (c)
		{
		case 'a':
			a = strtol(optarg, 0, 10);
			break;
		case 'b':
		  b = strtol(optarg, 0, 10);
		  break;
		case 'l':
		  maxrun = strtol(optarg, 0, 10);
		  break;
		case 's':
		  stdev = strtol(optarg, 0, 10);
		  break;
		case '?':
		  if (optopt == 'a')
		    fprintf (stderr, "Option -%c requires an argument.\n", optopt);
		  else if (isprint (optopt))
		    fprintf (stderr, "Unknown option `-%c'.\n", optopt);
		  else
		    fprintf (stderr, "Unknown option character `\\x%x'.\n", optopt);
			return 1;
		default:
			print_help();
			return 0;
		}

for (run=0; run<maxrun; run++)
{

	double x[NPOINTS],y[NPOINTS];

	/* generování náhodných bodů */
	for (i=0; i<NPOINTS; i++)
		{
		x[i] = (double)i/10.0;
		y[i] = a + b*x[i]*x[i] + stdev*normal_float01();
		}

double A[2][2]={}, B[2][2]={}, R[2]={}, n;

for (i=0; i<NPOINTS; i++)
	{
	A[0][0] += 1;
	A[0][1] += x[i]*x[i];
	R[0]    += y[i];
	A[1][0] += x[i]*x[i];
	A[1][1] += x[i]*x[i]*x[i]*x[i];
	R[1]	  += y[i]*x[i]*x[i];
	}


		double inv_data[] = {0.0, 0.0, 0.0, 0.0 };
     
       double r_data[] = { R[0], R[1] };
     
      gsl_matrix *m = gsl_matrix_calloc (2, 2);
		gsl_matrix_set (m, 0, 0, A[0][0]);
		gsl_matrix_set (m, 0, 1, A[0][1]);
		gsl_matrix_set (m, 1, 0, A[1][0]);
		gsl_matrix_set (m, 1, 1, A[1][1]);

		//gsl_matrix_fprintf (stdout, m, "%e");

		gsl_matrix *inversion_m = gsl_matrix_calloc (2, 2);
     
		gsl_vector_view r	= gsl_vector_view_array (r_data, 2);
     
       gsl_vector *v = gsl_vector_alloc (2);
       
      int signum;
     
      gsl_permutation * p = gsl_permutation_alloc (2);
		 
		/* LU dekompozice + řešení*/
		gsl_linalg_LU_decomp (m, p, &signum);
		gsl_linalg_LU_solve (m, p, &r.vector, v);
     
		double A1 = gsl_vector_get(v, 0);
		double A2 = gsl_vector_get(v, 1);

		/*compute iverse matrix*/
		gsl_linalg_LU_invert (m, p, inversion_m );

		double sa = gsl_matrix_get(inversion_m, 0,0);
		double sb = gsl_matrix_get(inversion_m, 1,1);

		//gsl_matrix_fprintf (stdout, inversion_m, "%e");

		gsl_permutation_free (p);
		gsl_matrix_free (m);
     	gsl_vector_free (v);


double residuum = 0.0;

for (i=0; i<NPOINTS; i++)
	{
	residuum += pow((y[i] -(A2*x[i]*x[i]) -A1), 2.0);  
	}

printf ("residuální suma čtverců: %e\n", residuum);
printf ("bodový odhad rozptylu:%f\n", sqrt(residuum/(float)(NPOINTS-NPARAM)));

double sigma_a = 1.01*sqrt(sa*(residuum/(float)(NPOINTS-NPARAM)));
double sigma_b = 1.01*sqrt(sb*(residuum/(float)(NPOINTS-NPARAM)));
printf ("a:%f b:%f\n", A1, A2);
printf ("sigma_a:%e sigma_b:%e\n", sigma_a, sigma_b);

if ( A1 < (a + sigma_a) && A1 > (a - sigma_a) )
	suc_a++;
if ( A2 < (b + sigma_b) && A2 > (b - sigma_b) )
	suc_b++;

fprintf (parametersprob ,"%d %f %f 0.683\n", run+1, ((float)suc_a)/((float)(run+1)), ((float)suc_b)/((float)(run+1)));


	double z[NPOINTS], original_fcn[NPOINTS], exp_fcn[NPOINTS], top_limit[NPOINTS], bot_limit[NPOINTS];
	gsl_vector *temp = gsl_vector_calloc (2);
	gsl_vector *func = gsl_vector_calloc (2);

	// určení intervalových odhadů funkce
	for (i=0; i<NPOINTS; i++)
	{

	gsl_vector_set (func, 0, 1.0);
	gsl_vector_set (func, 1, x[i]*x[i]);

	/* matice * vektor */
	gsl_blas_dgemv (CblasNoTrans, 1.0, inversion_m, func, 0.0, temp);

	/* vektor * vektor */
	gsl_blas_ddot (temp, func, &z[i]);

	original_fcn[i] = a+b*x[i]*x[i];
	exp_fcn[i] = A1+A2*x[i]*x[i];
	top_limit[i] = exp_fcn[i] + 1.01*sqrt( z[i] * ( residuum/(float)(NPOINTS-NPARAM)) );
	bot_limit[i] = exp_fcn[i] - 1.01*sqrt( z[i] * ( residuum/(float)(NPOINTS-NPARAM)) );

	//printf ("%f %f %f %f %f %f\n" , x[i], y[i], original_fcn[i], exp_fcn[i], top_limit[i], bot_limit[i]);
	}
	
	gsl_vector_free (temp);
	gsl_vector_free (func);	
	gsl_matrix_free (inversion_m);

j=0;
for (i=0; i<NPOINTS; i++)
	{
	if ( original_fcn[i] < top_limit[i] && original_fcn[i] > bot_limit[i] )
		j++;
	}

if (j==101)
	suc_line++;


fprintf (intregfunc ,"%d %f 0.683\n", run+1, (float)suc_line/(float)(run+1) );

}

fclose (intregfunc);
fclose (parametersprob);

return 0;
}


