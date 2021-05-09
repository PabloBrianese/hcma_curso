#include <stdio.h>

int main () {
	// Número de términos en la suma parcial de la serie
	int N = 100;
	// Índice de la serie
	int k = 0;
	// Aproximación numérica al valor de la serie
	float serie = 0.0;

	// Primera suma
	for (; k < N; ++k)
		serie += (1 - 2 * (k % 2)) * ((float) 4 / (float) (2 * k + 1));
	// Informe
	printf(
		"Sumando %d términos de la serie se obtiene la aproximación\n"
		"%f\n",
		N, serie
	);

	// Se aumenta N en un orden de magnitud
	N *= 100;
	// Segunda suma
	for (; k < N; ++k)
		serie += (1-2*(k%2)) * ((float)4/(float)(2*k+1));
	// Informe
	printf(
		"Sumando %d términos de la serie se obtiene la aproximación\n"
		"%f\n",
		N, serie
	);

	// Se aumenta N en un orden de magnitud
	N *= 100;
	// Segunda suma
	for (; k < N; ++k)
		serie += (1-2*(k%2)) * ((float)4/(float)(2*k+1));
	// Informe
	printf(
		"Sumando %d términos de la serie se obtiene la aproximación\n"
		"%f\n",
		N, serie
	);

	// Conclusión
	printf("En el límite, el valor de la serie es igual al número pi.\n");

	return 0;
}