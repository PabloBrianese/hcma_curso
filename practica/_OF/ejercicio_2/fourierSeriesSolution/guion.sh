#!/usr/bin/bash

bash compile.sh

bash makeDataFile.sh

python3 makeHeatmaps.py

bash makeTimeEvolutionGIF.sh