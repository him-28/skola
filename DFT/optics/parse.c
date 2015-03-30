#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <assert.h>

typedef struct {
	int lowband;
	int upband;
	int len;
	double *E;
	double *eps;
} trans;

typedef struct {
	int lowa;
	int lowb;
	int higha;
	int highb;
	int len;
	double *E;
	double *eps;
} strans;

int main(int argc, char *argv[])
{
	if(argc < 2){
		fprintf(stderr, "Error: case name unspecified!\n");
		return 1;
	}
	

	FILE * input_file;
	trans *data = NULL;
	int ndata = 0;

	for(int i = 1; 1; i++){
		
		char fpath[256];
		if(i < 101){
			/*Construct file name*/
			strcpy(fpath,argv[1]);
			strcat(fpath,".Im_eps_xx_");
			char num[4];
			sprintf(num, "%i", i);
			if(i != 100)
				strcat(fpath, num);
			else {
				strcat(fpath, "**");
				i = 140;
			}
			fprintf(stdout, "Opening file %s\n", fpath);
		}
		else {
			/*Construct file name*/
			strcpy(fpath,"fort.");
			char num[5];
			sprintf(num, "%i", i);
			strcat(fpath, num);
			fprintf(stdout, "Opening file %s\n", fpath);
		}

		/*Open file*/
		if((input_file = fopen( fpath, "r")) == NULL ){
			fprintf(stderr, "Error: Opening file %s failed\n", fpath);
			break;
		}
		
		/* Skip first two lines*/
		char buf[256];
	    fgets(buf, 256, input_file);
	    fgets(buf, 256, input_file);

		fscanf(input_file, "%s", buf);
		if(strstr(buf,"Energy")== NULL){
			fprintf(stderr, "Error: File not in right format, expected \"Energy\", found %s\n", buf);
			break;
		}

		/* Go through the file to determine number of collumns and bands*/
		int j = 0;
		int a,b;
		while(fscanf(input_file, "%i %i", &a, &b) == 2){
			data = realloc(data, (ndata + 1) * sizeof(trans));
			data[ndata].lowband = a;
			data[ndata].upband = b;
			printf("lower band: %i, upper band: %i\n", a, b);
			data[ndata].eps = NULL;
			data[ndata].E = NULL;			
			data[ndata].len = 0;
			ndata++;
			j++;
		}
		
		double e;

		while(fscanf(input_file, "%le", &e) == 1){
			for(int k = 0; k < j; k++){
				double ep;
				fscanf(input_file, "%le", &ep);
				if(ep != 0.0){
					data[ndata-j+k].len++;
					data[ndata-j+k].eps = realloc(data[ndata-j+k].eps, data[ndata-j+k].len*sizeof(double));
					data[ndata-j+k].eps[data[ndata-j+k].len-1] = ep;
					data[ndata-j+k].E = realloc(data[ndata-j+k].E, data[ndata-j+k].len*sizeof(double));
					data[ndata-j+k].E[data[ndata-j+k].len-1] = e;
				}					
			}
		}

		fclose(input_file);

				
	}

#if 0
	for(int i = 0; i < ndata; i++){
		printf("%i -> %i:\n", data[i].lowband, data[i].upband);
		for(int l = 0; l < data[i].len; l++){
			printf("%.3f %.3e\n", data[i].E[l], data[i].eps[l]);
		}
		printf("\n");
	}
#endif

char buf[254];
do {
	strans sdata;
	sdata.len = 0;
	sdata.E = NULL;
	sdata.eps = NULL;
	char name[256];

	printf("Input low band range:");
	scanf("%i %i", &sdata.lowa, &sdata.lowb);
	printf("Input high band range:");
	scanf("%i %i", &sdata.higha, &sdata.highb);
	printf("Output file name:");
	scanf("%s", name);

	for(int i = 0; i < ndata; i++){
		if(data[i].len == 0)
			continue;
		if(data[i].lowband >= sdata.lowa 
			&& data[i].lowband <= sdata.lowb 
			&& data[i].upband >= sdata.higha 
			&& data[i].upband <= sdata.highb){
			int j = 0, k = 0, len = 0;
			double *E = NULL, *eps = NULL;

			while(j < data[i].len || k < sdata.len){
				E = realloc(E, (len + 1) * sizeof(double));
				eps = realloc(eps, (len + 1) * sizeof(double));
				
				if(k == sdata.len || (data[i].E[j] < sdata.E[k] && j < data[i].len)){
					E[len] = data[i].E[j];
					eps[len] = data[i].eps[j];
					j++;
				}
				else if(j < data[i].len && k < sdata.len && data[i].E[j] == sdata.E[k]){
					E[len] = data[i].E[j];
					eps[len] = data[i].eps[j] + sdata.eps[k];
					j++;
					k++;
				}
				else if(j == data[i].len || (data[i].E[j] > sdata.E[k] && k < sdata.len)){
					E[len] = sdata.E[k];
					eps[len] = sdata.eps[k];
					k++;
				}
				else
					assert(!"problems ahead");
				len++;
			}

			/* copy temporary data */
			sdata.len = len;
			sdata.E = realloc(sdata.E, len * sizeof(double));
			sdata.eps = realloc(sdata.eps, len * sizeof(double));
			memcpy((void *)sdata.E, (void *)E, len * sizeof(double));
			memcpy((void *)sdata.eps, (void *)eps, len * sizeof(double));
			free(E);
			free(eps);
		}
	}

	FILE *output_file = fopen(name, "w");
	for(int l = 0; l < sdata.len; l++){
		fprintf(output_file, "%.3f %.3e\n", sdata.E[l], sdata.eps[l]);
	}
	fclose(output_file);

	free(sdata.E);
	free(sdata.eps);

	printf("Calculate another transition combination? (y/n)\n");
} while (scanf("%s", buf) == 1 && strstr(buf,"y") != NULL);

	for(int i = 0; i < ndata; i++){
		if(data[i].len == 0)
			continue;
		free(data[i].E);
		free(data[i].eps);
	}

	free(data);

	return 0;
}
