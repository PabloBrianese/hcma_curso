
set terminal png size 1000,1000

file_name = system('ls ./DatosElectronEnCampoElectromagnetico/ElectronEnCampo_IntensityMagn*IntensityElectr*NumPasosIntegracion*Dt*__traza')

set output 'trazaElectron.png'

set view 80 -30

set zrange [99:101]

splot file_name using 2:3:4 with lines
