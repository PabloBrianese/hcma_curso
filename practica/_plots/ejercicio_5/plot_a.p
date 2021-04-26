#este guion de gnuplot genera la grafica de una silla de montar

set terminal png size 1000,1000

set isosamples 50,50

set output 'plot_a.png'

set title 'Plot (a)'

splot x**2-y**2
