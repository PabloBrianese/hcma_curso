#include <iostream>
#include <fstream>
#include <array>
#include <string>

using namespace std;

constexpr auto filename = "Datos.dat";
constexpr auto NumIntervalos = 10;
constexpr auto NumNodos = NumIntervalos + 1;
constexpr auto DeltaX = 1.0 / double(NumIntervalos);

int main()
{
  array<double, NumNodos> y;
  y[0] = 5;  // condición inicial
  for (auto i = 1; i < NumNodos; ++i)
    y[i] = y[i - 1] / (1 + 3 * DeltaX);  // solución iterariva para el resto de los nodos


  ofstream Outfile (filename);
  Outfile << "# x_node y(x_node)" << endl;
  for (auto i = 0; i < NumNodos; ++i)
    Outfile << i * DeltaX << " " << y[i] << endl;

  cout << "Listo, solución por diferencias finitas guardadas en el archivo "
    << filename
    << endl;
}