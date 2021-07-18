#!/bin/bash
if [ "$#" != "2" ]; then
  echo -e "Numero incorrecto de argumentos.\n\n\n"
  echo -e "Uso del script:\t$0 DeltaT NumProcesadores\n"
  exit 1
fi


####################Testeado con OF6#####################
####################Testeado con OF6#####################
mfc_DeltaT=`echo "$1" | bc -l`

NumProcesadores=`echo "$2" | bc -l`

echo "numberOfSubdomains ${NumProcesadores};" > mfc_numberOfSubdomains.h

echo "Invocado como:" > invocacion.h 
echo "$0 $1 $2 " >> invocacion.h 


echo "//variables para el case" > mfc_foam_case_variables.h 
echo "mfc_DeltaT $mfc_DeltaT;" >> mfc_foam_case_variables.h 
#lo mismo en formato bash
echo "#variables para el case" > mfc_foam_case_variables.sh 
echo "mfc_DeltaT=$mfc_DeltaT" >> mfc_foam_case_variables.sh 

m4 blockMeshDictCaja.m4 > system/blockMeshDict
blockMesh
echo "Ya ejecutamos blockMesh"
echo "."
sleep 1
echo "."
sleep 1
echo "."
sleep 1



checkMesh
echo "Ya ejecutamos checkMesh"
echo "."
sleep 1
echo "."
sleep 1
echo "."
sleep 1

cp 0/T.org 0/T

setFields
echo "Ya ejecutamos setFields"
echo "."
sleep 1
echo "."
sleep 1
echo "."
sleep 1

echo "Listo! Ejecutamos scalarTransportFoam en paralelo"
rm -rf processor*
decomposePar
mpirun -np ${NumProcesadores} scalarTransportFoam -parallel 

