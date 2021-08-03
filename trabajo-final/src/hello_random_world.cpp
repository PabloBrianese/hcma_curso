#include <iostream>
#include <random>
int main() {
  // Inicialización del motor mt19937 con una semilla 1729 
  std::mt19937 mt{1729};
  // Creación de una variable aleatoria
  // con distribución uniforme
  // en el rango de números enteros [0, 99]
  std::uniform_int_distribution<int> dist{0, 99};

  for (int i = 0; i < 16; ++i) {
    // Obtenemos los valores de la distribución dist
    // pasandole el motor mt como argumento.
    std::cout << dist(mt) << " ";
  }
  std::cout << std::endl;
}
