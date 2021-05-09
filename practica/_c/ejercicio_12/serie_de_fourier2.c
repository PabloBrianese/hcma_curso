#include <stdio.h>
#include <stdlib.h>		/* ceil, sin, itoa */
#include <math.h>		/* M_PI */

double funcion (double x);
double serie_senos(double x, unsigned N);

#define N_MUESTRA 10000

int main () {
	// Variable independiente, valor de la función, serie de fourier
	double x, f, y;

	// Orden de aproximación en la serie de fourier
	unsigned N = 0;
	printf("Ingresar el número de términos que debe incluise en la serie de fourier:\n");
	scanf("%d", &N);  // El valor de N se obtiene del usuario

	// Nombre del archivo que contendrá la tabla
	char nombre_de_archivo[100];
	sprintf(nombre_de_archivo, "tabla_fourier%d.csv", N);
	// Creamos la tabla como archivo CSV
	FILE *tabla = fopen(nombre_de_archivo, "w");

	for (int i = 0; i <= N_MUESTRA; ++i) { 
		// Calculamos los valores que irán al archivo
		x = 6 * M_PI * ((double) i / N_MUESTRA) - 3 * M_PI;
		f = funcion(x);
		y = serie_senos(x, N);
		// Escribimos al archivo en formato CSV
		fprintf (tabla, "%f,%f,%f\n", x, f, y);
	}

	// Cerramos el archivo de texto
	fclose(tabla);

	return 0;
}

double funcion (double x) {
	// Onda cuadrada -1, 1, -1, 1, ...
	return 	-1 * (((int)ceil(x / M_PI) % 2) == 0) 
			+ 1 * (((int)ceil(x / M_PI) % 2) != 0);
}

double serie_senos(double x, unsigned N) {
	// Serie de Fourier de la onda cuadrada
	// Inicialización
	double sum = 0.0;
	// Suma sobre números impares
	for (int k = 0; 2*k+1 <= N; ++k) {
		sum += ((double) 4 / ((2*k+1) * M_PI)) * sin((2*k+1) * x);
	}
	return sum;
}
