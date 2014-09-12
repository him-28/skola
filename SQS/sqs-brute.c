#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <time.h>

#include <gsl/gsl_rng.h>

#ifndef M_PI
#    define M_PI 3.14159265358979323846
#endif

#define DIST_MARGIN 1e-5

gsl_rng * r;

int compare_double(const void * a, const void * b)
{
	double A = *(double *)a;
	double B = *(double *)b;

	if (A < B) return -1;
	else if (A > B) return 1;
	else return 0;
}

int next_sqs_position(int *Apositions, int nAatoms, int n_sqs_atoms){
	if(Apositions[nAatoms-1] < n_sqs_atoms - 1){
		Apositions[nAatoms-1]++;
		return 1;
	}
	else {
		if(nAatoms - 1 > 0){
			if(!next_sqs_position(Apositions, nAatoms - 1, n_sqs_atoms - 1))
				return 0;
			Apositions[nAatoms - 1] = Apositions[nAatoms - 2] + 1;
			return 1;
		}
		else
			return 0;
	}
}

int random_sqs_position(int *Apositions, int nAatoms, int n_sqs_atoms){
	for(int j = 0; j < nAatoms; j++)
		Apositions[j] = -1;	

	int i = 0;
	while(i < nAatoms){
		Apositions[i] = gsl_rng_uniform_int(r, n_sqs_atoms);
		for(int j = 0; j < i; j++)
			if(Apositions[i] == Apositions[j])
				i--;
		i++;		
	}
	
	for(int j = 0; j < nAatoms; j++)	
		//printf("%i %i\n", j, Apositions[j]);

	return 1;
}

int isA(int *Apositions, int nAatoms, int n_sqs_atoms, int pos){
	pos = pos % n_sqs_atoms;
	for(int i = 0; i < nAatoms; i++)
		if(Apositions[i] == pos)
			return 1;
	return 0;
}

