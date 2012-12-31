#include <stdio.h>
#include <stdlib.h>
#include <gsl/gsl_rng.h>
#include <gsl/gsl_math.h>
#include <assert.h>

#define M_E 9.10938291e-31
#define M_HE 6.642155684e-27
#define K_B 1.3806503e-23
#define P 1.0e3
#define Q_E 1.602e-19

#define POCET_SRAZEK 100000000
#define POCET_ELEKTRONU 20
#define TOWNSENDS 24.0

typedef struct v6 *uvec6;

typedef struct v6 {
	double x;
	double y;
	double z;
	double vx;
	double vy;
	double vz;
} vec6;

typedef struct v3 *uvec3;

typedef struct v3 {
	double x;
	double y;
	double z;
} vec3;

double absv3 (double a, double b, double c)
{
	return sqrt ( a * a + b * b + c * c);
}

double absv2 (double a, double b)
{
	return sqrt ( a * a + b * b );
}

void nova_pozice ( uvec6 s_poz, uvec3 f, double t)  
{
	s_poz->x += s_poz->vx * t + 0.5 * ( f->x / M_E ) * t * t;
	s_poz->y += s_poz->vy * t + 0.5 * ( f->y / M_E ) * t * t;   
	s_poz->z += s_poz->vz * t + 0.5 * ( f->z / M_E ) * t * t;

	s_poz->vx += ( f->x / M_E ) * t;
	s_poz->vy += ( f->y / M_E ) * t;   
	s_poz->vz += ( f->z / M_E ) * t;  
} 

void srazka ( uvec6 e, /*uvec6, N 0K not moving ionts */ double ztrata_e, gsl_rng * r )
{
	vec3 g1, g2, vN;

	double cos_chi= 1 - 2 * gsl_rng_uniform (r);
	double sin_chi= sqrt( 1 - cos_chi * cos_chi);
	double psi= 2 * M_PI * gsl_rng_uniform (r);

	g1.x = e->vx;
	g1.y = e->vy;
	g1.z = e->vz;

	double absg1 = absv3 ( g1.x, g1.y, g1.z );

	double energy1 = 0.5 * M_E * absg1 * absg1;

	//printf ("absg1^2: %e ztrata_e : %e ", absg1* absg1 , 2 * ztrata_e * ( ( M_E + M_HE ) / ( M_E * M_HE ) ) );

	double absg2a = sqrt( g1.x * g1.x + g1.y * g1.y + g1.z * g1.z - 2 * ztrata_e * ( ( M_E + M_HE ) / ( M_E * M_HE ) ) );

	g2.x = g1.x * cos_chi + absv2( g1.y, g1.z ) * sin_chi * sin( psi ) ;  
	g2.y = g1.y * cos_chi + sin_chi * ( absg1 * g1.z * cos( psi ) - g1.x * g1.y * sin( psi) ) / absv2( g1.y, g1.z ); 
	g2.z = g1.z * cos_chi - sin_chi * ( absg1 * g1.y * cos( psi ) + g1.x * g1.z * sin( psi) ) / absv2( g1.y, g1.z ); 

	double absg2b = absv3 ( g2.x, g2.y, g2.z );

	//printf ("první verze: %e druhá verze:  %e \n", absg2a, absg2b);

	//Nové rychlosti elektronu
	e->vx = ( M_E * e->vx ) / ( M_E + M_HE ) + ( M_HE / ( M_E + M_HE ) ) * g2.x * ( absg2a / absg2b ) ; //FIXME: je tam plus nebo minus?
	e->vy = ( M_E * e->vy ) / ( M_E + M_HE ) + ( M_HE / ( M_E + M_HE ) ) * g2.y * ( absg2a / absg2b ) ; 
	e->vz = ( M_E * e->vz ) / ( M_E + M_HE ) + ( M_HE / ( M_E + M_HE ) ) * g2.z * ( absg2a / absg2b ) ; 

	//Nevé rychlosti neutrálu (pro kontrolu)
	vN.x = ( M_E * e->vx ) / ( M_E + M_HE ) - ( M_E / ( M_E + M_HE ) ) * g2.x * ( absg2a / absg2b ) ; 
	vN.y = ( M_E * e->vy ) / ( M_E + M_HE ) - ( M_E / ( M_E + M_HE ) ) * g2.y * ( absg2a / absg2b ) ; 
	vN.z = ( M_E * e->vz ) / ( M_E + M_HE ) - ( M_E / ( M_E + M_HE ) ) * g2.z * ( absg2a / absg2b ) ; 

	//Celková energie po srážce pro kontrolu
	double energy2 = 0.5 * M_HE * ( vN.x * vN.x + vN.y * vN.y + vN.z * vN.z ) + 0.5 * M_E * ( e->vx * e->vx + e->vy * e->vy + e->vz * e->vz );

	//printf ("Energie před %e eV energie po: %e eV\n", energy1 / Q_E , energy2 / Q_E );

}


