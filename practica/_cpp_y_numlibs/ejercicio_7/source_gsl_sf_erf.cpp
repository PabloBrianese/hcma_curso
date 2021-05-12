#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <gsl/gsl_sf.h>

using namespace std;

int main(int argc, char* argv[]) {
  // Error en el número de argumentos recibidos
  if (argc != 4) exit(EXIT_FAILURE);

  // Argumentos pasados por línea de comandos
  int N = atoi(argv[1]);
  double x_min = atof(argv[2]), x_max = atof(argv[3]);

  // Puntos de muestreo
  vector<double> xs;
  for (double t = 0.0; t < N; ++t) 
    xs.push_back((x_max - x_min) * (t / (N - 1)) + x_min);

  // Muestreo
  for (double x : xs) cout << x << " " << gsl_sf_erf(x) << endl;
}
