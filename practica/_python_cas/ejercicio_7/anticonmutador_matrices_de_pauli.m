#!/usr/bin/octave -qf

# este guion de octave calcula los anticonmutadores de las matrices de pauli

disp('Las matrices de Pauli son')
sigma_x = [0 1; 1 0]
sigma_y = [0 -i; i 0]
sigma_z = [1 0; 0 -1]

function retval = anticonmutador (A,B)
  retval = A*B + B*A;
endfunction

disp('Con ayuda de Octave, calculamos sus anticonmutadores')
disp ('{sigma_x, sigma_y} ='), disp (anticonmutador(sigma_x, sigma_y))
disp ('{sigma_x, sigma_z} ='), disp (anticonmutador(sigma_x, sigma_z))
disp ('{sigma_y, sigma_z} ='), disp (anticonmutador(sigma_y, sigma_z))