int main(int argc, char *argv[]){

	gsl_rng_default_seed = time(NULL);
	r = gsl_rng_alloc (gsl_rng_default);

	typedef enum {DEFAULT, VASP, WIEN2K} format;
	format input_format = VASP;
	format output_format = VASP;
	
	if(argc < 2){
		fprintf(stderr, "sqs: input file unspecified!\n");
		return 1;
	}
	
	/* open input file */
	FILE * input_file;
	if((input_file = fopen( argv[1], "r")) == NULL ){
		fprintf(stderr, "Error: Opening file %s failed\n", argv[1]);
		return 1;
	}

	double a, b, c, alpha, beta, gamma;
	double u1[3], u2[3], u3[3];

	double pos[3];
	char atomname[20], sqs_atomname[20], sqs_atomname_old[20];
	typedef struct {
		double v1;
		double v2;
		double v3;
		char name[20];
		int is_sqs;
		int atomtype;
	} input_atom;

	int atomtypes;
	input_atom *inat = NULL;
	int n_sqs_atoms_prim_cell = 0;
	int n_atoms_prim_cell = 0;

	int basis_is_cartesian = 0;
	double factor = 1.0;

	/* import cell parameters and basis vectors */
	if(input_format == DEFAULT){
		if(fscanf(input_file, "%le %le %le %le %le %le", &a, &b, &c, &alpha, &beta, &gamma) != 6 ||
			fscanf(input_file, "%le %le %le", &u1[0], &u1[1], &u1[2]) != 3 ||
			fscanf(input_file, "%le %le %le", &u2[0], &u2[1], &u2[2]) != 3 ||
			fscanf(input_file, "%le %le %le", &u3[0], &u3[1], &u3[2]) != 3){
			fprintf(stderr, "sqs: error while reading input file\n");
			return 1;
		}

		/* import primitive cell structure in own format*/
		for(int i = 0; fscanf(input_file, "%le %le %le %s", &pos[0], &pos[1], &pos[2], atomname) == 4; i++){
			inat = realloc(inat, (i + 1) * sizeof(input_atom));
			n_atoms_prim_cell++;
			inat[i].v1 = pos[0];
			inat[i].v2 = pos[1];
			inat[i].v3 = pos[2];
			printf("sqs: input atom %i at %.3f %.3f %.3f\n", i, inat[i].v1, inat[i].v2, inat[i].v3);
			strcpy(inat[i].name, atomname);
			if(strstr(atomname,",")){
				inat[i].is_sqs = 1;
				n_sqs_atoms_prim_cell++;
			}
			else
				inat[i].is_sqs = 0;
		}
	}
	else if(input_format == VASP){
		basis_is_cartesian = 1;

		char compound[100], components[100], numbers[100], coordinates[100];
		if(fgets(compound, 100, input_file) == NULL ||
			fscanf(input_file, "%le", &factor) != 1 ||
			fscanf(input_file, "%le %le %le", &u1[0], &u1[1], &u1[2]) != 3 ||
			fscanf(input_file, "%le %le %le", &u2[0], &u2[1], &u2[2]) != 3 ||
			fscanf(input_file, "%le %le %le\n", &u3[0], &u3[1], &u3[2]) != 3){
			fprintf(stderr, "sqs: error 1 while reading vasp file\n");
			return 1;
		}
		if(fgets(components, 100, input_file) == NULL ||
			fgets(numbers, 100, input_file) == NULL ||
			fgets(coordinates, 100, input_file) == NULL){
			fprintf(stderr, "sqs: error 2 while reading vasp file\n");
		}

		if(strstr(coordinates,"Direct") == NULL){
			fprintf(stderr, "sqs: error usopported coordinate system %s, use Direct\n", coordinates);
			return 1;
		}
		//printf("%f %f %f\n", u1[0], u1[1], u1[2]);
		//printf("%f %f %f\n", u2[0], u2[1], u2[2]);
		//printf("%f %f %f\n", u3[0], u3[1], u3[2]);
		//printf("%s|%s|%s|%s", compound, components, numbers, coordinates);

		struct {
			char name[10];
			char amount[10];
			int n;
		} comp[10];

		int i = 0;
		char *p_components = components, *p_numbers = numbers;
		for(i = 0; sscanf(p_components, "%s", &comp[i].name) == 1 && sscanf(p_numbers, "%s", &comp[i].amount) == 1; i++){
			p_components = strstr(components, comp[i].name) + strlen(comp[i].name);
			p_numbers = strstr(numbers, comp[i].amount) + strlen(comp[i].amount);
			sscanf(comp[i].amount, "%d", &comp[i].n); 
		}
		printf("sqs: found %i atom types:\n", i);
		for(int j = 0; j < i; j++)
			printf("%i: %s\n", j, comp[j].name);
		printf("sqs: which one you want to SQS:");
		int n_atom_sqs = -1, k = 0, l = 0;
		scanf("%i",&n_atom_sqs);
		printf("sqs: symbol of the replacement atom:");
		scanf("%s",sqs_atomname);

		strcpy(sqs_atomname_old, comp[n_atom_sqs].name);
		
		for(int j = 0; fscanf(input_file, "%le %le %le", &pos[0], &pos[1], &pos[2]) == 3; j++){
			
			inat = realloc(inat, (j + 1) * sizeof(input_atom));
			n_atoms_prim_cell++;
			inat[j].v1 = pos[0];
			inat[j].v2 = pos[1];
			inat[j].v3 = pos[2];
			printf("sqs: input atom %i at %.3f %.3f %.3f\n", j, inat[j].v1, inat[j].v2, inat[j].v3);
			inat[i].atomtype = k;
			strcpy(inat[j].name, comp[k].name);
			if(k == n_atom_sqs){
				inat[j].is_sqs = 1;
				n_sqs_atoms_prim_cell++;
			}
			else
				inat[j].is_sqs = 0;
			l++;
			if(l == comp[k].n){
				l = 0;
				k++;		
			}
		}
		atomtypes = k;
	}

	int ncelsa, ncelsb, ncelsc;
	double conc;
	printf("\nsqs: number of cells in direction a: ");
	scanf("%i", &ncelsa);
	printf("sqs: number of cells in direction b: ");
	scanf("%i", &ncelsb);
	printf("sqs: number of cells in direction c: ");
	scanf("%i", &ncelsc);
	printf("sqs: desired atomic concentration of atom type A: ");
	scanf("%le", &conc);
	int n_sqs_atoms = ncelsa * ncelsb * ncelsc * n_sqs_atoms_prim_cell;
	int nAatoms = round( conc * n_sqs_atoms );
	conc = (double)nAatoms/(double)n_sqs_atoms;
	printf("sqs: nearest possible concentration for selected supercell size is %f\n", conc);
	printf("sqs: we have a total of %i atoms of supercell\n", n_atoms_prim_cell * ncelsa * ncelsb * ncelsc);
	printf("sqs: %i of them are being SQS'd\n", n_sqs_atoms);
	printf("sqs: with A concentration of %.2f, %i of them are A type\n\n",  conc, nAatoms);

	/* convert angles to radians */
	alpha = (alpha / 180) * M_PI;
	beta = (beta / 180) * M_PI;
	gamma = (gamma / 180) * M_PI;

	/* precompute latice coordinates to cartesian transformation matrix */
	double T[3][3];

	if(basis_is_cartesian == 0){
		T[0][0] = a * ncelsa;
		T[0][1] = b * ncelsb * cos(gamma);
		T[0][2] = c * ncelsc * cos(beta);
		T[1][0] = 0;
		T[1][1] = b * ncelsb * sin(gamma);
		T[1][2] = c * ncelsc * (cos(alpha) - cos(beta) * cos(gamma)) / sin(gamma);
		T[2][0] = 0;
		T[2][1] = 0;
		T[2][2] = c * ncelsc * sqrt(1.0 - cos(alpha)* cos(alpha) - cos(beta) * cos(beta) 
					- cos(gamma) * cos(gamma) + 2 * cos(alpha) * cos(beta) * cos(gamma))
					 / sin(gamma);
	}
	else {
		T[0][0] = factor * u1[0] * ncelsa;
		T[0][1] = factor * u2[0] * ncelsb;
		T[0][2] = factor * u3[0] * ncelsc;
		T[1][0] = factor * u1[1] * ncelsa;
		T[1][1] = factor * u2[1] * ncelsb;
		T[1][2] = factor * u3[1] * ncelsc;
		T[2][0] = factor * u1[2] * ncelsa;
		T[2][1] = factor * u2[2] * ncelsb;
		T[2][2] = factor * u3[2] * ncelsc;
	}

	printf("Latice to cartesian transformation matrix\n");
	printf("%.3f %.3f %.3f\n", T[0][0], T[0][1], T[0][2]);
	printf("%.3f %.3f %.3f\n", T[1][0], T[1][1], T[1][2]);
	printf("%.3f %.3f %.3f\n\n", T[2][0], T[2][1], T[2][2]);

	typedef struct{
		double v1;
		double v2;
		double v3;
		char name[20];
	} atom_pos;
	atom_pos s_cell[n_sqs_atoms];
	int i = 0;

	/* generate the super cell */
	printf("Generated super cell:\n");
	for(int na = 0; na < ncelsa; na++){
		for(int nb = 0; nb < ncelsb; nb++){
			for(int nc = 0; nc < ncelsc; nc++){
				for(int n = 0; n < n_atoms_prim_cell; n++){
					if(inat[n].is_sqs){
						s_cell[i].v1 = (na + inat[n].v1) / ncelsa;
						s_cell[i].v2 = (nb + inat[n].v2) / ncelsb;
						s_cell[i].v3 = (nc + inat[n].v3) / ncelsc;
						strcpy(s_cell[i].name, inat[n].name);
						//printf("sqs: atom %2i at %.3f %.3f %.3f\n", i, s_cell[i].v1, s_cell[i].v2, s_cell[i].v3);
						i++;
					}
				}
			}
		}
	}

	i = 0;
	atom_pos large_s_cell[n_sqs_atoms * 27];
	/* generate the 3x3 super cell */
	//printf("Generated super cell:\n");
	for(int na = -1; na <= 1; na++){
		for(int nb = -1; nb <= 1; nb++){
			for(int nc = -1; nc <= 1; nc++){
				for(int n = 0; n < n_sqs_atoms; n++){
					//printf("%i %i %i %i", na, nb, nc, n);
					large_s_cell[i].v1 = na + s_cell[n].v1;
					large_s_cell[i].v2 = nb + s_cell[n].v2;
					large_s_cell[i].v3 = nc + s_cell[n].v3;
					strcpy(large_s_cell[i].name, s_cell[n].name);
					//printf("sqs: atom %2i at %.3f %.3f %.3f\n", i, large_s_cell[i].v1, large_s_cell[i].v2, large_s_cell[i].v3);
					i++;
				}
			}
		}
	}


	double distances[n_sqs_atoms][n_sqs_atoms * 27];
	double *dist_list = NULL;
	int dist_list_length = 0;

	//printf("\nDistance table\n");
	for(int i = 0; i < n_sqs_atoms; i++){
		for(int j = 0; j < n_sqs_atoms * 27; j++){

			double mindv1 = s_cell[i].v1 - large_s_cell[j].v1;
			double mindv2 = s_cell[i].v2 - large_s_cell[j].v2;
			double mindv3 = s_cell[i].v3 - large_s_cell[j].v3;

			/* transform to cartesian and compute distance */
			double x = T[0][0] * mindv1 + T[0][1] * mindv2 + T[0][2] * mindv3;
			double y = T[1][0] * mindv1 + T[1][1] * mindv2 + T[1][2] * mindv3;
			double z = T[2][0] * mindv1 + T[2][1] * mindv2 + T[2][2] * mindv3;
			distances[i][j] = sqrt(x * x + y * y + z * z);

			if(dist_list_length == 0){
				dist_list = realloc(dist_list, sizeof(double));
				dist_list[0] = distances[i][j];
				dist_list_length++;
			}
			else 
				for(int l = 0; l < dist_list_length; l++){
					if(fabs(dist_list[l] - distances[i][j]) < DIST_MARGIN)
						break;
					if(l == dist_list_length - 1){
						dist_list_length++;
						dist_list = realloc(dist_list, sizeof(double) * dist_list_length);
						dist_list[dist_list_length - 1] = distances[i][j];
					}
				}
			//printf("%f %f %f %f %f %f", s_cell[i].v1, s_cell[i].v2, s_cell[i].v3, large_s_cell[j].v1, large_s_cell[j].v2, large_s_cell[j].v3);
			//printf("%5.2f", distances[i][j]);
		}
		//printf("\n");
	}

	qsort(dist_list, dist_list_length, sizeof(double), compare_double);
	printf("Unique atomic distances: %i\n", dist_list_length);
	printf("Smallest 10 distances: %i\n", dist_list_length);
	for(int l = 1; l < 11; l++){
		printf("%.5f ", dist_list[l]);
	}
	printf("\n\n");

	int Apositions[nAatoms];
	for (int i = 0; i < nAatoms; i++)
		Apositions[i] = i;

	/* special cell from David rutile out_atomPositionsSQS_1
	Apositions[0] = 0;
	Apositions[1] = 3;
	Apositions[2] = 4;
	Apositions[3] = 6;
	Apositions[4] = 7;
	Apositions[5] = 8;
	Apositions[6] = 9;
	Apositions[7] = 11;*/

	/* special cell from David rutile out_atomPositionsSQS_2
	Apositions[0] = 0;
	Apositions[1] = 1;
	Apositions[2] = 3;
	Apositions[3] = 8;
	Apositions[4] = 9;
	Apositions[5] = 12;
	Apositions[6] = 13;
	Apositions[7] = 14;*/

/* special cell from David TiAlN out_atomPositionsSQS_1
	Apositions[0] = 22;
	Apositions[1] = 3;
	Apositions[2] = 4;
	Apositions[3] = 6;
	Apositions[4] = 7;
	Apositions[5] = 8;
	Apositions[6] = 10;
	Apositions[7] = 11;
	Apositions[8] = 17;
	Apositions[9] = 20;
	Apositions[10] = 21;
	Apositions[11] = 1;*/


	/* actually start SQS */
	/* try all possibilities for now, Monte Carlo later*/
	random_sqs_position(Apositions, nAatoms, n_sqs_atoms);

	struct {
		int Apositions[nAatoms];
		double match[8];
		double match_sum;
	} best_candidates[5];

	for(int i = 0; i < 5; i++)
		best_candidates[i].match_sum = 999.9;		

	int n_runs = 0;

	do {
		double match[dist_list_length];
		double match_sum = 0.0;

		for(int d = 1; d < 8/*dist_list_length*/; d++){
			int M = 0, NAB = 0;
			/* go over the table and find all pairs */
			for(int i = 0; i < n_sqs_atoms; i++){
				for(int j = 0; j < n_sqs_atoms * 27; j++){
					if(fabs(distances[i][j] - dist_list[d]) < DIST_MARGIN){
						M++;
						if(isA(Apositions, nAatoms, n_sqs_atoms, i) != isA(Apositions, nAatoms, n_sqs_atoms, j))
							NAB++;
					}
				}
			}
			M *= 2.0;
			match[d] = 1.0 - (NAB / (conc * (1.0 - conc) * M));
			match_sum += fabs(match[d]) * (1.0 + 2.0 * ((7.0 - d) / 7.0));
			//printf("%f ", match[d]);
		}

		if(match_sum <= best_candidates[0].match_sum){
			for(int i = 3; i >= 0; i--){
				for(int j = 0; j < nAatoms; j++)
					best_candidates[i+1].Apositions[j] = best_candidates[i].Apositions[j];
				for(int j = 1; j < 8; j++)
					best_candidates[i+1].match[j] = best_candidates[i].match[j];
				best_candidates[i+1].match_sum = best_candidates[i].match_sum;
			}
			for(int j = 0; j < nAatoms; j++)
				best_candidates[0].Apositions[j] = Apositions[j];
			for(int j = 1; j < 8; j++)
				best_candidates[0].match[j] = match[j];
			best_candidates[0].match_sum = match_sum;
		}

	} while(random_sqs_position(Apositions, nAatoms, n_sqs_atoms) && n_runs++ < 1000 );

	for(int i = 0; i < 5; i++){
		//for(int j = 0; j < nAatoms; j++)
			//best_candidates[i+1].Apositions[j] = best_candidates[i].Apositions[j];
		for(int j = 1; j < 8; j++)
			printf ("%.5f ", best_candidates[i].match[j]);
		printf ("%.5f\n", best_candidates[i].match_sum);
	}

	/* Output results to files */
	if(output_format == VASP){
		FILE * out_file = fopen(argv[2], "w");
		fprintf(out_file, "SQS generated %ix%ix%i supercell\n", ncelsa, ncelsb, ncelsc);
		fprintf(out_file, "%f\n", factor);
		fprintf(out_file, "%20.10f %20.10f %20.10f\n", u1[0] * ncelsa, u1[1] * ncelsa, u1[2] * ncelsa);
		fprintf(out_file, "%20.10f %20.10f %20.10f\n", u2[0] * ncelsb, u2[1] * ncelsb, u2[2] * ncelsb);
		fprintf(out_file, "%20.10f %20.10f %20.10f\n", u3[0] * ncelsc, u3[1] * ncelsc, u3[2] * ncelsc);

		fprintf(out_file, "%5s", sqs_atomname);
		fprintf(out_file, "%5s", sqs_atomname_old);
		char cur_atom[20] = {0}; 
		for(int i = 0; i < n_atoms_prim_cell; i++){
			if(inat[i].is_sqs == 0 && strcmp(inat[i].name, cur_atom) != 0){
				fprintf(out_file, "%5s", inat[i].name);
				strcpy(cur_atom, inat[i].name);
			}
		}
	
		fprintf(out_file, "\n%5i", nAatoms);
		fprintf(out_file, "%5i", n_sqs_atoms - nAatoms);
		int count = 0; 
		for(int i = 0; i < n_atoms_prim_cell; i++){
			if(inat[i].is_sqs == 0){
				count++;
				if(i == n_atoms_prim_cell - 1)
					fprintf(out_file, "%5i", count * ncelsa * ncelsb * ncelsc);
				else if(strcmp(inat[i].name, inat[i+1].name) != 0){
					fprintf(out_file, "%5i", count * ncelsa * ncelsb * ncelsc);
					count = 0;
				}
			}
		}

		fprintf(out_file, "\nDirect\n");

		for(int i = 0; i < n_sqs_atoms; i++)
			if(isA(Apositions, nAatoms, n_sqs_atoms, i) == 1)
				fprintf(out_file, "%16.9f %16.9f %16.9f\n", s_cell[i].v1, s_cell[i].v2, s_cell[i].v3);
		for(int i = 0; i < n_sqs_atoms; i++)
			if(isA(Apositions, nAatoms, n_sqs_atoms, i) == 0)
				fprintf(out_file, "%16.9f %16.9f %16.9f\n", s_cell[i].v1, s_cell[i].v2, s_cell[i].v3);
		
		for(int i = 0; i < atomtypes; i++){
	 		for(int na = 0; na < ncelsa; na++){
				for(int nb = 0; nb < ncelsb; nb++){
					for(int nc = 0; nc < ncelsc; nc++){
						for(int n = 0; n < n_atoms_prim_cell; n++){
							if(inat[n].is_sqs == 0 && inat[n].atomtype == i)
								fprintf(out_file, "%16.9f %16.9f %16.9f\n", 
									(na + inat[n].v1) / ncelsa, (nb + inat[n].v2) / ncelsb, (nc + inat[n].v3) / ncelsc);
						}
					}
				}
			}
		}
	}

	free(inat);

	return 0;
}
