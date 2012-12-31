/*
Napište program, který bude implementovat jednosměrný lineární spojový seznam s hlavou, do
kterého bude načítat ze souboru „data.txt“ jméno a věk oddělené bílými znaky. Celý soubor
přečte, zapamatuje si v dynamické struktuře a bude číst ze standardního vstupu od uživatele jména,
která vyhledá ve spojovaném seznamu a vypíše odpovídající záznamy.
	• http://en.wikipedia.org/wiki/Linked_list
	• Definujte si odpovídající strukturu, která ponese
		▪ jméno (max. 20 významných znaků)
		▪ věk (unsigned int)
		▪ ukazatel na další prvek (dalsiPrvek) typu ukazatel na danou strukturu
	• Příklad programu užívajícího spojových seznamů můžete nalézt na mých stránkách:
		▪ http://www.fi.muni.cz/~xbayer/ib001/2012/programy/kartoteka.c
		▪ http://www.fi.muni.cz/~xbayer/ib001/2012/
	• Příklad souboru data.txt si můžete stáhnout z:
		▪ http://www.fi.muni.cz/~xbayer/ib001/2012/20121712/data.txt
		▪ čtěte z aktuálního adresáře
	• Při načítání nového záznamu nastaví dalsiPrvek na nový prvek u minulého prvku :)
		▪ Aktuální prvek bude mít dalsiPrvek == NULL
	• Až dočte celý soubor do konce, bude číst od uživatele jména a pro každé z nich vypíše
	jméno a věk, kde se jméno shoduje se zadaným od uživatele.
	• Hlava slouží jako ukazatel na první prvek seznamu, od něj se začíná vyhledávat.
	• Každý nový záznam alokujte pomocí malloc().
		▪ Alokovanou paměť nezapomeňte před ukončením programu uvolnit.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct apolozka{
	char jmeno[21];
	unsigned int vek;
	struct apolozka * dalsi_prvek;
} polozka;

int main() {
	FILE * vstupni_soubor;
	if ((vstupni_soubor = fopen("data.txt", "r")) == NULL) {
		printf("Nepodarilo se otevřít soubor data.txt\n");
		return 1;
	}
		 

	polozka * prvni_pol = NULL;
	polozka * akt_pol = NULL;
	polozka * minula_pol;
	
	char jmeno[21];
	unsigned int vek;
	int prvni = 1;
	
	while (fscanf(vstupni_soubor, "%s %u", jmeno, &vek) == 2) {
		if ((akt_pol = (polozka *)malloc(sizeof(polozka))) == NULL ) {
			printf("Napodarilo se alokovat pamet\n");
			return 1; 
		}
		if (prvni_pol == NULL)
			prvni_pol = akt_pol;
		else
			minula_pol->dalsi_prvek = akt_pol;
		akt_pol->vek = vek;
		strcpy(akt_pol->jmeno, jmeno);
		akt_pol->dalsi_prvek = NULL;
		minula_pol = akt_pol;
	}
		
	akt_pol = prvni_pol;
	
	printf ("Zadej jmeno, ktere chces vyhledat:\n");
	while (scanf("%s", jmeno) == 1) {
		while (1) {
			if (strcmp(jmeno, akt_pol->jmeno) == 0)
				printf ("Jmeno: %s, vek: %u\n", akt_pol->jmeno, akt_pol->vek);
			if (akt_pol->dalsi_prvek == NULL)
				break;
			akt_pol = akt_pol->dalsi_prvek;
		}
		akt_pol = prvni_pol;
	}
	
	while (1) {
		minula_pol = akt_pol;
		if (akt_pol->dalsi_prvek == NULL)
			break;
		akt_pol = akt_pol->dalsi_prvek;
		free(minula_pol);
	}		

	return 0;
}
