#include <iostream>
#include <vector>
using namespace std;

double promedio (double*, int);
double promedio (vector<double>);
double promedio (vector<float>);
double promedio (vector<int>);

int main() {
    static int N = 10;
    double carr[N];
    vector<double> doubles;
    vector<float> floats;
    vector<int> ints;

	// Arreglo tipo C de doubles
    for (int i = 0; i < N; ++i)
        carr[i] = (double) i;

    cout << "El promedio de carr es:" << endl
         << promedio(carr, N) << endl;

	// Vector de doubles
    for (int i = 0; i < N; ++i)
        doubles.push_back ((double) i);

    cout << "El promedio de doubles es:" << endl
         << promedio(doubles) << endl;

	// Vector de floats
    for (int i = 0; i < N; ++i)
        floats.push_back ((float) i);

    cout << "El promedio de floats es:" << endl
         << promedio(floats) << endl;

	// Vector de ints
    for (int i = 0; i < N; ++i)
        ints.push_back (i);

    cout << "El promedio de ints es:" << endl
         << promedio(ints) << endl;
}

// Sobrecarga de la función promedio
double promedio (double carr[], int N) {
    double suma = 0.0;
    for (int i = 0; i < N; ++i) suma += carr[i];

    return suma / (double) N;
}

double promedio (vector<double> doubles) {
    double suma = 0.0;
    for (double d : doubles) suma += d;

    return suma / doubles.size();
}

double promedio (vector<float> floats) {
    double suma = 0.0;
    for (float f : floats) suma += f;

    return suma / floats.size();
}

double promedio (vector<int> ints) {
    double suma = 0.0;
    for (int i : ints) suma += i;

    return suma / ints.size();
}
