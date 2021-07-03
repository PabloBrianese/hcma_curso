#!/bin/bash

source ../env/bin/activate

python3 electronEnCampoElectrico.py
gnuplot -e "title='Integración con SciPy'" ../../electronEnCampoElectrico.p

deactivate
