
set title "Simulación con LAMMPS"

file_name='dat/electronEnCampoElectrico.dat'

set output 'dat/electronEnCampoElectrico.png'

set terminal png

set key off

set xrange [0:1e-8]
set yrange [0:-1e-8]
set zrange [5e-9:15e-9]

set ztics 5e-9,2.5e-9
set xtics 0,2.5e-9
set ytics -1e-8,2.5e-9

set format x "%.1e"
set format y "%.1e"
set format z "%.1e"

set xlabel 'x [m]'
set xlabel offset -1,-1
set ylabel 'y [m]'
set ylabel offset 4,-1
set zlabel 'z [m]'
set zlabel offset -3

set lmargin at screen .3
set rmargin at screen .75
set bmargin at screen .3
set tmargin at screen .9

set tics out

set xtics offset -3
set ytics offset 3

splot file_name using 2:3:4 with lines
