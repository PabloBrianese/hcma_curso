#!/bin/bash

source ../env/bin/activate

python3 electronEnCampoElectrico.py
gnuplot electronEnCampoElectrico.p

deactivate
