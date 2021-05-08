#include <stdio.h>		/* printf */
#include <math.h>		/* sqrt */

int main () {
	// Coeficientes del polinomio A x**2 + B x + C
	float A = 3.0, B = 0.0, C = - 20.0;
	// Discriminante
	float discriminante = B * B - 4 * A * C;
	// Raíces del polinomio
	float raiz1, raiz2, parte_real, parte_imaginaria;

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