/*
 * Fahrenheit na stupne Celsia
 *        
 * TODO:
 *  0. Problem s prekladem
 *  1. Problem s celociselnym delenim, implicitni konverze datovych typu
 *  2. Vypis promennych na vice cislic
 *  3. Konstanty jako realna cisla
 *  4. Promenne jako realna cisla
 *  5. Vypis promennych na vice desetinnych mist
 *  6. Vyuziti prikazu for
 *  7. Symbolicke konstanty
 *                                                   
 */
     
   #include <stdio.h>

    int main(void) {
	const int SHIFT = 32;
	const double RATIO = 5.0/9.0;
    	float celsius = 0;        // promenna pro stupne celsia
    	int dolni = 0;		// pocatecni mez tabulky
    	int horni = 300;	// horni mez
    	int krok = 20;		// krok ve stupnich tabulky
     
    	for (int fahr = dolni; fahr <= horni; fahr += krok) {
    		celsius = (fahr - 32) * 5.0 / 9;
    		printf("%d \t %.2f \n", fahr, celsius); // vypise prevod pro konkretni hodnotu fahrenheita
    	}
    	return 0;
    }


