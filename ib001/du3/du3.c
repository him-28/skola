/*
Napište program, který načte ze standardního vstupu řetězec délky nejvýše 20 znaků, ze kterého vyrobí dle abecedy uspořádanou množinu malých písmen abecedy a spočítá její potenční množinu (množinu všech podmnožin dané množiny písmen).

    Načtěte ze standardního vstupu (většinou klávesnice) řetězec délky nejvýše 20 znaků.
    Z řetězce eliminujte všechny znaky, které nepatří mezi znaky abecedy (a-z, A-Z) a všechny převeďte na malá písmena.
    Z řetězce eliminujte násobně se vyskytující znaky. 

    Kroky 1–3 prakticky získáte množinu malých písmen abecedy.

    Tuto množinu seřaďte, avšak nikoli pomocí algoritmů, které sami implementujete, ale pomocí funkce qsort() z stdlib.h:
        Prototyp qsort():
        void qsort(void *pole, size_t pocet_prvku, size_t velikost_jednoho_prvku, int(*porovnavaci_fce)(const void *, const void *));
        Prototyp porovnávací funkce:
        int porovnavaci_fce(const void *_prvek_a, const void *_prvek_b);
    Implementace porovnávací funkce by měla vracet:
        celé číslo < 0, je-li prvek odkazovaný _prvek_a menší než prvek odkazovaný _prvek_b
        0, jsou-li oba odkazované prvky shodné
        celé číslo > 0, je-li prvek odkazovaný _prvek_a větší než prvek odkazovaný _prvek_b 
    Více informací naleznete třeba v manových stránkách pod linuxem (man qsort 3) nebo třeba na: cppreference. 

    Pro získanou množinu znaků spočítejte její potenční množinu, což je vlastně množina všech jejich podmnožin. 

    Příklad:
        máme-li množinu A
        A = {'a', 'b', 'c'},
        pak její potenční množina ℘(A) bude:
        ℘(A) = {∅, {'a'}, {'b'}, {'c'}, {'a', 'b'}, {'a', 'c'}, {'b', 'c'}, {'a', 'b', 'c'}} 
    Je tedy vidět, že potenční množina obsahuje všechny nula, jedno, dvou, ... |A| (počet prvků množiny A) prvkové podmnožiny „zdrojové“ množiny.
        Samozřejmě pro všechny množiny A platí, že A ⊆ A, takže i celá A ∈ ℘(A), ale také ∅ ⊆ A, takže ∅ ∈ ℘(A). 
    Počet všech podmnožin dané množiny je 2^počet_prvků_dané_množiny, tedy: |℘(A)| = 2^|A|.
        Příklad:
        výše uvedená množina A má 3 prvky (|A| = 3), proto její potenční množina jich má 8 (|℘(A)| = 2^3 = 8), což si můžete výše ručně spočítat.

    Výpočet potenční množiny lze velmi snadno implementovat pomocí rekurzivního volání funkce (funkce volá sama sebe).
    Řešení, které nebude výpočet potenční množiny implementovat rekurzí, nebude akceptováno. 

    Vypočtenou uspořádanou množinu i její potenční množinu vypište přehledně na standardní výstup.
    Prázdnou množinu vyjádřete pomocí prázdných složených závorek: {}.
    Není třeba vypisovat všechny náležitosti zcela řádně, lze tedy například místo:
    {{}, {'a'}, {'b'}, {'c'}, {'a', 'b'}, {'a', 'c'}, {'b', 'c'}, {'a', 'b', 'c'}}
    psát pouze:
    {{}, a, b, c, ab, ac, bc, abc}
    Nemusíte též ošetřovat nevypsání čárky za posledním prvkem množiny, tedy například: {{}, a, b, c, ab, ac, bc, abc, } bude též akceptováno.
    Při správné implementaci výpočtu potenční množiny uspořádání „zdrojové“ množiny písmen způsobí přehledné vypsání písmen uspořádaných dle abecedy v jednotlivých podmnožinách potenční množiny. 
*/


#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAXDELKA 20

int porovnej(const void *a, const void *b){
	if ( *((char *)a) < *((char *)b) )
		return -1;
	else if ( *((char *)a) > *((char *)b) )
		return 1;
	else
		return 0;
}

int pot_mnoz( char * retezec, char * prefix,  int delka, int vel){
	
	//printf ("retezec:%s prefix:%s delka:%i, vel:%i\n", retezec, prefix, delka, vel);
	int prefixsize = strlen(prefix);
	char nprefix[prefixsize + 2];
	
	
	if (delka == vel){
		printf ("%s%s, ",prefix, retezec);
		return 0;
		}
	
	for (int i = 0; i < delka - vel + 1; i++){
		if (vel == 1)
			printf ("%s%c, ", prefix, *(retezec + i) );
		else {
			strcpy (nprefix, prefix);
			nprefix[prefixsize] = *(retezec + i);
			nprefix[prefixsize + 1] = 0;
			pot_mnoz (retezec + i + 1, nprefix, strlen(retezec + i + 1), vel - 1);
		}
	}
	if (strlen(prefix) == 0)
		pot_mnoz(retezec, "", strlen(retezec), vel + 1);
	
	return 0;
}

int main() {

	char retezec[MAXDELKA + 1];
	printf("Zadejte retezec delky nejvyse 20 znaku.\n");
	
	scanf("%20[^\n]s", retezec);

	printf("Retezec: \"%s\" obsahuje nasledujici mnozinu akceptovanych znaku:\n", retezec);

	for(int j = 0; retezec[j] != 0; j++)
		retezec[j] = tolower(retezec[j]);

	int i = 0;
	while (retezec[i] != 0){
		if (isalpha(retezec[i]) == 0 || strrchr(&retezec[i+1], retezec[i]) != NULL){
			memmove(&retezec[i], &retezec[i+1], (MAXDELKA - i)*sizeof(char));
			continue;
		}
		i++;
	}
	
	qsort (retezec, strlen(retezec), sizeof(char), porovnej);
	
	printf("{");
	for (int j = 0; j < strlen(retezec); j++)
		 printf("\'%c\',", retezec[j]);
	printf("}\n");
	
	printf("Jeje potencni mnozina je:\n");
	printf("{{}, ");
	if (strlen(retezec) > 0)
		pot_mnoz(retezec, "", strlen(retezec), 1);
	printf("}\n");
	return 0;
}
