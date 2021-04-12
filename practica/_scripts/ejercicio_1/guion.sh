#!/bin/bash

# Generamos un archivo en el directorio actual
# que guarda la ruta del directorio actual
pwd > prueba.dat

# Insertamos una linea en blanco como separador
echo "" >> prueba.dat

# Agregamos la hora de creación del archivo en una nueva linea
date +%T >> prueba.dat

# Insertamos una linea en blanco como separador
echo "" >> prueba.dat

# Agregamos un calendario del año 2020
cal 2020 >> prueba.dat