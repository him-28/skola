#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <gsl/gsl_linalg.h>
#include <gsl/gsl_blas.h>
#include <string.h>
#include <unistd.h>

#define NPARAM 2
#define MAXLENGTH 100

int main (int argc, char *argv[])
{

int c,i,j,k,run, npoints, suc_a=0, suc_b=0, suc_line=0, suc_stdev=0;
char word[MAXLENGTH];

FILE *intregfunc, *parametersprob, *graph, *stdevprob;
intregfunc = fopen("probability_of_regresion_funcion.txt","w");
parametersprob = fopen("probability_of_parameters.txt","w");
graph = fopen("funkce+fit+odhady.txt","w");
stdevprob = fopen("probability_of_stdev.txt","w");

gsl_matrix *m = gsl_matrix_calloc (2, 2);
gsl_matrix *inversion_m = gsl_matrix_calloc (2, 2);
gsl_permutation * p = gsl_permutation_alloc (2);
int signum;

/* rozumné počáteční parametry*/
int maxrun=10;
double a = 1.0;
double b = 2.0;
double stdev = 5;

double stdev_exp, stdev_min, stdev_max;
double A[2][2]={}, B[2][2]={}, R[2]={}, n;
double A1, A2;
double residuum;

if (argv[1]==NULL)
	{
	print_help();
	return 0;
	}

/* vstup z příkazové řádky */
while ((c = getopt (argc, argv, "a:b:l:s:n:")) != -1)
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
		case 'n':
		  npoints = strtol(optarg, 0, 10);
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

double x[npoints],y[npoints];

/* matice A (nezáleží na y)*/
for (i=0; i<npoints; i++)
	{
	x[i] = (double)i*(10.0/(double)(npoints-1));
	A[0][0] += 1;
	A[0][1] += x[i]*x[i];
	A[1][0] += x[i]*x[i];
	A[1][1] += x[i]*x[i]*x[i]*x[i];
	}

gsl_matrix_set (m, 0, 0, A[0][0]);
gsl_matrix_set (m, 0, 1, A[0][1]);
gsl_matrix_set (m, 1, 0, A[1][0]);
gsl_matrix_set (m, 1, 1, A[1][1]);
gsl_matrix_fprintf (stdout, m, "%e");

/* LU dekompozice*/
gsl_linalg_LU_decomp (m, p, &signum);

/*compute iverse matrix*/
gsl_linalg_LU_invert (m, p, inversion_m );

double sa = gsl_matrix_get(inversion_m, 0,0);
double sb = gsl_matrix_get(inversion_m, 1,1);

gsl_matrix_fprintf (stdout, inversion_m, "%e");



for (run=0; run<maxrun; run++)
	{
	residuum = 0.0;
	R[0] = 0.0;
	R[1] = 0.0;

	/* generování náhodných bodů a výpočet pravé strany*/
	for (i=0; i<npoints; i++)
		{
		y[i] = a + b*x[i]*x[i] + stdev*normal_float01();
		R[0] += y[i];
		R[1] += y[i]*x[i]*x[i];
		}

   double r_data[] = { R[0], R[1] };
     
	gsl_vector_view r	= gsl_vector_view_array (r_data, 2);
     
   gsl_vector *v = gsl_vector_alloc (2);
       
	/* řešení systému rovnic */
	gsl_linalg_LU_solve (m, p, &r.vector, v);
   A1 = gsl_vector_get(v, 0);
	A2 = gsl_vector_get(v, 1);

	gsl_vector_free (v);

	for (i=0; i<npoints; i++)
		{
		residuum += pow((y[i] -(A2*x[i]*x[i]) -A1), 2.0);  
		}

	stdev_exp = residuum/(float)(npoints-NPARAM);

	stdev_min = ( sqrt(stdev_exp) * sqrt(2*(npoints-NPARAM)) )/( sqrt(2*(npoints-NPARAM)-3) +1 );
	stdev_max = ( sqrt(stdev_exp) * sqrt(2*(npoints-NPARAM)) )/( sqrt(2*(npoints-NPARAM)-3) -1 );

//	stdev_min = (npoints-NPARAM)*stdev_exp/82.358;
//	stdev_max = (npoints-NPARAM)*stdev_exp/118.498;

	if( stdev_min < stdev && stdev_max > stdev )
		suc_stdev++;

	printf ("\n/********** %d *************/\n",run+1);
	printf ("residuální suma čtverců: %e\n", residuum);
	printf ("bodový odhad rozptylu:%f\n", sqrt(stdev_exp));
	printf ("intervalový odhad rozptylu: min: %f max: %f\n", stdev_min , stdev_max );

	double sigma_a = 1.01*sqrt(sa*stdev_exp);
	double sigma_b = 1.01*sqrt(sb*stdev_exp);
	printf ("a:%f +- %f\n", A1, sigma_a);
	printf ("b:%f +- %f\n", A2, sigma_b);

	if ( A1 < (a + sigma_a) && A1 > (a - sigma_a) )
		suc_a++;
	if ( A2 < (b + sigma_b) && A2 > (b - sigma_b) )
		suc_b++;

	fprintf (parametersprob ,"%d %f %f 0.683\n", run+1, ((float)suc_a)/((float)(run+1)), ((float)suc_b)/((float)(run+1)));
	fprintf (stdevprob ,"%d %f 0.683\n", run+1, ((float)suc_stdev)/((float)(run+1)) );


	double z[npoints], original_fcn[npoints], exp_fcn[npoints], top_limit[npoints], bot_limit[npoints];
	gsl_vector *temp = gsl_vector_calloc (2);
	gsl_vector *func = gsl_vector_calloc (2);

	// určení intervalových odhadů funkce
	for (i=0; i<npoints; i++)
	{

	gsl_vector_set (func, 0, 1.0);
	gsl_vector_set (func, 1, x[i]*x[i]);

	/* matice * vektor */
	gsl_blas_dgemv (CblasNoTrans, 1.0, inversion_m, func, 0.0, temp);

	/* vektor * vektor */
	gsl_blas_ddot (temp, func, &z[i]);

	original_fcn[i] = a+b*x[i]*x[i];
	exp_fcn[i] = A1+A2*x[i]*x[i];
	//FIXME: 
	top_limit[i] = exp_fcn[i] + 1.49*sqrt( z[i] * stdev_exp );
	bot_limit[i] = exp_fcn[i] - 1.49*sqrt( z[i] * stdev_exp );

	if (run==0)
		fprintf (graph ,"%f %f %f %f %f %f\n" , x[i], y[i], original_fcn[i], exp_fcn[i], top_limit[i], bot_limit[i]);
	}
	
	gsl_vector_free (temp);
	gsl_vector_free (func);	

	j=0;
	for (i=0; i<npoints; i++)
		{
		if ( original_fcn[i] < top_limit[i] && original_fcn[i] > bot_limit[i] )
			j++;
		}

	if (j==npoints)
		suc_line++;


	fprintf (intregfunc ,"%d %f 0.683\n", run+1, (float)suc_line/(float)(run+1) );

	}	

gsl_permutation_free (p);
gsl_matrix_free (m);
gsl_matrix_free (inversion_m);
fclose (intregfunc);
fclose (parametersprob);

return 0;
}


