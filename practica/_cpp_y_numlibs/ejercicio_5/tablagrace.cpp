#include <stdio.h> 
#include <stdlib.h> 
#include <math.h>
#include <fstream>

double my_function (double);

#define NUM 1000

int main(void) {
    // Creamos y escribimos en un archivo de texto
    std::ofstream archivo;
    archivo.open ("tabla.dat");
    double x;
    for (int i = 0; i < NUM; i++) {
        x = 20 * ((double) i / (NUM - 1)) - 10;
        archivo << 
            x << " " << my_function(x) 
            << std::endl;
    }
    archivo.close();

    // Graficamos con xmgrace
    system("xmgrace tabla.dat");

    return 0; 
}

// Definimos la función
double my_function (double x) {         
    return exp(x) * sin(2 * x);     
}
