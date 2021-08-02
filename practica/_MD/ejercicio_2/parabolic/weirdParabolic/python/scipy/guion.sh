#!/bin/bash

source ../env/bin/activate

python3 electronEnCampoElectromagnetico.py
gnuplot -e "title='Integración con SciPy'" ../../electronEnCampoElectromagnetico.p

deactivate
