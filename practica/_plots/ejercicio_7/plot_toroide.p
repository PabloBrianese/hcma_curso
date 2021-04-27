#este guion de gnuplot genera la grafica de un toroide

set terminal png size 1000,1000

set isosamples 50,50

set output 'plot_toroide.png'

set title 'Plot (toroide)'

set xlabel 'Eje X'
set ylabel 'Eje Y'
set zlabel 'Eje Z'

set parametric
R=3; r=2
splot [0:2*pi] [0:2*pi] (R+r*cos(u))*cos(v), (R+r*cos(u))*sin(v), r*sin(u)
