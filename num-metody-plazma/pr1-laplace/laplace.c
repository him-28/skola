#include "sipsol.c"
#include <math.h>

/* This program computes two dimensional laplace exuation in area [0,1]x[0,1] with boundary conditions: 
 *	u(x,0) = exp(−2x),
 *	u(0,y) = cos(2y),
 *	u(x,1) = exp(−2x) cos(2),
 *	u(1,y) = exp(−2) cos(2y).
 */

#define NET_SIZE 100
#define AREA_SIZE 1


int main()
{
long int n=(NET_SIZE-1)*(NET_SIZE-1); //we don't compute at the boundaries
long int nx=(NET_SIZE-1);
long int maxint=10000;

vector b, x, at, al, ar, ab;

double alpha=0.9;
double eps=0.000000000000001;

int l;
double h=(double)AREA_SIZE/(double)NET_SIZE;
double norm=h*h*0.25;

/*initialize variables for sipsol*/
for (l=0; l<n; l++)
	{
	at[l]=ab[l]=-0.25;
	if(l+1%nx==0) ar[l]=0.0; else ar[l]=-0.25;
	if(l+1%nx==0) al[l]=0.0; else al[l]=-0.25;
	x[l]=0.0; //uniform starting estimate
	b[l]=0.0;
	
	/*initialize right side of the equation*/	
	if( l<nx ) 			b[l] += norm*exp(-2.0*((double)l+1.0)*h); //bottom boundary condition
	if( l%nx==0 )		b[l] += norm*cos(2.0*floor((double)l/(double)nx + 1.0)*h); //left boundary condition
	if( (l+1)%nx==0 ) b[l] += norm*exp(-2.0)*cos(2.0*floor((double)l/(double)nx + 1.0)*h); //right boundary condition
	if( l>=(nx-1)*nx ) b[l] += norm*cos(2.0)*exp(-2.0*((double)(l%nx)+1.0)*h); //top boundary condition
	}

/*
for (l=0; l<n; l++)
	{
	if(b[l]!=0.0)
	printf("%d %f\n",l,b[l]);
	}
*/


Sipsol(n, nx, maxint, at, al, ar, ab, &b, &x, alpha, eps);


double c,d;
for (l=0; l<n; l++)
	{
	c=l%nx;
	d=floor((double)(l)/(double)nx);
	printf("%f %f %f\n",(c+1.0)*h, (d+1.0)*h ,x[l]);
	//if(b[l]!=0.0) printf("%f %f %f\n",(c+1.0)*h, (d+1.0)*h ,b[l]);
	}


return 0;
}
