#include <stdlib.h>
#include <stdio.h>

int npow(int a, int b){
	int ret = 1;
	for (int i = 0; i < b; i++)
		ret *= a;
	return ret;
}

int fact(int a){
	int ret = 1;
	while(a > 0){
		ret *= a;
		a--;
	}
	return ret;
}

int sum(int num, int *data){
	int ret = 0;
	while(num != 0){
		ret += data[num-1];
		num--;
	}
	return ret;
}

float aver(int num, int *data){
	int sum = 0;
	int n = num;
	while(num != 0){
		sum += data[num-1];
		num--;
	}
	return (float)sum / n;
}

int binom(int top, int bot){
	return fact(top) / (fact(bot) * fact(top - bot));
}

int prime(int a){
  if(a == 2)
		return 1;
	if(a == 1 || a % 2 == 0)
		return 0;
	for(int i = 3; i <= a / 2; i += 2)
		if((a % i) == 0){
			return 0;
		}
	return 1;
}

int main(){

	char op;
  printf("> ");

	while(scanf("%c", &op) != EOF){

		int n1, n2;
		float fn1, fn2;
	  int *data;

		switch(op){

			case '+':
				scanf("%i %i", &n1, &n2);
				printf("# %i\n", n1 + n2);
				break;

			case '-':
				scanf("%i %i", &n1, &n2);
				printf("# %i\n", n1 - n2);
				break;

			case '/':
				scanf("%f %f", &fn1, &fn2);
				printf("# %.3f\n", fn1 / fn2);
				break;

			case 'd':
				scanf("%i %i", &n1, &n2);
				printf("# %i\n", n1 / n2);
				break;

			case 'm':
				scanf("%i %i", &n1, &n2);
				printf("# %i\n", n1 % n2);
				break;

			case '*':
				scanf("%i %i", &n1, &n2);
				printf("# %i\n", n1 * n2);
				break;

			case '^':
				scanf("%i %i", &n1, &n2);
				printf("# %i\n", npow(n1, n2));
				break;

			case '!':
				scanf("%i", &n1);
				printf("# %i\n", fact(n1));
				break;

			case 's':
				scanf("%i", &n1);
				if((data = (int*)malloc(n1 * sizeof(int))) == NULL){
					printf("failed to allocate memory\n");
					exit(1);
				}
				for(int i = 0; i < n1; i++)
					scanf("%i", &data[i]);
				printf("# %i\n", sum(n1, data));
				free(data);
				break;

			case 'a':
				scanf("%i", &n1);
				if((data = (int*)malloc(n1 * sizeof(int))) == NULL){
					printf("failed to allocate memory\n");
					exit(1);
				}
				for(int i = 0; i < n1; i++)
					scanf("%i", &data[i]);
				printf("# %.3f\n", aver(n1, data));
				free(data);
				break;

			case 'c':
				scanf("%i %i", &n1, &n2);
				printf("# %i\n", binom(n1, n2));
				break;

			case 'p':
				scanf("%i", &n1);
				printf("# %s\n", prime(n1) ? "yes" : "no");
				break;

			default:
				printf("Unknown operation %c\n", op);
				break;
		}
	while(getchar() != '\n');
  	printf("> ");
	}

	return 0;
}
