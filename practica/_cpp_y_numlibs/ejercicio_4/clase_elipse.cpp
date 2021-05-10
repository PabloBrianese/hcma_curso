#include <iostream>
#include <cmath>

class Elipse {
    private:
    double centro_x, centro_y;
    double semieje_mayor, semieje_menor;

    public:
    void cambiar_centro (double, double);
    void cambiar_semiejes (double, double);
    void imprimir_centro ();
    void imprimir_semiejes ();
    void imprimir_area ();
}; 

void Elipse::cambiar_centro (double x, double  y) {
    centro_x = x;
    centro_y = y;
}

void Elipse::cambiar_semiejes (double mayor, double menor) {
    semieje_mayor = mayor;
    semieje_menor = menor;
}

void Elipse::imprimir_centro () {
    std::cout
        << "Centro: "
        << "(" << centro_x << ", " 
        << centro_y << ")"
        << std::endl;
}

void Elipse::imprimir_semiejes () {
    std::cout 
        << "Semieje mayor: "
        << semieje_mayor 
        << std::endl
        << "Semieje menor: "
        << semieje_menor 
        << std::endl;
}

void Elipse::imprimir_area () {
    std::cout 
        << "Área: "
        << semieje_mayor * semieje_menor * M_PI
        << std::endl;
}

int main () { 
    Elipse elip;
    elip.cambiar_centro (0.0, 0.0);
    elip.cambiar_semiejes (5.0, 3.0);
    elip.imprimir_centro ();
    elip.imprimir_semiejes ();
    elip.imprimir_area ();
 
    return 0;
}