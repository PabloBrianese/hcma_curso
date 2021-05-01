#!/bin/bash

pipenv run python3 ../con_numpy/regresion_numpy.py ../datos/datos2.csv
pipenv run python3 ../con_sklearn/regresion_sklearn.py ../datos/datos2.csv

pipenv run python3 sklearn_vs_numpy.py regresion_sklearn.csv regresion_numpy.csv
