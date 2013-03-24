

//#include "dopri5.h"
#include "dopri5.c"
#include <gnuplot.h>
#define DIFUSION 2000
#define ALPHA 2e-7
#define DIM 251




void fcn (unsigned n, double x, double *y, double *f)
	{
	
	unsigned i;
	double h = 25.0 / (double)(n-1);
	double a,b,c;
		
	f[0] =  6*DIFUSION*((y[1]-y[0])/(h*h)) - ALPHA*y[0]*y[0]; 
	
	for (i = 1;i<n;i++)
			{
			a = DIFUSION*((y[i+1] + y[i-1] - 2*y[i])/(h*h));
			b = DIFUSION*((y[i+1] - y[i-1])/(h*h*i));
			c = ALPHA*y[i]*y[i];
			if(i == n-1)	f[i] = 0.0;
			else f[i]= a + b - c;
			
			}
	}

void mysolout(long nr, double xold, double x, double* y, unsigned n, int* irtrn)
	{
	int i;
	double h = 25.0 / (double)(DIM-1);
	for (i = 1;i<DIM;i++)
 	{
	 printf ("%e %e %e \n", x, h*i,y[i]);
	} 
	}

int main()
	{
	int vyst,i;
	double h = 25.0 / (double)(DIM-1);
	double y[DIM] = {},z[DIM] = {}, x, xmax;
	double rtoler=1e-2,atoler=1e-2;

	for (i = 0;i<DIM;i++)
		{
		if (h*i < 10.0) y[i]=2e11;
		else y[i]=0.0;
		}
	
	vyst = dopri5(
		DIM,/* dimension of the system <= UINT_MAX-1*/
		&fcn, /* function computing the value of f(x,y) */
 		0.0, /* initial x-value */
		&y[0],  /* initial values for y */
		0.002, /* final x-value (xend-x may be positive or negative) */
		&rtoler,  /* relative error tolerance */
		&atoler,  /* absolute error tolerance */
		0,      /* switch for rtoler and atoler */
		NULL,//&mysolout, /* function providing the numerical solution during integration */
		0,        /* switch for calling solout */
  		NULL,   /* messages stream */
		0,   /* rounding unit */
		0,    /* safety factor */
		0,     /* parameters for step size selection */
		0,
		0,     /* for stabilized step size control */
		0,     /* maximal step size */
		0,        /* initial step size */
		0,      /* maximal number of allowed steps */
		0,       /* switch for the choice of the coefficients */
		0,     /* test for stiffness */
		0, /* number of components for which dense outpout is required */ 
 		0, /* indexes of components for which dense output is required, >= nrdens */
 		0  /* declared length of icon */
	);


if(vyst!=1)
printf ("//výstup: %d \n\n",vyst);

else{

for (i = 1; i<DIM; i++)
 {
 printf ("%e %e \n", (double)i ,y[i]);
 }
}


}

