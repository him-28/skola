#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

/*acually fix this, so we just read all this data once and pass it in parameters top the functions */
void get_r (double l[1500],double y[1500] )
{
	rewind (stdin);

	int i=0;
	float a,b,c,d,e,f,g;

	while ( scanf("%d %f %f %f %f %f %e", &f, &a, &b, &c, &d, &e, &g) > 0 )
			{
			l[i]=a;
			y[i]=c;
			i++;
			}
}

/* core math, all other functions are just wrappers to match GSL syntax*/
double Refl (double A, double B, double d, double l, double alpha, double beta)
{
	gsl_complex imunit, one;
	imunit = gsl_complex_rect (0.0, 1.0);
	one = gsl_complex_rect (1.0, 0.0);

	gsl_complex ns, n0, nv, r1, r2, fi, eifi, r;
	
	ns = get_ns ( l );

	n0 = gsl_complex_rect (1.0, 0.0); //vacuum, no absorption
	nv = gsl_complex_rect ( A + B/(l*l*1.0e-18) , alpha*exp( - beta * l * 1.0e-9 ) ); //2 parameters Cauchy formula, 

	r1 = gsl_complex_div (gsl_complex_sub(n0 , nv) , gsl_complex_add(n0 , nv) );
	r2 = gsl_complex_div (gsl_complex_sub(nv , ns) , gsl_complex_add(nv , ns) );

	fi = gsl_complex_mul_real( nv , (4.0 * 3.14 * d)/l );

	eifi = gsl_complex_exp ( gsl_complex_mul ( imunit, fi ) );

	r = gsl_complex_div (
			gsl_complex_add( r1, gsl_complex_mul ( r2, eifi ) ),
			gsl_complex_add( one, gsl_complex_mul ( gsl_complex_mul ( r1, r2 ), eifi ) ) 
			 );

	double R = gsl_complex_abs2 ( r );
	
	return R;
	}

void print_help()
	{
	printf ("Argumenty:\n -A -B [parametry Cauchyho vzorce n = A + B/lambda^2] \n -d [tloušťka vrstvy]\n -a -b [parametry extinkčního koeficinetu k = a*exp(-b*lambda)]\n");
	}


