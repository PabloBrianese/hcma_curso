#!/usr/bin/bash

g++ -o fourierSeriesSolution.out fourierSeriesSolution.cpp -lm

./fourierSeriesSolution.out > dat/fourierSeriesSolution.csv

python3 makeHeatmaps.py

convert -delay 100 dat/timestep* dat/fourierSeriesSolution.gif
