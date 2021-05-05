#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(void) {
	const int N = 1000;
	double x, y;
	FILE * fptr;

	// Definimos la función
	double my_function (double x) {
		return exp(x) * sin(2 * x);
	}

	// Creamos un archivo de texto csv
	system("touch tabla.dat");

	// Dirigimos el puntero hacia el archivo
	fptr = fopen ("tabla.dat", "w+");
	for (int i = 0; i < N; i++) {
		// Calculamos los valores x, y
		x = 20.0 * ((double) i / (double) (N - 1)) - 10;
		y = my_function(x);

		// Insertamos la información en el archivo
    	fprintf(fptr, "%g,%g\n", x, y);
	}
	// Cerramos el archivo
	fclose(fptr);

	return 0;
}
