/*
    Napište program, který bude číst celá čísla (typu int) ze standardního vstupu, dokud budou přicházet (do konce souboru nebo do zadání nevhodného vstupu).
    Program načtené číslo analyzuje a vypíše, kolik obsahuje jednotlivých číslic (od 0 do 9).
    Takto zpracuje pouze nezáporná čísla.
    Obdrží-li program číslo záporné, vypíše pouze chybovou hlášku a bude číst dál bez analýzy záporného čísla.
    Příklad výstupu programu je připojen níže.
    Jen připomínám, že na na příkazové řádce nasimulujete konec souboru stisknutím CTRL+D pod Unix-like systémy a CTRL+Z (a pak ENTER, je-li třeba) pod MS-like systémy.
    Pozor, je třeba být na začátku řádku, takže zadáváte-li čísla za sebou, je třeba zmáčknout klávesu ENTER a pak teprve simulovat konec souboru.

Nabízených řešení je mnoho, lze použít několik proměnných, pole (což jsme zatím nedělali) či číslo typu unsigned long long int (formátovací značka %llu) jako úložiště počtu číslic. Můžete předpokládat, že na vstup nepřijde číslo příliš velké (musí se vejít do proměnné typu int). Počet číslic však může dosáhnout 10, např. 1111111111 by mělo být akceptovatelné na většině implementací. 
*/

#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	
	int cislo, i;
	int pocet[10] = { 0 };

	printf("Zadej celé číslo:\n");

	while (scanf("%d", &cislo) == 1) {
		if (cislo < 0) {
			printf ("Neplatný vstup!\nProgram akceptuje pouze celá nezáporné čísla\n");
		}
		else {
			printf( "Číslo %d se skládá z číslic:\n", cislo);
		
			do {
				i = cislo % 10;
				pocet[i]++;
				cislo /= 10;
			} while (cislo != 0);

			for (i = 0; i <= 9; i++ ) {
				printf( "%i ... %ix\n", i, pocet[i] );
				pocet[i] = 0;
			}
		}
	
		printf("\nZadejte další číslo:\n");

	}

	return 0;
}
