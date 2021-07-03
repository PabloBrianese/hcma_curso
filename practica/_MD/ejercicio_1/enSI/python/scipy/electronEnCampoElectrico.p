
set title "Integración con SciPy"

file_name='dat/electronEnCampoElectrico.dat'

set output 'dat/electronEnCampoElectrico.png'

set terminal png

set key off

splot file_name using 2:3:4 with lines
