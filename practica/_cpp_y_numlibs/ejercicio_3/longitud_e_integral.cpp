#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdlib>
#include <cmath>

using namespace std;

int main() {
    vector<double> xs, ys;

	// Cantidades a calcular
    double longitud = 0.0, integral = 0.0;

    // Incorporación de los datos
    ifstream archivo;
    archivo.open("MuestreoCurvaXY.dat");

    string linea, stringx, stringy;
    unsigned coma;
    while (getline(archivo, linea)) {
        coma = linea.find(',');
        stringx = linea.substr(0, coma);
        stringy = linea.substr(coma + 1, string::npos);

        xs.push_back(atof(stringx.data()));
        ys.push_back(atof(stringy.data()));
    }
    archivo.close();

    // Cálculo de la longitud y la integral
    for (int i = 1; i < xs.size(); ++i) {
        longitud += 
			pow(
				pow(xs[i] - xs[i-1], 2.0) +
				pow(ys[i] - ys[i-1], 2.0),
				0.5
			);

        integral +=
            0.5 * (ys[i] + ys[i-1]) * (xs[i] - xs[i-1]);
    }
    // Informe
    cout 
        << "La longitud de la curva es" << endl
        << longitud << endl
        << "La integral de la función es" << endl
        << integral << endl;
}