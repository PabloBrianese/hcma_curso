#este guion de gnuplot genera la grafica de una helice

set terminal png size 1000,1000

set isosamples 50,50

set output 'plot_a.png'

set title 'Plot (a)'

set xlabel 'Eje X'
set ylabel 'Eje Y'
set zlabel 'Eje Z'

set parametric

splot [0:5*pi] cos(u), sin(u), u/3
