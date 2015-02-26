#include <stdio.h>
#include <stdbool.h>

unsigned reverse(unsigned n)
{
	unsigned ret = 0;

	while(n > 0){
		ret *= 10;
		ret += n % 10;
		n /= 10;
	}
	return ret;
}

bool is_palindrome(unsigned n)
{
	return n == reverse(n);
}

int main(void)
{
	int n;
	if (scanf("%d", &n) != 1) {
		printf("Chyba vstupu, chybi N\n");
		return 1;
	}
	for (int i = 0; i <= n; i++) {
		unsigned k;
		if (scanf("%u", &k) != 1) {
			printf("Chyba vstupu, chybi K_%d\n", i);
			return 1;
		}

		int p;

		for (p = 0; p < 1000 && !is_palindrome(k); p++) {
			k += reverse(k);
		}

		if (is_palindrome(k)) {
			printf("%d %u\n", p, k);
		} else {
			printf("Nenalezeno\n");
		}
	}

	return 0;
}
