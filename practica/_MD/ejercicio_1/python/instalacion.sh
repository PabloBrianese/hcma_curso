#!/bin/bash

apt install python3 python3-pip python3-venv gnuplot

python3 -m venv

source env/bin/activate

python3 -m pip install numpy scipy

deactivate
