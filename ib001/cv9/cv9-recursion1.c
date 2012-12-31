#include <stdio.h>

int sum (int a) {

	if (a == 1)
		return 1;
	else 
		return a + sum (a-1) ;
}

int main()
{
	int c;
	printf("Zadej číslo:");
	scanf ("%d", &c);
	printf ("suma %d = %d\n", c, sum(c));
	
	return 0;
}
