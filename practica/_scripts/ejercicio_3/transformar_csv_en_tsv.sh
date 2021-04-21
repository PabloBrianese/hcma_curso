#!/bin/bash

# El guion crea un archivo TSV a partir de uno CSV.
# El guion toma exactamente dos argumentos;
# el primero $1 es un archivo con formato CSV,
# y el segundo $2 es el nombre que se desea asignar al nuevo archivo TVS. 

# Se verifica que el usuario haya ingresado 2 argumentos
if [ "$#" -eq "2" ];
then
    
    # Si no hay error se crea un archivo de texto con nombre $2 que contiene
    # los datos de $1 pero en el cual se substituye cada aparicion de "," por un
    # caracter tabulador "\t".
    sed "s/,/\t/g" $1 > $2

else
    
    # Si el usuario ingresa mas o menos que dos argumentos, la funcion imprime
    # en la consola una explicacion del problema y del funcionamiento de csv2tsv.

    error="El numero de argumentos ingresado lleva a un error.
La funcion csv2tsv espera recibir dos argumentos;
un primer argumento con el archivo CSV que se deasea modificar;
y un segundo argumento con el nombre del archivo TSV que se desea crear."

    echo "$error"
fi