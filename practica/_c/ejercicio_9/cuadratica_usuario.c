#include <stdio.h>		/* printf, scanf */
#include <stdlib.h>		/* exit */
#include <math.h>		/* sqrt */

int main () {
	// Coeficientes del polinomio
	float A, B, C;
	// Discriminante
	float discriminante;
	// Raíces del polinomio
	float raiz1, raiz2, parte_real, parte_imaginaria;

	// Indicación
	printf(
		"Se espera que los números ingresados sean de tipo float.\n"
	);
	// Pedido del coeficiente A al usuario
	printf	(
		"Ingresar el coeficiente principal A del polinomio\n"
		"A x^2 + B x + C\n"
	);
	scanf("%f", &A);
	if (A == 0) {  // Error. Interrumpe el programa.
		printf(
			"Error. "
			"El coeficiente principal del polinomio debe ser no nulo.\n"
		);
		exit(0);
	}

	// Pedido del coeficiente B al usuario
	printf(
		"Ingresar el coeficiente B del polinomio\n"
		"%f x^2 + B x + C\n",
		A
	);
	scanf("%f", &B);

	// Pedido del coeficiente C al usuario
	printf(
		"Ingresar el coeficiente C del polinomio\n"
		"%f x^2 + %f x + C\n",
		A, B
	);
	scanf("%f", &C),

	// Análisis del discriminante
	discriminante = B * B - 4 * A * C;
	if (discriminante > 0) {
		raiz1 = - B / (2.0 * A) + sqrt(discriminante) / (2.0 * A);
    raiz2 = - B / (2.0 * A) - sqrt(discriminante) / (2.0 * A);
    printf (
			"El polinomio "
			"%f x**2 + %f x + %f\n"
			"tiene dos raíces reales:\n"
			"%f, %f\n",
			A, B, C,
			raiz1, raiz2
		);
	}
	else if (discriminante < 0) {
    parte_real = - B / (2.0 * A);
    parte_imaginaria = sqrt(- discriminante) / (2.0 * A);
    printf (
			"El polinomio "
			"%f x**2 + %f x + %f\n"
			"tiene dos raíces complejas:\n"
			"%f + i %f, %f - i %f\n",
			A, B, C,
			parte_real, parte_imaginaria,
			parte_real, parte_imaginaria
		);
	}
	else {  // discriminante == 0
		raiz1 = - B / (2.0 * A);
		printf (
			"El polinomio "
			"%f x**2 + %f x + %f\n"
			"tiene una única raíz real:\n"
			"%f\n",
			A, B, C,
			raiz1
		);
	}

	return 0;
}