#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>

#include <glib.h>

#include <gsl/gsl_cdf.h>

#define SIGMA1_CONF 0.682689492

typedef struct {
	double E;
	double R1;
	double R2;
	double R3;
} input_line;

double t_dist_coef( double conf, double nu )
{
	return gsl_cdf_tdist_Pinv( 0.5 + conf / 2.0 , nu);
}

int comparef (gconstpointer ia, gconstpointer ib) 
{
	input_line * a = (input_line *)ia;
	input_line * b = (input_line *)ib;

	if ( a->E < b->E )
		return 1;
	else if ( a->E > b->E )
		return -1;
	else
		return 0;
}

int main(int argc, char *argv[])
{
	if(argc < 2){
		fprintf(stderr, "Error: spec-elettra: input file unspecified!\n");
		return 1;
	}
	
	/*Open file*/
	FILE * input_file;
	if((input_file = fopen( argv[1], "r")) == NULL ){
		fprintf(stderr, "Error: Opening file %s failed\n", argv[1]);
		return 1;
	}

	GArray * input_data;
	input_data = g_array_new (TRUE, TRUE, sizeof(input_line)); 

	input_line L;
	double E[3];
	while(fscanf(input_file, "%le %le %le %le %le %le", &E[0], &L.R1, &E[1], &L.R2, &E[2], &L.R3) == 6){
		/* Just double check those are the same */
		assert(E[0] == E[1] && E[1] == E[2]);
		/* Also check for strange values*/
		if(L.R1 > 1.0 || L.R1 < 0.0 || 
			L.R2 > 1.0 || L.R2 < 0.0 || 
			L.R3 > 1.0 || L.R3 < 0.0 || 
			isnan(L.R1) || isnan(L.R2) || isnan(L.R3)){
			fprintf(stderr, "warning: invalid input value at %.1f eV, skipping (R1:%.3f R2:%.3f R3:%.3f)\n", E[0], L.R1, L.R2, L.R3);
			continue;
		}
		/* And those are not! */
		assert(L.R1 != L.R2 || L.R2 != L.R3);
		L.E = E[0];
		g_array_append_val(input_data, L);
	}

	g_array_sort(input_data, &comparef);

	for(unsigned i = 0; i < input_data->len; i++){
		double lambda, R, sigma, w;
		L = g_array_index(input_data, input_line, i);
		R = (L.R1 + L.R2 + L.R3) / 3.0;
		//printf("%f %f %f\n", L.R1, L.R2, L.R3);
		sigma = sqrt((
					(R - L.R1) * (R - L.R1) + 
					(R - L.R2) * (R - L.R2) + 
					(R - L.R3) * (R - L.R3)) / 2.0) * t_dist_coef(SIGMA1_CONF, 2.0);
		w = 1.0 / (sigma * sigma);
		/* FIXME: check for w being too big and use some max value instead */	
		//printf("sigma: %f, w: %f\n", sigma, w);
		lambda =  1239.852066 / L.E;
		printf("%i\t%.6f\t%f\t%.6f\t%.6f\t%.6f\t%.6f\n", 350001, lambda, 5.0, R, 0.0, 0.0, w);
	}	

	g_array_free(input_data, TRUE);
	fclose(input_file);	
	
	return 0;
}
