#!/bin/bash

# Creamos un directorio para almacenar enlaces
mkdir bin

# Añadimos este nuevo directorio a PATH
export PATH="$PWD/bin:$PATH"

# Creamos un enlace suave/simbólico
ln --symbolic $PWD/transformar_csv_en_tsv.sh $PWD/bin/csv2tsv

