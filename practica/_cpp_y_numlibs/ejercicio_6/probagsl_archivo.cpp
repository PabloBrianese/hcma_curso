#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdlib.h>
#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>

using namespace std;

double aleatorio_preprocesador (gsl_rng*, const string);

// "gsl_ran_gaussian" |--> normal
// "gsl_ran_lognormal" |--> lognormal
#define DIRECTIVA "gsl_ran_gaussian"

int main(int argc, char* argv[]) {
    const int N = atoi(argv[1]);

    // puntero al generador de números pseudoaleatorios
    const gsl_rng_type* T;
    gsl_rng* r;

    gsl_rng_env_setup();

    T = gsl_rng_default;
    r = gsl_rng_alloc(T);

    vector<double> ys;
    for (int i = 0; i < N; ++i) ys[i] = aleatorio_preprocesador

    // Archivo de datos
    ofstream datos;
    datos.open("muestreo_" DIRECTIVA ".dat");
    for (int i = 0; i < N; ++i)
        datos  << aleatorio_preprocesador(r, DIRECTIVA) << endl;

    datos.close();

    gsl_rng_free (r);
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
