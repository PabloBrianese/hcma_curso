#include <iostream> /* cout */
#include <cstdlib>  /* exit, EXIT_FAILURE */
#include <string>  /* string */
#include <gsl/gsl_rng.h>  /* gsl_rng_type, gsl_rng, gsl_rng_env_setup, gsl_rng_default, gsl_rng_default_seed, gsl_rng_alloc, gsl_rng_free, gsl_rng_set */
#include <gsl/gsl_randist.h>  /* gsl_ran_gaussian, gsl_ran_lognormal */

using namespace std;

// Distribución de probabilidad a muestrear
// "gsl_ran_gaussian" |--> normal
// "gsl_ran_lognormal" |--> lognormal
#define DIRECTIVA "gsl_ran_gaussian"

double aleatorio_preprocesador(gsl_rng*, const string);

int main(int argc, char* argv[]) {
    if (argc != 2) { exit(EXIT_FAILURE); }

    // Número de muestras a generar
    const int N = atoi(argv[1]);

    // Tipo de generador
    const gsl_rng_type* T = gsl_rng_default;  // default = gsl_rng_mt1997
    // Puntero al generador
    gsl_rng* r = gsl_rng_alloc(T);
    // Semilla del generador
    gsl_rng_set(r, gsl_rng_default_seed);  // default = 0

    // Muestreo y salida a la consola
    for (int i = 0; i < N; ++i)
        cout << aleatorio_preprocesador(r, DIRECTIVA) << endl;

    // Se libera la memoria usada por el generador
    gsl_rng_free(r);
}

double aleatorio_preprocesador (gsl_rng* r, const string distribution) {
    if (distribution == "gsl_ran_gaussian") {
        return gsl_ran_gaussian(r, 1.0);
    }
    else if (distribution == "gsl_ran_lognormal") {
        return gsl_ran_lognormal(r, 0.0, 1.0);
    }
    else { exit(EXIT_FAILURE); }
}
