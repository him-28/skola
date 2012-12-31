#include <stdio.h>

void nacti (int * c, int size)
{
	if (size > 0){
		scanf ("%d", c);
		nacti (c+1, size-1);
	}
} 

void vypis (int * c, int size)
{
	if (size > 0){
		printf ("%i ", *c);
		vypis (c+1, size-1);
	}
}   


int main()
{
	int size = 10;
	int c[size];

	nacti(c, size);
	
	vypis(c, size);
	
	return 0;
}
