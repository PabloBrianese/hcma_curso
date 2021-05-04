#include <stdio.h>

int main(void) 
{
	int n;
	long int fib;
	long int fib1 = 1;
	long int fib2 = 1;

	printf("%ld \n", fib1);
	printf("%ld \n", fib2);

	for (n = 1; n <= 48; n++) {
		fib = fib2 + fib1;
		printf("%ld \n", fib);

		// Actualización
		fib1 = fib2;
		fib2 = fib;
	}

	return 0;
}
