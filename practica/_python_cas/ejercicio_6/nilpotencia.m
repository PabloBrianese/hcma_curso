#!/usr/bin/octave -qf

# calcula el orden de nilpotencia de una matriz

matriz = [0 2 1 6; 0 0 1 2; 0 0 0 3; 0 0 0 0];

N=4;  # número de filas/columnas de la matriz cuadrada

for i = 1:N
  # calculamos la i-esisma potencia de la matriz
  printf ('matriz^%d = \n', cast(i, "char"));
  disp (matriz^i);
  if matriz^i == zeros(4,4)
    # si esta potencia es nula hallamos el orden de nilpotencia
    # y terminamos el programa. 
    printf ('El orden de nilpotencia de la matriz es:'), disp (i);
    return
  # si no es nula y hemos llegado a la ultima potencia concluimos que
  # concluimos que la matriz no es  nilpotente 
  elseif i == N
    display('La matriz no es nilpotente.')
  endif
endfor
