#include <stdio.h>		/* printf */
#include <stdlib.h>		/* atof */

int main (int argc, char **argv) {
	// Temperatura ingresada en grados Celcius (°C)
	float temp_celcius;
	// Temperatura de salida en grados Farenheit (°F)
	float temp_farenheit;

	// Comportamiento cuando NO se reciben argumentos
	if (argc == 1) {
		printf(
			"La temperatura de fusión del agua es  0 °C = 32 °F" "\n"
			"La temperatura de ebullición del agua es 100 °C = 212 °F" "\n"
			"Para convertir temperaturas de grados celcius a grados farenheit" "\n"
			"pase argumentos numéricos de tipo float al ejecutable." "\n"
		);
	}
	// Comportamiento cuando SÍ se reciben argumentos
	else {
		for (int i = 1; i < argc; ++i) {
			temp_celcius = atof(argv[i]);
			temp_farenheit = 1.8 * temp_celcius + 32.0;

			// Informe al usuario
			printf("%f °C = %f °F\n", temp_celcius, temp_farenheit);
		}
	}

	return 0;
}