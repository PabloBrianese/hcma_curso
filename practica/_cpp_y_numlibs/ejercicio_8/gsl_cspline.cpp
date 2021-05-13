#include <fstream>
#include <gsl/gsl_spline.h>

#define N_DATOS 5
#define N_INTERP 1000

int main() {
  // Datos
  double xa[N_DATOS] = {-4, -2, 0, 3, 5};
  double ya[N_DATOS] = {10, -6, 2, -1, 8};

  // Inicialización de la interpolación
  gsl_interp_accel* accel_ptr = gsl_interp_accel_alloc();
  gsl_spline* spline_ptr = gsl_spline_alloc(gsl_interp_cspline, N_DATOS);
  // Ajuste de la interpolación a los datos
  gsl_spline_init(spline_ptr, xa, ya, N_DATOS);

  // Muestreo de la curva interpolada
  std::ofstream archivo;
  archivo.open("gsl_cspline.dat");
  double x, y;
  for (int i = 0; i <= N_INTERP; ++i) {
    x = 9 * (double) i / N_INTERP - 4;
    y = gsl_spline_eval(spline_ptr, x, accel_ptr);
    archivo << x << " " << y << std::endl;
  }
  archivo.close();
  
  // Delocación de la interpolación
  gsl_spline_free(spline_ptr);
  gsl_interp_accel_free(accel_ptr);

  return 0;
}
