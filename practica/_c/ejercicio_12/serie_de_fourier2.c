#include <stdio.h>
#include <stdlib.h>		/* ceil, sin, atoi */
#include <math.h>		/* M_PI */

double funcion (double x);
double serie_senos(double x, unsigned N);

int main (int argc, char *argv[]) {
	static int N_MUESTRA = 10000;
	// Variable independiente, valor de la función, serie de fourier
	double x, f, y;

	// Orden de aproximación en la serie de fourier
	// El valor de N se obtiene desde la terminal
	int N =  atoi(argv[1]);

	// Nombre del archivo que contendrá la tabla
	char nombre_de_archivo[100];
	sprintf(nombre_de_archivo, "tabla_fourier%d.csv", N);
	// Creamos la tabla como archivo CSV
	FILE *tabla = fopen(nombre_de_archivo, "w");

	for (int i = 0; i < N_MUESTRA; ++i) { 
		// Calculamos los valores que irán al archivo
		x = 6.0 * M_PI * ((double) i / (double) N_MUESTRA) - 3.0 * M_PI;
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
	int paridad = (int) ceil(x / M_PI) % 2;
	return 	-1 * (paridad == 0) + 1 * (paridad != 0);
}

double serie_senos(double x, unsigned N) {
	// Serie de Fourier de la onda cuadrada
	// Inicialización
	double sum = 0.0;
	// Suma sobre números impares
	for (int i = 1; i < N; i += 2)
		sum += (4.0 / (i * M_PI)) * sin(i * x);

	return sum;
}
