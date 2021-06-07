
set terminal png size 1000,1000

file_name = './DatosElectronEnCampoElectromagnetico/ElectronEnCampo_IntensityMagn10IntensityElectr0.1NumPasosIntegracion1000000Dt1e-05__traza'

set output 'trazaElectron.png'

set view 80 -30

splot file_name using 2:3:4 with lines
