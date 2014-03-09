#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#ifndef M_PI
#    define M_PI 3.14159265358979323846
#endif

#define DIST_MARGIN 1e-5

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
	return 0;
}

int isA(int *Apositions, int nAatoms, int n_sqs_atoms, int pos){
	pos = pos % n_sqs_atoms;
	for(int i = 0; i < nAatoms; i++)
		if(Apositions[i] == pos)
			return 1;
	return 0;
}

int main(int argc, char *argv[]){
	
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

	/* import cell parameters and basis vectors */
	if(fscanf(input_file, "%le %le %le %le %le %le", &a, &b, &c, &alpha, &beta, &gamma) != 6 ||
		fscanf(input_file, "%le %le %le", &u1[0], &u1[1], &u1[2]) != 3 ||
		fscanf(input_file, "%le %le %le", &u2[0], &u2[1], &u2[2]) != 3 ||
		fscanf(input_file, "%le %le %le", &u3[0], &u3[1], &u3[2]) != 3){
		fprintf(stderr, "sqs: error while reading input file\n");
		return 1;
	}

	double pos[3];
	char atomname[20];
	typedef struct {
		double v1;
		double v2;
		double v3;
		char name[20];
		int is_sqs;
	} input_atom;

	input_atom *inat = NULL;
	int n_sqs_atoms_prim_cell = 0;
	int n_atoms_prim_cell = 0;

	/* import primitive cell structure */
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
	printf("sqs: we have a total of %i atoms of supercell\n", n_atoms_prim_cell * ncelsa * ncelsb * ncelsc);
	printf("sqs: %i of them are being SQS'd\n", n_sqs_atoms);
	printf("sqs: with A concentration of %.2f, %i of them are A type\n\n",  conc, nAatoms);

	/* convert angles to radians */
	alpha = (alpha / 180) * M_PI;
	beta = (beta / 180) * M_PI;
	gamma = (gamma / 180) * M_PI;

	/* precompute latice coordinates to cartesian transformation matrix */
	double T[3][3];
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
						printf("sqs: atom %2i at %.3f %.3f %.3f\n", i, s_cell[i].v1, s_cell[i].v2, s_cell[i].v3);
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
					printf("%i %i %i %i", na, nb, nc, n);
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

			double mindv1 = fabs(s_cell[i].v1 - large_s_cell[j].v1);
			double mindv2 = fabs(s_cell[i].v2 - large_s_cell[j].v2);
			double mindv3 = fabs(s_cell[i].v3 - large_s_cell[j].v3);

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
			
			//printf("%5.2f ", distances[i][j]);
		}
		//printf("\n");
	}

	qsort(dist_list, dist_list_length, sizeof(double), compare_double);
	printf("Unique atomic distances: %i\n", dist_list_length);
	for(int l = 0; l < dist_list_length; l++){
		printf("%.3f ", dist_list[l]);
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

	/* special cell from David rutile out_atomPositionsSQS_2*/
	Apositions[0] = 0;
	Apositions[1] = 1;
	Apositions[2] = 3;
	Apositions[3] = 8;
	Apositions[4] = 9;
	Apositions[5] = 12;
	Apositions[6] = 13;
	Apositions[7] = 14;

	/* special cell from David TiAlN out_atomPositionsSQS_1
	Apositions[0] = 1;
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
	Apositions[11] = 22;
	Apositions[12] = 23;
	Apositions[13] = 24;
	Apositions[14] = 25;
	Apositions[15] = 29;
	Apositions[16] = 33;
	Apositions[17] = 34;
	Apositions[18] = 37;
	Apositions[19] = 38;
	Apositions[20] = 41;
	Apositions[21] = 44;
	Apositions[22] = 45;
	Apositions[23] = 47;*/

	/* actually start SQS */
	/* try all possibilities for now, Monte Carlo later*/
	//do {
		double match[dist_list_length];
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
			printf("%f ", match[d]);
		}
	//printf("\n");
	//} while(next_sqs_position(Apositions, nAatoms, n_sqs_atoms));

	return 0;
}
