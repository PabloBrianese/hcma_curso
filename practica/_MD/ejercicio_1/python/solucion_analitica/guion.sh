#!/bin/bash

source ../env/bin/activate

python3 electronEnCampoElectrico.py
gnuplot -e "title='Solución Analítica" ../../electronEnCampoElectrico.p

deactivate
