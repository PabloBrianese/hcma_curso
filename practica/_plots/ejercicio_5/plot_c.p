#este guion de gnuplot genera la grafica de un polinomio radial

set terminal png size 1000,1000

set isosamples 50,50

set output 'plot_c.png'

set title 'Plot (c)'

set xlabel 'Eje X'
set ylabel 'Eje Y'
set zlabel 'Eje Z'

set xrange [-3:3]
set yrange [-3:3]
set zrange [-50:50]

splot 1 -2*(x**2 + y**2)
