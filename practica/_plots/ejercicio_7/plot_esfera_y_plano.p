#este guion de gnuplot genera la grafica de una esfera y un plano

set terminal png size 1000,1000

set isosamples 50,50

set output 'plot_esfera_y_plano.png'

set title 'Plot (esfera y plano)'

set xlabel 'Eje X'
set ylabel 'Eje Y'
set zlabel 'Eje Z'

set ticslevel 0

set xrange [-2:2]
set yrange [-2:2]
set zrange [-2:2]

set view equal xyz

set view 80, 30

set hidden3d

set parametric

splot u, v, 0, \
      cos(u)*sin(v), sin(u)*sin(v), cos(v)
