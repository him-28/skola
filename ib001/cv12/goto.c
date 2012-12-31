#include <stdio.h>
#include <stdlib.h>

int main(){

	int size = 2;
	int matice[size][size];
	
	int i = 0;

	cyklus1:
	scanf("%i", &matice[i / size][i % size] );
	i++;
	if (i < size*size)
		goto cyklus1;
	
	i = 0;	
	
	printf("Zadali jste čísla:");
	
	cyklus2:
	printf("%i ", matice[i / size][i % size] );
	i++;
	if (i < size*size)
		goto cyklus2;
		
	return 0;
}
