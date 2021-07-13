#!/bin/bash

#Correr con
#mpirun -np 2 lammps19 -sf opt < ElectronEnCampoEyB.lammps
#si se quiere usar la definicion de una variable  desde linea de
#comandos usar:
#lammps19 -var extern valor -sf opt < ElectronEnCampoEyB.lammps

# Campo eléctrio nonulo # Campo magnético nonulo
lmp_ubuntu \
  -v Ex 0 -v Ey 0.1 -v Ez 0 \
  -v Bx 0 -v By 1 -v Bz 0 \
  -in ../electronEnCampoElectromagnetico.lammps\
  -log none

gnuplot -e "title='Simulación con LAMMPS'" ../electronEnCampoElectromagnetico.p
