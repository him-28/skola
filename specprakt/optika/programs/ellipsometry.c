#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <gsl/gsl_complex.h>
#include <gsl/gsl_complex_math.h>

#define MAXSIZE 1500
#define PI 3.14159265

int main()
{

	int i=0, f;
	float a,b,c,d,e;
	double l[MAXSIZE], rho_r[MAXSIZE], rho_i[MAXSIZE], angle[MAXSIZE], weight[MAXSIZE], angle_rad;
	FILE *e55, *e60, *e65, *e70, *e75;

	e55 = fopen("nke55.txt","w");
	e60 = fopen("nke60.txt","w");
	e65 = fopen("nke65.txt","w");
	e70 = fopen("nke70.txt","w");
	e75 = fopen("nke75.txt","w");	

	while ( scanf("%d %f %f %e %e %e", &f, &a, &b, &c, &d, &e) > 0 )
	{
		l[i]=a;
		angle[i]=b;
		rho_r[i]=c;
		rho_i[i]=d;
		i++;
	}


	gsl_complex imunit, one, rho, s, z, n[MAXSIZE], eps[MAXSIZE];

	imunit = gsl_complex_rect (0.0, 1.0);
	one = gsl_complex_rect (1.0, 0.0);

	for (i = 0; l[i] ; i++)
	{
		angle_rad = (angle[i]/180.0)* PI;
	
		rho = gsl_complex_rect ( rho_r[i], -rho_i[i] ); 

		s = gsl_complex_pow_real( gsl_complex_div ( gsl_complex_sub( one , rho) , gsl_complex_add( one , rho) ) , 2.0 );
		z = gsl_complex_sqrt( gsl_complex_add(one , gsl_complex_mul_real( s , tan( angle_rad ) * tan( angle_rad ) ) ) );
    
		n[i] = gsl_complex_mul_real( z, sin( angle_rad ) );
		eps[i] = gsl_complex_pow_real( n[i] , 2.0 );
		

		if ( abs(angle[i]-55.0) < 1e-5 )
			fprintf (e55, "%f %f %f %f %f\n", l[i], GSL_REAL (n[i]),  GSL_IMAG (n[i]), GSL_REAL (eps[i]),  GSL_IMAG (eps[i]) );
		else if ( abs(angle[i]-60.0) < 1e-5 )
			fprintf (e60, "%f %f %f %f %f\n", l[i], GSL_REAL (n[i]),  GSL_IMAG (n[i]), GSL_REAL (eps[i]),  GSL_IMAG (eps[i]) );
		else if ( abs(angle[i]-65.0) < 1e-5 )
			fprintf (e65, "%f %f %f %f %f\n", l[i], GSL_REAL (n[i]),  GSL_IMAG (n[i]), GSL_REAL (eps[i]),  GSL_IMAG (eps[i]) );
		else if ( abs(angle[i]-70.0) < 1e-5 )
			fprintf (e70, "%f %f %f %f %f\n", l[i], GSL_REAL (n[i]),  GSL_IMAG (n[i]), GSL_REAL (eps[i]),  GSL_IMAG (eps[i]) );
		else if ( abs(angle[i]-75.0) < 1e-5 )
			fprintf (e75, "%f %f %f %f %f\n", l[i], GSL_REAL (n[i]),  GSL_IMAG (n[i]), GSL_REAL (eps[i]),  GSL_IMAG (eps[i]) );
	}

	fclose(e55);
	fclose(e60);
	fclose(e65);
	fclose(e70);
	fclose(e75);
	
	return 0;	
}
