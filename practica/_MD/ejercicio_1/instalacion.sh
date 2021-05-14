#!/bin/bash

apt install openmpi-bin libjpeg-dev libpng-dev libfftw3-dev

cd /opt
git clone -b stable https://github.com/lammps/lammps.git

cd lammps/src
make yes-misc
make yes-molecule
make ubuntu

cd ~
mkdir bin
echo 'PATH=$PATH:~/bin' >> .bashrc
cd bin
ln --symbolic /opt/lammps/src/lmp_ubuntu
