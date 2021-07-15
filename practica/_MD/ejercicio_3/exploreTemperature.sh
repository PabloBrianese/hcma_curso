#!/usr/bin/bash

for temperatura in {100..2000..100}
do
  lmp_ubuntu -var Temperatura $temperatura -in ArgonLJ.lammps
done
