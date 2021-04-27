#este guion de gnuplot genera la grafica de un torbellino

set terminal png size 1000,1000

set isosamples 50,50

set output 'plot_b.png'

set title 'Plot (b)'

set xlabel 'Eje X'
set ylabel 'Eje Y'
set zlabel 'Eje Z'

set xrange [-15:15]
set yrange [-15:15]

set parametric

splot [0:10*pi] (u/2)*cos(u), (u/2)*sin(u), u/2
