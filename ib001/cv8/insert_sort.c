#include <stdio.h>
#include <stdlib.h>

int main()
{

	srand(5);
	int data[21]={0};
	
	for (int i = 0; i<20; i++) {
		data[i+1] = rand();
		printf ("%i\n", data[i+1]);
	}
	printf("\n");
	
	int a;
	
	for (int i = 1; i < 21; i++ ) {
		a = data[i];
		for (int j = i-1; j >= 0; j-- ) {
			if ( data[j] > a )
				data[j+1] = data[j];
			else {
				data[j+1] = a;
				break;
			}
				
		}		
	}

	for (int i = 0; i<20; i++) {
		printf ("%i\n", data[i]);
	}
	printf("\n");

}
