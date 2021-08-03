#include <iostream>
#include <random>

int main() {
  // Creamos una instancia rd de la clase random_device
  std::random_device rd;
  // y la llamamos para dar una semilla
  // al generador de números pseudo-aleatorios.
  std::mt19937 mt{rd()};
  std::uniform_int_distribution<int> dist{0, 99};
  for (int i = 0; i < 16; ++i) {
    std::cout << dist(mt) << " ";
  }
  std::cout << std::endl;
}
