#include <cstdlib>  /* system */
#include <cmath>  /* exp, sin */
#include <array>  /* array */
#include <fstream>  /* ofstream */

using namespace std;

double f (double);  // Función a graficar

int main(void) {
    // Puntos de muestreo de la función en el intervalo [- 10, 10]
    array<double, 1000> xs;
    for (double t = 0.0; t < xs.size(); ++t) 
        xs[i] = 20 * (t / (xs.size() - 1)) - 10;

    // Creamos un archivo de texto
    ofstream archivo;
    archivo.open ("tabla.dat");

    // Escribimos sobre el archivo de texto
    for (double x : xs) archivo << x << " " << f(x) << endl;

    // Cerramos el archivo de texto
    archivo.close();

    // Graficamos con xmgrace
    system("xmgrace tabla.dat");
}

// Definimos la función
double f (double x) { return exp(x) * sin(2 * x); }
