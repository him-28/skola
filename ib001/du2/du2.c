/* Zadání 2. domácího úkolu
 *
 * Napište program, který bude vyhledávat násobně se vyskytující „sekvence“ (podpole ;-)) v poli znaků.
 * Program se uživatele zeptá na počet znaků, kolik jich chce zadat a poté znaky načte do pole odpovídající délky.
 * Po načtení všech znaků program začne vyhledávat násobně se vyskytující sekvence délky 1, pak 2, 3, atd. až do délky pole-1.
 * Pokud by uživatel nezadal všechny avizované znaky, ohlašte chybu a program ukončete s návratovou hodnotou různou od 0, např. return 1;.
 * Nalezené sekvence vypíše na terminál s pozicí (indexem začátku pro jednoduchost) v poli, kde se vyskytují.
 * Sekvence se mohou v poli překrývat.
 * (Pro znalé C – nejedná se o řetězce, doopravdy se má jednat o obyčejná pole a je zakázáno pole znaků převést na C (null-terminated)
 * řetězce či jiné implementace řetězců a využívat funkcí, které s nimi umí pracovat, např. strstr(), strchr() apod.
 * Proto se schválně vyhýbám sousloví „vyhledávání podřetězce“.)
 *
 *
 * Příklad vstupu a výstupu
 *
 * Zadej pocet znaku: 8
 * Zadej znaky: aabaaaab
 *
 * Nalezene nasobne se vyskytující sekvence a indexy zacatku:
 * a: 0 1 3 4 5 6
 * b: 2 7
 * aa: 0 3 4 5
 * ab: 1 6
 * aab: 0 5
 * aaa: 3 4
 */

#include <stdio.h>
#include <stdlib.h>

int zkontroluj (unsigned char * znak, int pocet, int poz1, int delka )
{
	int celk_nalez = 0, i, nalez;

	for (int poz2 = poz1 + 1; poz2 <= pocet - delka; poz2++ ) {
		for (i = 0; i < delka; i++){
			if ( *(znak + poz1 + i) != *(znak + poz2 + i) ) {
				nalez = 0;
				break;
				}
			if ( i == delka - 1 )
				celk_nalez++;
				nalez = 1;
		}
		
		if ( celk_nalez == 1 && nalez ){
			for (i = 0; i < delka; i++){
				printf( "%c", *(znak + poz1 + i) );
			}
			printf(": %i", poz1);
		}

		if ( celk_nalez > 0 && nalez)
			printf (" %i", poz2);
	
	}

	if ( celk_nalez > 0 )
		printf ("\n");

	return celk_nalez;
}

/* Na rozdíl od funkce zkontroluj prochází pole směrem dopředu a pokud najde stejnou 
 *	sekvenci, tak vrátí jedničku. Optimálnější by pravděpodobně bylo nalezené násobné
 *	sekvence někde ukládat a nové sekvence kontrolovat s uloženými, nicméně jelikož nevíme
 * kolik jich bude ani jejich délku, bylo by asi potřeba pro ně alokovat paměť dynamicky.
 * Použité řešení bude fungovat pro jakoukoli délku pole znaků. 
 */
int predchozi_vyskyt (unsigned char * znak, int pocet, int poz1, int delka )
{
	for (int poz2 = poz1 - 1; poz2 >= 0; poz2-- ) {
		for (int i = 0; i < delka; i++){
			if ( *(znak + poz1 + i) != *(znak + poz2 + i) ) {
				break;
				}
			if ( i == delka - 1 )
				return 1;
		}
	}
		
	return 0;
}


int main(void)
{

	int pocet;

	printf("Zadejte, kolik znaků bude na vstupu: ");

	if ( scanf("%d ", &pocet) != 1 ) {
		printf ("Neplatný vstup!\nProgram akceptuje pouze celá přirozená čísla\n");
		return 1;
		}
	/*FIXME: better error handling?*/

	unsigned char znak[pocet];
	int i = 0;

	while ( scanf("%c", &znak[i] ) == 1 && i < pocet) {
		i++;
	}


	//printf ("\ni je: %i, pocet je: %i\n", i , pocet);

	if ( i < pocet ) {
		printf ("Bylo zadáno méně znaků než je potřeba\n");
		return 1;
	}

	for (int j = 0; j < i; j++) {
		printf ("%c", znak[j] ); 
	}

	printf ("\nNalezené násobně se vyskytující sekvence a indexy začátků:\n");

	for(int poz1 = 0; poz1 < pocet; poz1++) {
		for (int delka = 1; delka < pocet - poz1; delka++ ){
			if ( !predchozi_vyskyt (znak, pocet, poz1, delka) )
				zkontroluj(znak, pocet, poz1, delka);
		}
	}
	
	return 0;
}
