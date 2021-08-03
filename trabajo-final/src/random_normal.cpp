#include <iostream>
#include <random>

int main() {
  // Utilizamos un URBG como fuente de aleatoriedad,
  // no un motor
  std::random_device rd;

  // Variable con distribución normal estándar
  // que toma valores de tipo double
  double mean1 = 0, stddev1 = 1;
  std::normal_distribution<double> d1{mean1, stddev1};

  // Variable con distribución normal
  // que toma valores de tipo float
  float mean2 = -2, stddev2 = 0.1415;
  std::normal_distribution<float> d2{mean2, stddev2};

  std::cout << "d1: \n";
  for (int i = 0; i < 16; ++i)
    std::cout << d1(rd) << " ";
  std::cout << std::endl;

  std::cout << "d2: \n";
  for (int i = 0; i < 16; ++i)
    std::cout << d2(rd) << " ";
  std::cout << std::endl;
}
