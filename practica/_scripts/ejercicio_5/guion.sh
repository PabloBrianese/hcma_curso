#!/bin/bash

# este guion copia las lineas n..m de un archivo de texto ArchEntrada
# luego las pega en un archivo de texto ArchSalida

# asignamos nombres a los argumentos 
ArchEntrada=$1 ; ArchSalida=$2 ;
n=$3 ; m=$4 ;

cat $ArchEntrada |\
  head -n $m |\
  tail -n $(($m - $n + 1)) \
  >> $ArchSalida
