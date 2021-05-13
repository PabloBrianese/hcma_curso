#!/bin/bash

g++ gsl_cspline.cpp -o gsl_cspline.out -lm -lgslcblas -lgsl

./gsl_cspline.out > gsl_cspline.dat
