#!/usr/bin/bash

#Correr con 
#mpirun -np 2 lammps19 -sf opt < ArgonLJ.lammps
#si se quiere usar la definicion de una variable  desde linea de
#comandos usar:
#lammps19 -var extern valor -sf opt < ArgonLJ.lammps


lmp_ubuntu -in ArgonLJ.lammps