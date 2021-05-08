#!/bin/bash

gcc cuadraticaA1B1C1.c -o cuadraticaA1B1C1.out -lm
gcc cuadraticaA2B4C2.c -o cuadraticaA2B4C2.out -lm
gcc cuadraticaA3B0C-20.c -o cuadraticaA3B0C-20.out -lm

./cuadraticaA1B1C1.out
./cuadraticaA2B4C2.out
./cuadraticaA3B0C-20.out
