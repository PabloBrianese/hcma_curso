#!/bin/bash

source env/bin/activate

python3 electronEnCampoElectrico.py
gnuplot electronEnCampoElectrico.p

python3 solucionAnalitica.py
gnuplot solucionAnalitica.p

deactivate
