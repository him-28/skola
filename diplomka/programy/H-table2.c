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
		char *name2;
		int isfixed;
		char *nicename;
		char *format;
		double multiply;
	} datacols[] = {
		{"", "", 0, "$f_\\mathrm{H,E}$", "%.3f", 1.0},
		{"fHf", "", 0, "$f_\\mathrm{H}$", "%.3f", 1.0},
		{"fHsp3CH3f", "", 0, "$f_\\mathrm{H_{sp3CH3}}$", "%.3f", 1.0}, 
		{"fHsp3CH2f", "", 0, "$f_\\mathrm{H_{sp3CH2}}$", "%.3f", 1.0}, 
		{"fHsp3CHf", "", 0, "$f_\\mathrm{H_{sp3CH}}$", "%.3f", 1.0}, 
		{"fHsp2CH2f", "", 0, "$f_\\mathrm{H_{sp2CH2}}$", "%.3f", 1.0},
		{"fHsp2CHf", "", 0, "$f_\\mathrm{H_{sp2CH}}$", "%.3f", 1.0},
		{"", "", 0, "", "c"},
		{"Naf", "", 0, "$N_\\mathrm{a}$\\,[eV$^2$]", "%.0f", 1.0},
		{"fCsp3f", "", 0, "$f_\\mathrm{Csp3}$", "%.3f", 1.0},
		{"fCsp3/fCsp2f", "", 0, "$f_\\mathrm{C_{sp3}}/f_\\mathrm{C_{sp2}}$", "%.3f", 1.0},
		{"df", "E", 0, "$d_\\mathrm{fE}$\\,[nm]", "%.0f", 1.0},
		{"df", "R", 0, "$d_\\mathrm{fR}$\\,[nm]", "%.0f", 1.0},
		{"df", "M", 0, "$d_\\mathrm{fM}$\\,[nm]", "%.0f", 1.0},
		{"Egpif", "", 0, "$E_\\mathrm{g\\pi}$\\,[eV]", "%.1f", 1.0},
		{"Ehpif", "", 1, "$E_\\mathrm{h\\pi}$\\,[eV]", "%.2f", 1.0},
		{"Ecpif", "", 0, "$E_\\mathrm{c\\pi}$\\,[eV]", "%.1f", 1.0},
		{"Bcpif", "", 0, "$B_\\mathrm{c\\pi}$\\,[eV]", "%.1f", 1.0},
		{"Egsigmaf", "", 0, "$E_\\mathrm{g\\sigma}$\\,[eV]", "%.1f", 1.0},
		{"Ehsigmaf", "", 1, "$E_\\mathrm{h\\sigma}$\\,[eV]", "%.2f", 1.0},
		{"Ecsigmaf", "", 1, "$E_\\mathrm{c\\sigma}$\\,[eV]", "%.2f", 1.0},
		{"Bcsigmaf", "", 1, "$B_\\mathrm{c\\sigma}$\\,[eV]", "%.2f", 1.0},
		{"alphaKf", "", 1, "$\\alpha_\\mathrm{K}$", "%.1f", 1.0},
		{"EKf", "", 1, "$E_\\mathrm{K}$\\,[eV]", "%.0f", 1.0},
		{"alphapixif", "", 1, "$\\alpha_{\\pi\\xi}$", "%.3f", 1.0},
		{"alphasigmaxif", "", 1, "$\\alpha_{\\sigma\\xi}$", "%.3f", 1.0},
		{"Exf", "", 1, "$E_\\mathrm{x}$\\,[eV]", "%.2f", 1.0},
		{"Qat", "", 1, "$Q_\\mathrm{t}$\\,[eV$^{3/2}$]", "%.1f", 1.0},
		{"Egat", "", 1, "$E_\\mathrm{g}$\\,[eV]", "%.1f", 1.0},
		{"Ehat", "", 1, "$E_\\mathrm{h}$\\,[eV]", "%.1f", 1.0},
		{"QGat", "", 1, "$Q_\\mathrm{G}$\\,[eV$^{3/2}$]", "%.1f", 1.0},
		{"EGat", "", 1, "$E_\\mathrm{G}$\\,[eV]", "%.1f", 1.0},
		{"BGat", "", 1, "$E_\\mathrm{G}$\\,[eV]", "%.1f", 1.0},
		{"dt", "", 0, "$d_\\mathrm{t}$\\,[nm]", "%.1f", 1.0},
		{"dt1", "", 1, "$d_\\mathrm{t}$\\,[nm]", "%.1f", 1.0},
		{"fOs", "", 1, "$f_\\mathrm{O}$\\,[10$^{-6}$]", "%.2f", 1e6},
		{"ds", "", 0, "$d_\\mathrm{s}$\\,[$\\mu$m]", "%.0f", 1e3},
		{"ds1", "", 1, "$d_\\mathrm{s}$\\,[$\\mu$m]", "%.0f", 1e3},
		{"dt", "", 0, "$d_\\mathrm{t}$\\,[nm]", "%.0f", 1.0},
		{"dt1", "", 1, "$d_\\mathrm{t}$\\,[nm]", "%.0f", 1.0},
		{"db", "", 0, "$d_\\mathrm{b}$\\,[nm]", "%.1f", 1.0},
		{"db1", "", 1, "$d_\\mathrm{b}$\\,[nm]", "%.1f", 1.0},
		{"chi", "", 0, "$\\chi$", "%.2f", 1.0},
		{"chi(R", ")", 0, "$\\chi_\\mathrm{R}$", "%.2f", 1.0},
		{"chi(Is", ",IcII%*i,IcIII%*i)", 0, "$\\chi_\\mathrm{ell}$", "%.2f", 1.0},
		{"chi(TMIR", ")", 0, "$\\chi_\\mathrm{T}$", "%.2f", 1.0},


		{"alphasp3CH3af", "", 1, "$\\alpha_\\mathrm{sp3CH3a} \\times 10^{-3}$", "%.2f", 1e3},
		{"nusp3CH3af", "", 1, "$\\nu_\\mathrm{sp3CH3a}$\\,[cm$^{-1}$]", "%.0f", 1.0},
		{"alphasp3CH3sf", "", 1, "$\\alpha_\\mathrm{sp3CH3s} \\times 10^{-3}$", "%.2f", 1e3},
		{"nusp3CH3sf", "", 1, "$\\nu_\\mathrm{sp3CH3s}$\\,[cm$^{-1}$]", "%.0f", 1.0},
		{"betasp3CH3sf", "", 0, "$\\beta_\\mathrm{sp3CH3}$\\,[10$^1$cm$^{-1}$]", "%.0f", 1e-1},
		{"alphasp3CH3sbf", "", 1, "$\\alpha_\\mathrm{sp3CH3bs} \\times 10^{-3}$", "%.2f", 1e3},
		{"nusp3CH3sbf", "", 1, "$\\nu_\\mathrm{sp3CH3bs}$\\,[cm$^{-1}$]", "%.0f", 1.0},
		{"betasp3CH3sbf", "", 0, "$\\beta_\\mathrm{sp3CH3bs}$\\,[10$^1$cm$^{-1}$]", "%.0f", 1e-1},
		{"alphasp3CH2af", "", 1, "$\\alpha_\\mathrm{sp3CH2a} \\times 10^{-3}$", "%.2f", 1e3},
		{"nusp3CH2af", "", 1, "$\\nu_\\mathrm{sp3CH2a}$\\,[cm$^{-1}$]", "%.0f", 1.0},
		{"alphasp3CH2sf", "", 1, "$\\alpha_\\mathrm{sp3CH2s} \\times 10^{-3}$", "%.2f", 1e3},
		{"nusp3CH2sf", "", 1, "$\\nu_\\mathrm{sp3CH2s}$\\,[cm$^{-1}$]", "%.0f", 1.0},
		{"betasp3CH2sf", "", 0, "$\\beta_\\mathrm{sp3CH2}$\\,[10$^1$cm$^{-1}$]", "%.0f", 1e-1},
		{"alphasp3CHf", "", 1, "$\\alpha_\\mathrm{sp3CH} \\times 10^{-3}$", "%.2f", 1e3},
		{"nusp3CHf", "", 1, "$\\nu_\\mathrm{sp3CH}$\\,[cm$^{-1}$]", "%.0f", 1.0},
		{"betasp3CHf", "", 0, "$\\beta_\\mathrm{sp3CH}$\\,[10$^1$cm$^{-1}$]", "%.0f", 1e-1},
		{"alphasp2CH2af", "", 1, "$\\alpha_\\mathrm{sp2CH2a} \\times 10^{-3}$", "%.2f", 1e3},
		{"nusp2CH2af", "", 1, "$\\nu_\\mathrm{sp2CH2a}$\\,[cm$^{-1}$]", "%.0f", 1.0},
		{"alphasp2CH2sf", "", 1, "$\\alpha_\\mathrm{sp2CH2s} \\times 10^{-3}$", "%.2f", 1e3},
		{"nusp2CH2sf", "", 1, "$\\nu_\\mathrm{sp2CH2s}$\\,[cm$^{-1}$]", "%.0f", 1.0},
		{"betasp2CH2sf", "", 0, "$\\beta_\\mathrm{sp2CH2}$\\,[10$^1$cm$^{-1}$]", "%.0f", 1e-1},
		{"alphasp2CHf", "", 1, "$\\alpha_\\mathrm{sp2CH} \\times 10^{-3}$", "%.2f", 1e3},
		{"nusp2CHf", "", 1, "$\\nu_\\mathrm{sp2CH}$\\,[cm$^{-1}$]", "%.0f", 1.0},
		{"betasp2CHf", "", 0, "$\\beta_\\mathrm{sp2CH}$\\,[10$^1$cm$^{-1}$]", "%.0f", 1e-1},

		{"alphaCH2wf", "", 0, "$N_\\mathrm{sp2C,A}\\,[10^{-6}\\,\\mathrm{eV}^2]$", "%.0f", 0.0},
		{"nuCH2wf", "", 0, "$\\nu_\\mathrm{sp2C,A}$\\,[cm$^{-1}$]", "%.0f", 1.0},
		{"betaCH2wf", "", 0, "$\\beta_\\mathrm{sp2C,A}$\\,[10$^1$cm$^{-1}$]", "%.0f", 1e-1},
		{"alphaCHof", "", 0, "$N_\\mathrm{sp2C,B}\\,[10^{-6}\\,\\mathrm{eV}^2]$", "%.0f", 0.0},
		{"nuCHof", "", 0, "$\\nu_\\mathrm{sp2C,B}$\\,[cm$^{-1}$]", "%.0f", 1.0},
		{"betaCHof", "", 0, "$\\beta_\\mathrm{sp2C,B}$\\,[10$^1$cm$^{-1}$]", "%.0f", 1e-1},
		{"alphaCH8f", "", 0, "$N_\\mathrm{sp2C,C}\\,[10^{-6}\\,\\mathrm{eV}^2]$", "%.0f", 0.0},
		{"nuCH8f", "", 0, "$\\nu_\\mathrm{sp2C,C}$\\,[cm$^{-1}$]", "%.0f", 1.0},
		{"betaCH8f", "", 0, "$\\beta_\\mathrm{sp2C,C}$\\,[10$^1$cm$^{-1}$]", "%.0f", 1e-1},
		{"alphaCH2xf", "", 0, "$N_\\mathrm{sp3CHxy}\\,[10^{-6}\\,\\mathrm{eV}^2]$", "%.0f", 0.0},
		{"nuCH2xf", "", 0, "$\\nu_\\mathrm{sp3CHxy}$\\,[cm$^{-1}$]", "%.0f", 1.0},
		{"betaCH2xf", "", 0, "$\\beta_\\mathrm{sp3CHxy}$\\,[10$^1$cm$^{-1}$]", "%.0f", 1e-1},
	};

	struct {
		char *file;
		char *nicename;
		char *sample;
		double values[sizeof(datacols)/sizeof(datacols[0])];
		double errors[sizeof(datacols)/sizeof(datacols[0])];
		double NH;
	} datarows[] = {
		{"vysledky/out-multifit", "CH30A", "1", 0.326, 0},
		{"vysledky/out-multifit", "CH83A", "4", 0.48, 0}, 
		{"vysledky/out-multifit", "CH88A", "2", 0.38, 0}, 
		{"vysledky/out-multifit", "CH90A", "3", 0.31, 0},
		{"vysledky/out-CH30C", "CH30C", "", 0.306, 0},
		{"vysledky/out-CH30D", "CH30D", "", 0.306, 0}, 
		{"vysledky/out-CH87A", "CH87A", "", 0.48, 0},
		{"vysledky/out-CH89A", "CH89A", "", 0.35, 0}

	};


	for (int i = 0; i < sizeof(datarows)/sizeof(datarows[0]); i++) {
	
		FILE *input_file;
		if ((input_file = fopen(datarows[i].file,"r")) == NULL){
			printf("Unable to open file %s\n", datarows[i].file);
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
			if(strcmp(datacols[j].name2, "") != 0 && strcmp(datarows[i].sample, "") == 0)
				strcat(test, "1");
			else if (datacols[j].isfixed != 1)
				strcat(test, datarows[i].sample);
			strcat(test, datacols[j].name2);
			strcat(test, " = %lf +- %lf");

			while(fgets(buf, 199, input_file) != NULL) {
				if (sscanf(buf, test, &datarows[i].values[j], &datarows[i].errors[j]) >= 1)
					break;	
			}
		}
		if (strstr(datacols[5].name, "fHsp2CH2f") != NULL)
			datarows[i].values[5] = datarows[i].values[1] - datarows[i].values[2] - datarows[i].values[3] - datarows[i].values[4] - datarows[i].values[6];
		datarows[i].NH = 0.000545*datarows[i].values[1]*datarows[i].values[8];
		datarows[i].values[10] = datarows[i].values[9]/(1 - datarows[i].values[1] - datarows[i].values[9]);
	}

	printf("\\begin{tabular}{l");
	for(int i = 0; i < sizeof(datarows)/sizeof(datarows[0]); i++)
		printf("c");
	printf("}\n");
	printf("\\hline\n");
	printf("Vrstva");
	for(int i = 0; i < sizeof(datarows)/sizeof(datarows[0]); i++)
		printf(" & %s", datarows[i].nicename);
	printf("\\\\\n");
	printf("\\hline\\hline\n");

	for (int i = 0; i < sizeof(datacols)/sizeof(datacols[0]); i++) {
		if(strcmp(datacols[i].name, "") == 0 &&
			strcmp(datacols[i].nicename, "") == 0)
				printf("\\hline\n");
		else {
			printf("%s", datacols[i].nicename);
			for (int j = 0; j < sizeof(datarows)/sizeof(datarows[0]); j++) {
				char format[50] = " & ";
				char zaok[50] = "%.";

				if (datarows[j].errors[i]*datacols[i].multiply > 1.0){
					//printf("ano %s\n", datacols[i].nicename);
					for (int rad = 0; rad < 30; rad++){
						if(datarows[j].errors[i]*datacols[i].multiply < pow(10.0, (double)(rad+1)) &&
							datarows[j].errors[i]*datacols[i].multiply > pow(10.0, (double)(rad))){
							datarows[j].values[i] = round(datarows[j].values[i]/pow(10.0, (double)rad))*pow(10.0, (double)rad);
							break;
						}
					}
				}
				else {
					//printf("ne %s\n", datacols[i].nicename);
					for (int rad = -1; rad > -30; rad--){
						if(datarows[j].errors[i]*datacols[i].multiply < pow(10.0, (double)(rad+1)) &&
						   datarows[j].errors[i]*datacols[i].multiply > pow(10.0, (double)(rad))){
							char cislo[10] = "";
							sprintf(cislo, "%i", rad*(-1));
							strcat(zaok, cislo);
							strcat(zaok, "f");
							//printf("%s\n",zaok);
							break;
						}
					}	
				}
				if(strcmp(zaok,"%.") == 0)
					strcat(format, datacols[i].format);
				else
					strcat(format, zaok);
				if(datacols[i].multiply != 0.0)
					printf(format, datarows[j].values[i]*datacols[i].multiply);
				else
					printf(format, datarows[j].values[i]*datarows[j].NH*1e6);
			}
			printf("\\\\\n");
		}
	}
	printf("\\hline\n");
 	printf("\\end{tabular}\n");

	return 0;
}

