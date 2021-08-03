#!/bin/bash

#Correr con
#mpirun -np 2 lammps19 -sf opt < ElectronEnCampoEyB.lammps
#si se quiere usar la definicion de una variable  desde linea de
#comandos usar:
#lammps19 -var extern valor -sf opt < ElectronEnCampoEyB.lammps


# Campo eléctrico no nulo # Campo magnético no nulo
lmp_ubuntu \
  -v vx_ini 0 -v vy_ini 0 -v vz_ini 1\
  -v Ex -0.00054854 -v Ey -1 -v Ez 0 \
  -v Bx 1 -v By 0 -v Bz 0 \
  -in electronEnCampoElectromagnetico.lammps\

gnuplot -e "title='Simulación con LAMMPS'" electronEnCampoElectromagnetico.p
