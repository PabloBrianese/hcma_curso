#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <gsl/gsl_sf.h>

// "gsl_sf_bessel_J0" |-->
// Función de Bessel de primera especie de orden 0.
// "gsl_sf_erf" |-->
// Función error
// "gsl_sf_hermite_func_ord4" |-->
// La función de Hermite de orden 4
#define DIRECTIVA "gsl_sf_hermite_func_ord4"

double funcion_especial (double x, std::string funcion_especial);

int main(int argc, char* argv[]) {
  if (argc == 1) {
    printf(
      "Ingresar número de muestras, y extremos inferior y superior del intervalo."
    );

    return 0;
  }

  // Argumentos pasados por línea de comandos
  unsigned N = (unsigned) atoi(argv[1]);
  double x_min = atof(argv[2]);
  double x_max = atof(argv[3]);

  // Fuanción especial
  std::string funcion_especial_str = DIRECTIVA ;

  // Escritura de la tabla
  std::string nombre_tabla 
    = "muestreo_" + funcion_especial_str + ".dat";
  std::ofstream muestreo;
  muestreo.open(nombre_tabla.data());
  double x;
  for (unsigned i = 0; i < N; ++i) {
    x = (x_max - x_min) * ((double) i / N) + x_min;
    muestreo << x << " " << funcion_especial(x, funcion_especial_str) 
             << std::endl;
  }
  muestreo.close();

  return 0;
}

double funcion_especial (double x, std::string funcion_especial_str) {
  if (funcion_especial_str == "gsl_sf_bessel_J0") {
    return gsl_sf_bessel_J0(x);
  }
  else if (funcion_especial_str == "gsl_sf_erf") {
    return gsl_sf_erf(x);
  }
  else if (funcion_especial_str == "gsl_sf_hermite_func_ord4") {
    return gsl_sf_hermite_func(4, x);
  }
  else {
    printf(
      "Error. Las opciones son\n"
      "gsl_sf_bessel_J0\n"
      "gsl_sf_erf\n"
      "gsl_sf_hermite_func_ord4\n"
    );
    exit(1);
  }
}
