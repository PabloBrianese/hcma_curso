#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>

double aleatorio_preprocesador (gsl_rng*, const std::string);

// "gsl_ran_gaussian" |--> normal
// "gsl_ran_lognormal" |--> lognormal
#define DIRECTIVA "gsl_ran_gaussian"

int main(int argc, char* argv[]) {
    // Número de puntos aleatoios a generar
    if (argc == 1) {
	std::cout << "Ingresar un número de muestras a tomar"
	          << std::endl; 
        return 0;
    }

    const unsigned N = (unsigned) atoi(argv[1]);
    // puntero al generador de números pseudoaleatorios
    const gsl_rng_type* T;
    gsl_rng* r;

    gsl_rng_env_setup();

    T = gsl_rng_default;
    r = gsl_rng_alloc (T);

    // Archivo de datos
    std::ofstream datos;
    datos.open ("muestreo_" DIRECTIVA ".dat");
    for (unsigned i = 0; i < N; ++i) {
        datos << aleatorio_preprocesador(r, DIRECTIVA)
	      << std::endl;
    }
    datos.close();

    gsl_rng_free (r);

    return 0;
}

double aleatorio_preprocesador (gsl_rng* r, const std::string distribution) {
    if (distribution == "gsl_ran_gaussian") {
        return gsl_ran_gaussian(r, 1.0);
    }
    else if (distribution == "gsl_ran_lognormal") {
        return gsl_ran_lognormal(r, 0.0, 1.0);
    }
    else {
        exit(EXIT_FAILURE);
    }
}
