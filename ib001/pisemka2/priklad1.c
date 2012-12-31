/*
Napište program, který od uživatele vyžádá na standardním vstupu na počet matic a jejich rozměr,
matice naplní náhodnými nezápornými čísly menšími než 1000. Ke každé matici si spočítá její
sumu a vypíše matice v pořadí, jak byly vygenerovány, spolu se sumou do prvního souboru
„maticeA.txt“. Poté matice seřadí vzestupně dle sumy a v tomto pořadí spolu se sumou vypíše
do druhého souboru „maticeB.txt“. Ukončí činnost.
	• Vstup od uživatele na standardním vstupu bude ve formátu:
		▪ pocet_matic pocet_radku pocet_sloupcu
	• Seřazení matic můžete provést libovolným algoritmem, lze použít vlastní implementaci
	nebo i funkci qsort() z stdlib.h.
	• Výpis do souboru proveďte v textovém režimu, ať lze matici i sumu snadno číst v textových
	editorech, např. poznámkovém bloku či vim.
	• Budete-li užívat dynamicky alokované paměti, nezapomeňte všechnu zase uvolnit.
		▪ Stačí ovšem statická alokace, neboť znáte vše dopředu.
	• Oba soubory založte v aktuálním adresáři.
	• Nezapomeňte na nastavení generátoru náhodných čísel semínkem třebas dle času.
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
	int rozmer;
	int * umatice;
	int soucet;
} struct_mat;

int napln_matici(struct_mat * a){

	if ((a->umatice = (int *)malloc(sizeof(int) * a->rozmer * a->rozmer)) == NULL) {
		printf("Nepodarilo se alokovat pamet\n");
		return 1;
	}
	int soucet = 0;
	int b = 0;
	
	for(int i = 0; i < a->rozmer; i++){
		for(int j = 0; j < a->rozmer; j++ ) {
			b = rand() % 1000;
			*(a->umatice + j * a->rozmer + i) = b;
			soucet += b;
		}
	}
	a->soucet = soucet;
		
	return 0;
}

int vypis_matici(const struct_mat a, FILE * soubor) {
	
	fprintf(soubor, "%i\n", a.soucet);
	for(int i = 0; i < a.rozmer; i++){
		for(int j = 0; j < a.rozmer; j++ ) {
			fprintf (soubor, "%3i ", *(a.umatice + j * a.rozmer + i) );
		}
		fprintf(soubor, "\n");
	}
	fprintf(soubor, "\n");
}
	

int porovnej(const void *a, const void *b){
	struct_mat * m_a;
	struct_mat * m_b;
	m_a = (struct_mat *)a;
	m_b = (struct_mat *)b;
	
	if (m_a->soucet < m_b->soucet)
		return -1;
	else if (m_a->soucet > m_b->soucet)
		return 1;
	else
		return 0;
}

int main() {

	FILE *vystupa, *vystupb;
	
	vystupa = fopen("maticeA.txt", "w");
	vystupb = fopen("maticeB.txt", "w");
	
	
	int pocet_matic;
	printf("Zadejte pocet matic:\n");
	scanf("%i", &pocet_matic);
	if (pocet_matic < 1) {
		printf("Pocet matic musím být prirozene cislo!\n");
		return 1;
	}

	int rozmery_matic[pocet_matic];
	struct_mat pole_matic[pocet_matic];
	
	for(int i = 0; i < pocet_matic; i++ ) {
		printf("Zadejte rozmer %i-te matice: ", i+1);
		//FIXME: input error handling
		scanf("%i", &rozmery_matic[i]);
	} 
	
	srand(time(NULL));
	
	for(int i = 0; i < pocet_matic; i++) {
		pole_matic[i].rozmer = rozmery_matic[i];
		if (napln_matici(&pole_matic[i]) == 1)
			return 1;
	}

	for(int i = 0; i < pocet_matic; i++ )
		vypis_matici(pole_matic[i], vystupa);
	
	qsort (pole_matic, pocet_matic, sizeof(struct_mat), porovnej);
	
	for(int i = 0; i < pocet_matic; i++ ) {
		vypis_matici(pole_matic[i], vystupb);
		free(pole_matic[i].umatice);
		}

	return 0;
}
