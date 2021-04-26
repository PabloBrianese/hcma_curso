#este guion de gnuplot genera la grafica de una funcion exponencial radial

set terminal png size 1000,1000

set isosamples 50,50

set output 'plot_b.png'

set title 'Plot (b)'

set xlabel 'Eje X'
set ylabel 'Eje Y'
set zlabel 'Eje Z'

set xrange [-3:3]
set yrange [-3:3]
set zrange [0:1]

splot exp((-1.0)*(x**2+y**2))
