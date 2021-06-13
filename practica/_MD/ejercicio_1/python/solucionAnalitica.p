
set terminal png size 1000,1000

file_name='solucionAnalitica.dat'

set output 'solucionAnalitica.png'

splot file_name using 2:3:4 with lines
