#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <unistd.h>
#include <string.h>

/*some elementary constants*/
#define K_B 1.3806503e-23 
#define PI 3.14159265
#define ME 9.10938188e-31
#define ELM 1.60217646e-19

int main( int argc, char *argv[] )
{
	/*some reasonable default electron temperature (3eV)*/
	double T = 34800.0;
	
	int c;
	/* vstup z příkazové řádky */
	while ((c = getopt (argc, argv, "T:")) != -1)
		switch (c)
			{
			case 'T':
				T = strtod(optarg, 0);
				break;
			case '?':
			  if (optopt == 'T')
			    fprintf (stderr, "Parametr -%c vyžaduje argument.\n", optopt);
			  else if (isprint (optopt))
			    fprintf (stderr, "Neznámý přepínač `-%c'.\n", optopt);
			  else
			    fprintf (stderr, "Unknown option character `\\x%x'.\n", optopt);
				return 1;
			default:
				//print_help();
				return 0;
			}

/*experimental crossection coeficients*/
double sigmaAr_e[24][2]=
{{0.0001, 0.0},
{2.0, 0.0},
{4.0, 0.0},
{6.0, 0.0},
{8.0, 0.0},
{10.0, 0.0},
{11.0, 0.0},
{12.0, 0.0},
{13.0, 0.0},
{13.47, 0.0},
{14.0, 0.77},
{15.0, 2.23},
{16.0, 3.7},
{17.0, 5.16},
{18.0, 6.62},
{19.0, 8.08},
{20.0, 9.54},
{21.0, 11.0},
{25.0, 10.5},
{30.0, 10.0},
{38.46, 8.75},
{57.69, 7.5},
{73.07, 6.89},
{100.0, 6.13}};

double sigmaO_e[31][2]=
{{0.0001, 0.0},
{2, 0.0},
{4, 0.0},
{6, 0.0},
{8, 0.0},
{10, 0.0},
{10.95, 0.0},
{11.45, 1.13},
{12.45, 1.73},
{13.45, 3.45},
{14.45, 5.55},
{15.45, 7.13},
{16.45, 8.25},
{17.45, 9.75},
{18.45, 10.5},
{19.45, 11.3},
{20.45, 11.6},
{21.45, 12.0},
{22.45, 12.0},
{23.45, 12.0},
{24.45, 12.0},
{26.45, 11.8},
{28.45, 11.6},
{31.45, 11.3},
{36.45, 10.9},
{41.45, 10.5},
{51.45, 9.37},
{61.45, 7.88},
{71.45, 6.98},
{81.45, 6.3},
{91.45, 6.0}};

double sigmaO_de[26][2]=
{{0.0001, 0.0},
{2.0, 0.0},
{4.0, 0.0},
{6.0, 0.0},
{8.0, 0.0},
{10.0, 0.0},
{12.0, 0.0},
{14.0, 0.0},
{16.0, 0.0},
{17.0, 1.25},
{18.0, 2.5},
{19.0, 3.75},
{20.0, 5.0},
{21.39, 6.0},
{22.89, 7.27},
{24.5, 8.41},
{26.21, 9.61},
{28.05, 10.5},
{30.0, 11.7},
{35.0, 13.4},
{40.0, 14.5},
{50.0, 16.6},
{60.0, 18.6},
{70.0, 19.5},
{80.0, 20.0},
{90.0, 20.4}};

	double const k =  pow (2.0, 1.5) / ( sqrt(PI) * pow (K_B, 1.5) * pow (T, 1.5) * sqrt(ME) );

	int i;
	double kAr_e = 0.0;
	double kO_e = 0.0; 
	double kO_de = 0.0;
	double E, dE, ds;


	for (i=0; i<24 ; i++ ) //FIXME: hardcoded sizes
		{
	
		if(i==0)
			{
			dE = sigmaAr_e[1][0] - sigmaAr_e[0][0];
			}
		else if ( i==23 )
			{
			dE = sigmaAr_e[i][0] - sigmaAr_e[i-1][0];
			}
		else 
			{
			dE = ( sigmaAr_e[i+1][0] - sigmaAr_e[i-1][0] )/2.0;
			}
		
		dE *= ELM;
		E = sigmaAr_e[i][0] * ELM;

		ds = k * exp( -E/(K_B * T) ) * sigmaAr_e[i][1] * 1.0e-22 * E * dE; 
		
		kAr_e += ds;
	
		} 


	for (i=0; i<31 ; i++ )
		{
	
		if(i==0)
			{
			dE = sigmaO_e[1][0] - sigmaO_e[0][0];
			}
		else if ( i==30 )
			{
			dE = sigmaO_e[i][0] - sigmaO_e[i-1][0];
			}
		else 
			{
			dE = ( sigmaO_e[i+1][0] - sigmaO_e[i-1][0] )/2.0;
			}
		
		dE *= ELM;
		E = sigmaO_e[i][0] * ELM;

		ds = k * exp( -E/(K_B * T) ) * sigmaO_e[i][1] * 1.0e-22 * E * dE; 
		
		kO_e += ds;
	
		} 


	for (i=0; i<26 ; i++ )
		{
	
		if(i==0)
			{
			dE = sigmaO_de[1][0] - sigmaO_de[0][0];
			}
		else if ( i==25 )
			{
			dE = sigmaO_de[i][0] - sigmaO_de[i-1][0];
			}
		else 
			{
			dE = ( sigmaO_de[i+1][0] - sigmaO_de[i-1][0] )/2.0;
			}
		
		dE *= ELM;
		E = sigmaO_de[i][0] * ELM;

		ds = k * exp( -E/(K_B * T) ) * sigmaO_de[i][1] * 1.0e-23 * E * dE; 
		
		kO_de += ds;
	
		} 


	printf ("Rychlostní konstanty:\n");
	printf ("Pro teplotu elektronů T = %.2f K\n", T);
	printf ("kAr_e = %.2e cm3 s-1\n", kAr_e*1e6);
	printf ("k0_e = %.2e cm3 s-1\n", kO_e*1e6);
	printf ("k0_de = %.2e cm3 s-1\n", kO_de*1e6);

	return 0;	
}
