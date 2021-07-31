



echo "Listo! Comenzamos el postprocesado..."

postProcess -func "mag(U)"

#postProcess -func "mag(UA)"

postProcess -func perfil_axial_magU
echo "Ya procesamos el archivo perfil_axial_magU"
echo "."
sleep 1

#postProcess -func perfil_axial_magUA
#echo "Ya procesamos el archivo perfil_axial_magUA"
#echo "."
#sleep 1

echo "Listo! Toda la salida se puede encontrar en el directorio postProcessing"
