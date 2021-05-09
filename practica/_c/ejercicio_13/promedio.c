#include <stdio.h>

// Declaración de funciones
double promedio (double vec[], int N);

int main() {
    // Tamaño del arreglo
    int N = 7;
    // Arreglo de tipo double
    double vec[N];

    // Asignación de valores al arreglo
    for (int i = 0; i < N; ++i) vec[i] = (double) i;

    // Informe
    printf("El promedio del arreglo\n");
    for (int i = 0; i < N; ++i) printf("%g, ", vec[i]);

    printf("\nes %f\n", promedio(vec, N));
    return 0;
}

double promedio (double vec[], int N) {
    // Calcular el promedio del arreglo
    double media = 0.0;
    for (int i = 0; i < N; ++i) media += vec[i];

    media /= (double) N;

    return media;
}
