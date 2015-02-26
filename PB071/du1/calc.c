#include <stdlib.h>
#include <stdio.h>

/* FIXME: do printing in functions... */

typedef struct {
	int narg;
	int *args;
	char ret_type;
	int iret;
	float fret;
	char *sret[4];
} cont;

void add(cont *a){
	printf("%i\n", a->args[0] + a->args[1]);
}

void sub(cont *a){
	printf("%i\n", a->args[0] - a->args[1]);
}

void divide(cont *a){
	printf("%.3f\n", (float)a->args[0] / a->args[1]);
}

void idiv(cont *a){
	printf("%i\n", a->args[0] / a->args[1]);
}

void mod(cont *a){
	a->iret = a->args[0] % a->args[1];
}

void mult(cont *a){
	a->iret = a->args[0] * a->args[1];
}

void npow(cont *a){
	a->iret = 1;
	for (int i = 0; i < a->args[1]; i++)
		a->iret *= a->args[0];
}

void fact(cont *a){
	a->iret = 1;
	while(a->args[0] > 0){
		a->iret *= a->args[0];
		a->args[0]--;
	}
}

void sum(cont *a){
	a->iret = 0;
	while(a->args[0] != 0){
		a->iret += a->args[a->args[0]];
		a->args[0]--;
	}
}

void aver(cont *a){
	int tot = 0;
	int n = a->args[0];
	while(a->args[0] != 0){
		tot += a->args[a->args[0]];
		a->args[0]--;
	}
	a->fret = tot / n;
}

void prime(cont *a){
	if(a->args[0] == 1){
		printf("no\n");
		return;
	}
	for(int i = 2; i <= a->args[0] / 2; i++)
		if((a->args[0] % i) == 0){
			printf("no\n");
			return;
		}
	printf("yes\n");
}

int main(){

	struct optable{
		char op;
		unsigned min_arg;
		unsigned max_arg;
		char ret_type;
		void (*func)(cont *);
	} ops[] = {
		{'+', 2, 2, 'n', add},
		{'-', 2, 2, 'n', &sub},
		{'/', 2, 2, 'n', &divide},
		{'d', 2, 2, 'n', &idiv},
		{'m', 2, 2, 'i', &mod},
		{'*', 2, 2, 'i', &mult},
		{'^', 2, 2, 'i', &npow},
		{'!', 1, 1, 'i', &fact},
		{'s', 1, 0, 'i', &sum},
		{'a', 1, 0, 'f', &aver},
//		{'c', 2, 2, 'i',},
		{'p', 1, 1, 'n', &prime},
	};

	char op;
	while(scanf("%c", &op) != EOF){

		for(unsigned i = 0; i < sizeof(ops) / sizeof(ops[0]); i++){

			/* find correct operation in the operations table */
			if(ops[i].op == op){
				cont data;
				data.args = NULL;
				int temp;
				unsigned narg = 0;

				/* read integer input values and store them in data structure */
				while(scanf("%i", &temp) == 1){
					if((data.args = realloc(data.args, ++narg * sizeof(int))) == NULL){
						printf("Failed to allocate memory\n");
						return 1;
					}
					data.args[narg - 1] = temp;

					/* new line means end of expression */
					if(getchar() == '\n')
						break;
				}
				data.narg = narg;

				/* check the right number of arguments */
				if(narg < ops[i].min_arg){
					printf("Not enough arguments\n");
					break;
				}
				if(ops[i].max_arg < narg && ops[i].max_arg != 0){
					printf("Too many arguments, ingnoring the superfluous ones\n");
				}

				/* call coresponding function */
				ops[i].func(&data);

				/* print output with correct type */
				if(ops[i].ret_type == 'i')
					printf("%i\n", data.iret);
				else if(ops[i].ret_type == 'f')
					printf("%.3f\n", data.fret);

				/* clean up */
				free(data.args);
				break;

			}
			else if(i == sizeof(ops) / sizeof(ops[0]) - 1)
				printf("Unknown operation %c\n", op);
		}
	}	

	return 0;
}
