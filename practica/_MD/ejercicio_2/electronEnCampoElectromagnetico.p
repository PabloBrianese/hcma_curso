#!/usr/bin/gnuplot

set title left
set title title

file_name='dat/electronEnCampoElectromagnetico.dat'

set output 'dat/electronEnCampoElectromagnetico.png'

set terminal png

set xrange [-15:15]
set yrange [-100:0]
set zrange [50:150]

set xlabel 'x [Angstrom]'
set xlabel offset -1,-1
set ylabel 'y [Angstrom]'
set ylabel offset 4,-1
set zlabel 'z [Angstrom]'
set zlabel offset -2

set lmargin at screen .3
set rmargin at screen .75
set bmargin at screen .3
set tmargin at screen .9

set key off

set xtics offset -1
set ytics offset 1

splot file_name using 2:3:4 with lines
