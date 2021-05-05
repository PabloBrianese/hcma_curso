#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(void)
{


	int es_primo (int n) {
		for (int r = 2; r <= sqrt(n); r++)
			if (n % r == 0) return 0;  // No es primo 

		return 1;  // Es primo
	}


	// Imprimir primos
	const int N = 10000;
	for (int n = 2; n <= N; ++n)
		if (es_primo(n)) printf("%d\n", n);
	
	return 0;
}