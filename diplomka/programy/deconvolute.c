#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <math.h>

#define sp2CH 0
#define sp2CH2 1
#define sp3CH 2
#define sp3CH2 3
#define sp3CH3 4

int main(int argc, char *argv[]){
	assert(argc == 3);

	FILE *input_file;
	if ((input_file = fopen(argv[1],"r")) == NULL){
		printf("Unable to open file %s\n", argv[1]);
		return 1; 
	}

	int sample = atoi(argv[2]);
	if (sample == 0){
		free(argv[2]);
		argv[2] = "";
	}

	struct {
		char *name;
		int type;
		char *opt;
	} peak_names[] = {
		{"sp3CH3a", sp3CH3, "lt 1 lc rgb \"red\""}, 
		{"sp3CH3s", sp3CH3, "lt 2 lc rgb \"red\""},
		{"sp3CH2a", sp3CH2, "lt 1 lc rgb \"blue\""},
		{"sp3CH2s", sp3CH2, "lt 2 lc rgb \"blue\""},
		{"sp3CH", sp3CH, "lt 1 lc rgb \"green\""},
		{"sp2CH2a", sp2CH2, "lt 1 lc rgb \"orange\""},
		{"sp2CH2s", sp2CH2, "lt 2 lc rgb \"orange\""},
		{"sp2CH", sp2CH, "lt 1 lc rgb \"yellow\""}
	};

	struct {
		double alpha;
		double nu;
		double beta;
	} data[8];

	double Na;
	double dummy;
	double fHx[5], fH;
	
	char test[200] = "# Naf";
	char buf[200];
	strcat(test, argv[2]);
	strcat(test, " = %lf +- %lf");

	while(fgets(buf, 199, input_file) != NULL) {
		if (sscanf(buf, test, &Na, dummy) >= 1)
			break;	
	}

	rewind(input_file);
	strcpy(test, "# fHsp3CH3f");
	strcat(test, argv[2]);
	strcat(test, " = %lf +- %lf");

	while(fgets(buf, 199, input_file) != NULL) {
		if (sscanf(buf, test, &fHx[sp3CH3], dummy) >= 1)
			break;	
	}

	rewind(input_file);
	strcpy(test, "# fHsp3CH2f");
	strcat(test, argv[2]);
	strcat(test, " = %lf +- %lf");

	while(fgets(buf, 199, input_file) != NULL) {
		if (sscanf(buf, test, &fHx[sp3CH2], dummy) >= 1)
			break;	
	}

	rewind(input_file);
	strcpy(test, "# fHsp3CHf");
	strcat(test, argv[2]);
	strcat(test, " = %lf +- %lf");

	while(fgets(buf, 199, input_file) != NULL) {
		if (sscanf(buf, test, &fHx[sp3CH], dummy) >= 1)
			break;	
	}

	rewind(input_file);
	strcpy(test, "# fHsp2CHf");
	strcat(test, argv[2]);
	strcat(test, " = %lf +- %lf");

	while(fgets(buf, 199, input_file) != NULL) {
		if (sscanf(buf, test, &fHx[sp2CH], dummy) >= 1)
			break;	
	}

	rewind(input_file);
	strcpy(test, "# fHf");
	strcat(test, argv[2]);
	strcat(test, " = %lf +- %lf");

	while(fgets(buf, 199, input_file) != NULL) {
		if (sscanf(buf, test, &fH, dummy) >= 1)
			break;	
	}
	fHx[sp2CH2] = fH - fHx[sp3CH3] - fHx[sp3CH2] - fHx[sp3CH] - fHx[sp2CH];

	//fprintf(stderr, "fH:%f, fH33:%f, fH32:%f, fH31:%f, fH22:%f, fH21:%f\n", 
	//		fH, fHx[sp3CH3], fHx[sp3CH2], fHx[sp3CH], fHx[sp2CH2], fHx[sp2CH]);

	for(int i = 0; i < sizeof(peak_names)/sizeof(peak_names[0]); i++){

		rewind(input_file);
		strcpy(test, "# alpha");
		strcat(test, peak_names[i].name);
		strcat(test,"f");
		strcat(test, " = %lf +- %lf");
		while(fgets(buf, 199, input_file) != NULL) {
			if (sscanf(buf, test, &data[i].alpha, dummy) >= 1)
				break;	
		}

		rewind(input_file);
		strcpy(test, "# nu");
		strcat(test, peak_names[i].name);
		strcat(test,"f");
		strcat(test, " = %lf +- %lf");
		while(fgets(buf, 199, input_file) != NULL) {
			if (sscanf(buf, test, &data[i].nu, dummy) >= 1)
				break;	
		}

		rewind(input_file);
		strcpy(test, "# beta");
		strcat(test, peak_names[i].name);
		strcat(test,"f");
		strcat(test, argv[2]);
		strcat(test, " = %lf +- %lf");
		while(fgets(buf, 199, input_file) != NULL) {
			if (sscanf(buf, test, &data[i].beta, dummy) >= 1)
				break;	
		}
	}

	printf("plot[2750:3150]\\\n");//[2800:2100]
	for(int i = 0; i < sizeof(peak_names)/sizeof(peak_names[0]); i++){
		printf("G(x,%e,%e)*%e*0.000545*%e*%e t \"%s\" %s,",
				data[i].nu, data[i].beta, Na, data[i].alpha,
				fHx[peak_names[i].type], peak_names[i].name, peak_names[i].opt);
	}

	for(int i = 0; i < sizeof(peak_names)/sizeof(peak_names[0]); i++){
		printf("G(x,%e,%e)*%e*0.000545*%e*%e", 
				data[i].nu, data[i].beta, Na, data[i].alpha, fHx[peak_names[i].type]);
		if(i != sizeof(peak_names)/sizeof(peak_names[0]) - 1)
			printf("+\\\n");
	}
	printf(" t \"celkem\" lt 1 lc rgb \"black\"");

	return 0;
}

