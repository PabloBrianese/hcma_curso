#este guion de gnuplot genera la grafica de un elipsoide

set terminal png size 1000,1000

set isosamples 50,50

set output 'plot_elipsoide.png'

set title 'Plot (elipsoide)'

set xlabel 'Eje X'
set ylabel 'Eje Y'
set zlabel 'Eje Z'

set view equal xyz

set parametric

splot [0:2*pi] [0:pi] 2*cos(u)*sin(v), 2*sin(u)*sin(v), cos(v)
