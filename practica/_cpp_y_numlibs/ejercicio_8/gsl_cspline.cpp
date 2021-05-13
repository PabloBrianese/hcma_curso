#include <iostream>
#include <algorithm>
#include <gsl/gsl_spline.h>

using namespace std;

int main() {
  // Datos
  const size_t N_DATOS = 5;
  const double xa[N_DATOS] = {-4.0, -2.0, 0.0, 3.0, 5.0};
  const double ya[N_DATOS] = {10.0, -6.0, 2.0, -1.0, 8.0};
  const double x_min = *min_element(xa, xa + N_DATOS);
  const double x_max = *max_element(xa, xa + N_DATOS);

  // Inicialización de la interpolación
  gsl_interp_accel* accel_ptr = gsl_interp_accel_alloc();
  gsl_spline* spline_ptr = gsl_spline_alloc(gsl_interp_cspline, N_DATOS);
  // Ajuste de la interpolación a los datos
  gsl_spline_init(spline_ptr, xa, ya, N_DATOS);

  // Muestreo de la curva interpolada
  const int N_INTERP = 1000;
  double x;
  for (double t = 0.0; t < N_INTERP; ++t) {
    x = (x_max - x_min) * t / (N_INTERP - 1) + x_min;
    cout << x << " " << gsl_spline_eval(spline_ptr, x, accel_ptr) << endl;
  }

  // Delocación de la interpolación
  gsl_spline_free(spline_ptr);
  gsl_interp_accel_free(accel_ptr);
}
