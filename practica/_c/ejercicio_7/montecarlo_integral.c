#include <stdio.h>  /* printf */
#include <stdlib.h>  /* rand, srand, RAND_MAX */
#include <math.h>  /* exp */
#include <time.h>  /* time */

int main ()
{
	// Número de puntos en cada aproximación
	static long N[4] = {0, 1000, 1000000, 100000000};
	// Coordenadas x, y de un punto aleatorio
	double x, y;
	// Variable de conteo
	long count = 0;
	// Resultados del cálculo
	double integral[3];


	// Inicialización del PRNG
	srand((unsigned int) time(NULL));

	// Cálculo de las aproximaciones mediante Monte Carlo
	for (int k = 0; k < 3; ++k) {
		// Conteo de los puntos que caen en el área debajo de la curva
		for (unsigned long i = N[k]; i < N[k + 1]; ++i) {
			// Punto aleatorio en el rectángulo que contiene a la gráfica
			x = (double) rand() / (double) RAND_MAX;
			y = (double) rand() / (double) RAND_MAX;

			if (y <= exp(- x)) ++count;
		}

		// Registro del valor de la integral en esta aproximación
		integral[k] = (double) count / (double) N[k + 1];
	}

	// Informe
	printf("Tomando puntos aleatorios en cantidades\n");
	for (int k = 0; k < 3; ++k) printf("%lu \n", N[k + 1]);

	printf("se obtienen las sucesivas aproximaciones\n");
	for (int k = 0; k < 3; ++k) printf("%lf \n", integral[k]);

	printf(
		"al valor de la integral de la función y = exp(- x) "
		"en el intervalo [0, 1]\n"
		"y se obtienen las sucesivas aproximaciones\n"
	);
	for (int k = 0; k < 3; ++k) 
		printf("%lf \n", 1.0 / (1.0 - (double) integral[k]));

	printf("al número e.\n");

	return 0;
}
