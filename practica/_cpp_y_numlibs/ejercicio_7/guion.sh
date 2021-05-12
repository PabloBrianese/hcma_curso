#!/bin/bash

g++ source_gsl_sf_bessel_J0.cpp -o source_gsl_sf_bessel_J0.out -lm -lgslcblas -lgsl
g++ source_gsl_sf_erf.cpp -o source_gsl_sf_erf.out -lm -lgslcblas -lgsl
g++ source_gsl_sf_hermite_func_ord4.cpp -o source_gsl_sf_hermite_func_ord4.out -lm -lgslcblas -lgsl

./source_gsl_sf_bessel_J0.out 1000 0 10 > muestreo_gsl_sf_bessel_J0.dat
./source_gsl_sf_erf.out 100 -2 2 > muestreo_gsl_sf_erf.dat
./source_gsl_sf_hermite_func_ord4.out 10 -5 5 > muestreo_gsl_sf_hermite_func_ord4.dat
