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

	struct {
		char *name;
		char *nicename;
		char *align;
	} datacols[] = {
		{"", "f$_H$ ERDA", "c"},
		{"fHf", "f$_H$", "c"},
		{"fHsp3CH3f", "f$_\\mathrm{H_{sp3CH3}}$", "c"}, 
		{"fHsp3CH2f", "f$_\\mathrm{H_{sp3CH2}}$", "c"}, 
		{"fHsp3CHf", "f$_\\mathrm{H_{sp3CH}}$", "c"}, 
		{"fHsp2CH2f", "f$_\\mathrm{H_{sp2CH2}}$", "c"},
		{"fHsp2CHf", "f$_\\mathrm{H_{sp2CH}}$", "c"}
	};

	struct {
		char *file;
		char *nicename;
		char *sample;
		double values[sizeof(datacols)/sizeof(datacols[0])];
	} datarows[] = {
		{"../grafy/vysledky/out-multifit", "CH30A", "1", 0.326, 0},
		{"../grafy/vysledky/out-multifit", "CH83A", "4", 0.48, 0}, 
		{"../grafy/vysledky/out-multifit", "CH88A", "2", 0.38, 0}, 
		{"../grafy/vysledky/out-multifit", "CH90A", "3", 0.31, 0},
		{"../grafy/vysledky/out-CH87A", "CH87A", "", 0.48, 0},
		{"../grafy/vysledky/out-CH89A", "CH89A", "", 0.35, 0},
		{"../grafy/vysledky/out-CH30C", "CH30C", "", 0.306, 0} 
	};


	for (int i = 0; i < sizeof(datarows)/sizeof(datarows[0]); i++) {
	
		FILE *input_file;
		if ((input_file = fopen(datarows[i].file,"r")) == NULL){
			printf("Unable to open file %s\n", argv[1]);
			return 1; 
		}

		for (int j = 0; j < sizeof(datacols)/sizeof(datacols[0]); j++) {
			if(strcmp(datacols[j].name, "") == 0)
				continue;	
	
			char test[200];
			char buf[200];
			double dummy;

			rewind(input_file);
			strcpy(test, "# ");
			strcat(test, datacols[j].name);
			strcat(test, datarows[i].sample);
			strcat(test, " = %lf +- %lf");

			while(fgets(buf, 199, input_file) != NULL) {
				if (sscanf(buf, test, &datarows[i].values[j], dummy) >= 1)
					break;	
			}
		}
		if (strstr(datacols[5].name, "fHsp2CH2f") != NULL)
			datarows[i].values[5] = datarows[i].values[1] - datarows[i].values[2] - datarows[i].values[3] - datarows[i].values[4] - datarows[i].values[6];
	}

	printf("\\begin{tabular}{l");
	for(int i = 0; i < sizeof(datacols)/sizeof(datacols[0]); i++)
		printf("%s", datacols[i].align);
	printf("}\n");
	printf("\\hline\n");
	printf("Vrstva");
	for(int i = 0; i < sizeof(datacols)/sizeof(datacols[0]); i++)
		printf(" & %s", datacols[i].nicename);
	printf("\\\\\n");
	printf("\\hline\\hline\n");

	for (int i = 0; i < sizeof(datarows)/sizeof(datarows[0]); i++) {
		printf("%s", datarows[i].nicename);
		for (int j = 0; j < sizeof(datacols)/sizeof(datacols[0]); j++) {
			printf(" & %.3f", datarows[i].values[j]);
		}
		printf("\\\\\n");
	}
	printf("\\hline\n");
 	printf("\\end{tabular}\n");

	return 0;
}

