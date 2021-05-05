#include <stdio.h>		// printf, NULL
#include <stdlib.h>		// srand, rand
#include <time.h>		// time

int main () 
{
	// Inicialización del PRNG
	srand(time(NULL));
	// Informe del resultado
	printf(
		"Resultado de la tirada de dados: %d\n", 
		(rand() % 6) + 1
	);

	return 0;
}