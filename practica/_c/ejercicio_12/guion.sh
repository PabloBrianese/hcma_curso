#!/bin/bash

gcc serie_de_fourier2.c -o serie_de_fourier2.out -lm

# Crear tablas
./serie_de_fourier2.out 2
./serie_de_fourier2.out 5
./serie_de_fourier2.out 10
./serie_de_fourier2.out 100
