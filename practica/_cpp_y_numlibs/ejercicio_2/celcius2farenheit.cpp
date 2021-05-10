#include <iostream>    /* cout, endl */
#include <cstdlib>	    	/* atof */
using namespace std;

int main (int argc, char* argv[]) {
  // Temperatura ingresada en grados Celcius (°C)
  float temp_celcius = atof(argv[1]);
  // Temperatura de salida en grados Farenheit (°F) 	
  float temp_farenheit = 1.8 * temp_celcius + 32.0;
  // Informe al usuario
  cout << temp_celcius << " °C"
       << " = " 
       << temp_farenheit << " °F" << endl;
}
