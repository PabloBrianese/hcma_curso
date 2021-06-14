
set terminal png size 1000,1000

file_name='dat/solucionAnalitica.dat'

set output 'dat/solucionAnalitica.png'

splot file_name using 2:3:4 with lines
