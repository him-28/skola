#include<stdio.h>

int main(void) {
	int i = 10;
	int *pInt = NULL;
	int **ppInt = &pInt;

	pInt = &i;
	*pInt = 20;

	printf("i == %d,\t*pInt == %d,\t**ppInt = %d\n"
		, i, *pInt, **ppInt);
	printf("pInt =\t\t%ld,\n*ppInt =\t%ld,\nppInt =\t\t%ld\n",
		(long int)pInt, (long int)*ppInt, (long int)ppInt);

	return 0;
}