int main () 
{

	/*Inicializace generátoru pseudonáhodných čísel*/
	const gsl_rng_type * T;
	gsl_rng * r;
	gsl_rng_env_setup();
	T = gsl_rng_default;
	r = gsl_rng_alloc (T);

	/*Koncentrace při zadanám tlaku*/
	double n,t,v,C,emax,vmax, temp, energyeV, sumt, ezstart;
	n = P / ( 300.0 * K_B );

	/*Ez je dopočítáno aby E/n = 24Td (zadání)*/
	vec3 F;
	uvec3 uF = &F;
	F.x = 0.0;
	F.y = 0.0;
	F.z = TOWNSENDS*1e-21 * n * Q_E;
	
	printf ("n: %e, E:%e \n", n, F.z / Q_E);
	
	emax = 2.5; //eV
	vmax = sqrt( ( 2 * emax * Q_E ) / M_E );
	C = ( 6.0e-20 + 10*(emax - 0.2)*1.0e-20 ) * vmax; 
	printf ("Konstanta C:%e\n", C);

	double vstd[POCET_ELEKTRONU];
	double sumv = 0.0;
	
	vec6 e = { 0 };
	uvec6 ue = &e;
	
	for ( int k = 0; k < POCET_ELEKTRONU; k++){

		e.x=0.0;
		e.y=0.0;
		e.z=0.0;
		e.vx=0.0;
		e.vy=0.0;
		e.vz=0.0;
		sumt = 0.0;
		
		for ( int i = 0; i < POCET_SRAZEK; i++ ) {

			t = -log (gsl_rng_uniform (r)) / ( n * C );
			//printf ("čas: %e\n",t);
			if (i >= POCET_SRAZEK/10 )
				sumt += t;
			if (i == POCET_SRAZEK/10)
				ezstart = e.z;
			
			nova_pozice ( ue, uF, t );
		
			v = absv3 ( e.vx, e.vy, e.vz );
			energyeV = ( 0.5 * M_E * v * v ) / Q_E;
			//assert ( v < vmax ); //musíme zvětšit C

			//printf ("Před srážkou: vx:%e vy:%e vz:%e\n", e.vx, e.vy, e.vz);
			temp = gsl_rng_uniform (r) * ( C / v );				
			if ( temp < 6.0e-20 ) {
				//printf ("Pružná srážka\n");
				srazka ( ue, 0.0, r );
			}
			else if ( energyeV > 0.20 && temp < 6.0e-20 + 10 * (energyeV - 0.2)* 1.0e-20 ) {
				//printf ("Nepružná srážka\n");
				srazka ( ue, 0.20 * Q_E , r );
			}
			else {
				//printf ("Fiktivní srážka\n");
			}
			//printf ("Po srážce: vx:%e vy:%e vz:%e\n", e.vx, e.vy, e.vz);
		}
	
	printf ("Elektron číslo:%i, driftová rychlost: %e\n", k+1, ( e.z - ezstart ) / sumt );
	
	vstd[k] = ( e.z - ezstart ) / sumt;
	sumv += ( e.z - ezstart ) / sumt;
	
	}
	
	double avgv = sumv/(double)POCET_ELEKTRONU;
	sumv = 0.0;
	
	for (int i = 0; i < POCET_ELEKTRONU; i++){
		sumv += (vstd[i] - avgv)*(vstd[i] - avgv);
	}
	double prumerv = sqrt(sumv/(double)(POCET_ELEKTRONU - 1));
	
	printf ("\nVýsledek pro %i elektronů a %i srážek\n", POCET_ELEKTRONU, POCET_SRAZEK);
	printf ("Průměrná driftová rychlost %e, stdev: %e\n", avgv, prumerv );

	gsl_rng_free (r);

	return 0;
}
