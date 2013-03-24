#include "sipsol.c"
#include <math.h>

/* This program computes two dimensional laplace exuation in area [0,1]x[0,1] with boundary conditions: 
 *	u(x,0) = exp(−2x),
 *	u(0,y) = cos(2y),
 *	u(x,1) = exp(−2x) cos(2),
 *	u(1,y) = exp(−2) cos(2y).
 */

//#define NET_SIZE 100
//#define AREA_SIZE 1


int main()
{
long NET_SIZE=400;
long AREA_SIZE=1;
 
long n=(NET_SIZE-1)*(NET_SIZE-1); //we don't compute at the boundaries
long nx=(NET_SIZE-1);
long maxint=10000;
long dimension=n*n;

vector b={}, x={}, at={}, al={}, ar={}, ab = {};

double alpha=0.992;
double eps=1e-12;

int l;
double h=(double)AREA_SIZE/(double)NET_SIZE;
double norm=0.25;

/*initialize variables for sipsol*/
for (l=1; l<=n; l++)
	{
	at[l]=-0.25;
	if(l>nx) ab[l]=-0.25;
	if(l%nx==0) ar[l]=0.0; else ar[l]=-0.25;
	if((l-1)%nx==0) al[l]=0.0; else al[l]=-0.25;
	x[l]=0.0; //uniform starting estimate
	
	/*initialize right side of the equation*/
	if( l<=nx ) 		b[l] += norm*exp(-2.0*(double)l*h); //bottom boundary condition
	if( (l-1)%nx==0 )	b[l] += norm*cos(2.0*floor((double)l/(double)nx + 1.0)*h); //left boundary condition
	if( l%nx==0 ) 		b[l] += norm*exp(-2.0)*cos(2.0*floor((double)(l-1)/(double)nx + 1.0)*h); //right boundary condition
	if( l>(nx-1)*nx ) b[l] += norm*cos(2.0)*exp(-2.0*((double)((l-1)%nx)+1.0)*h); //top boundary condition
	}



Sipsol(n, nx-1, maxint, at, al, ar, ab, &b, &x, alpha, eps);

/*
for (l=1; l<=n; l++)
	{
	int i;
	for (i=1; i<=n; i++)
		{
		if(l==i) printf ("1.00 ");
		else if(i-1==l && i%nx!=1) printf ("-0.25 ");
		else if(i-nx==l) printf ("-0.25 ");
		else if(l-nx==i) printf ("-0.25 ");
		else if(l-1==i && i%nx!=0) printf ("-0.25 ");
		else printf ("0.00 ");
		}
	printf ("\n");
	}
*/


double c,d;
for (l=1; l<=n; l++)
	{
	c=(l-1)%nx;
	d=floor((double)(l-1)/(double)nx);
//	printf("%e %e %e\n",(c+1.0)*h, (d+1.0)*h ,x[l]);
//	printf("%e %e %e\n",(c+1.0)*h, (d+1.0)*h ,x[l]- cos(2*(d+1.0)*h)*exp(-2*(c+1.0)*h));
	if( ((c+1.0)*h) > 0.49999 && ((c+1.0)*h) < 0.50001 && ((d+1.0)*h) > 0.49999 && ((d+1.0)*h) < 0.50001 )
		printf("%e %e %e\n",(c+1.0)*h, (d+1.0)*h ,x[l]- cos(2*(d+1.0)*h)*exp(-2*(c+1.0)*h));
	//if(b[l]!=0.0) printf("%f %f %f\n",(c+1.0)*h, (d+1.0)*h ,b[l]);
	//printf("%f \n",b[l]);
	}


return 0;
}
