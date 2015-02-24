#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct {
	double kx, ky, kz;
	int knum;
	int unknown;
	int ene_num;
	double mult;
	double *data;
} kpoint; 

int main(int argc, char *argv[]){

	if(argc != 3){
		printf("incorect number of arguments\n");
		printf("expected filtene <bandindex> <energyfile>\n");
	}

	int sel_band = atoi(argv[1]);
	printf("selected band %i\n", sel_band);

	FILE *enefile;
	if((enefile = fopen(argv[2], "r")) == NULL){
		printf("unable to open input file %s", argv[2]);
	}

	char out_file_name[1000] = {};
	strcat(out_file_name, argv[2]);
	strcat(out_file_name, "f");
	FILE *outfile = fopen(out_file_name, "w");
	
	char l1[1000];
	char l2[1000];
	/* there must be much more clever way how to read the output */
	int i = 0;
	while(fgets(l1, 1000, enefile) != NULL &&
		  fgets(l2, 1000, enefile) != NULL &&
		  l1[0] != ' ')
		i++;

	rewind(enefile);

	while(i-- > 0){
		fprintf(outfile, fgets(l1, 1000, enefile));
		fprintf(outfile, fgets(l1, 1000, enefile));
	}

	kpoint *kpoints = malloc(sizeof(kpoint));  

	i = 0;
	while(fscanf(enefile, "%le %le %le %i %i %i %le",
				&kpoints[i].kx, &kpoints[i].ky, &kpoints[i].kz, &kpoints[i].knum,
				&kpoints[i].unknown, &kpoints[i].ene_num, &kpoints[i].mult) == 7){
		kpoints[i].data = malloc(kpoints[i].ene_num * sizeof(double));
		int dummy;
		for(int j = 0; j < kpoints[i].ene_num; j++){
			fscanf(enefile, "%i %le", &dummy, &kpoints[i].data[j]);
		}
		i++;
		kpoints = realloc(kpoints, sizeof(kpoint) * (i + 1));
	}

	/* only select the required band */
	for(int j = 0; j < i; j++){
		/* check that we actually have the required band index */
		if(kpoints[j].ene_num < sel_band){
			printf("band %i not present at k-point %i, energy limits too low?\n", sel_band, kpoints[j].knum);
		}
		fprintf(outfile, " %18.12E %18.12E %18.12E", kpoints[j].kx, kpoints[j].ky, kpoints[j].kz);
		fprintf(outfile, " %9i %5i %5i %4.1f   \n", kpoints[j].knum, kpoints[j].unknown, 1, kpoints[j].mult);
		fprintf(outfile, "%12i", 1);
		if(abs(kpoints[j].data[sel_band - 1]) >= 1.0)
			fprintf(outfile, "%19.14f     \n", kpoints[j].data[sel_band - 1]);
		else if(abs(kpoints[j].data[sel_band - 1]) >= 0.1)
			fprintf(outfile, "%19.15f     \n", kpoints[j].data[sel_band - 1]);
		else
			fprintf(outfile, "%24.15E\n", kpoints[j].data[sel_band - 1]);
	}

	/* clean up */
	for(int j = 0; j < i; j++)
		free(kpoints[j].data);
	free(kpoints);
	fclose(outfile);
	fclose(enefile);

	return 0;
}
