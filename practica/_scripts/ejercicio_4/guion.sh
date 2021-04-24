#!/bin/bash

# Este guion crea un archivo GIF con un disco que describe una
# curva continua sobre el archivo Campo.jpg.
# Se espera encontrar el archivo Campo.jpg en el directorio
# donde se abre la terminal que ejecuta el guion.

# Especificamos el centro del disco inicial de la animacion
# Coordenada x
x0=130
# Coordenada y
y0=90
# Especificamos el radio del disco
r=7

# Especificamos el desplazamiento del disco en la i-ésima imagen
# con respecto al punto de inicio.
# Desplazamiento en la direccion x
DX=(0 5 10 15 20 25 20 15 10 5)
# Desplazamiento en la direccion y
DY=(0 2 4 4 2 0 -2 -4 -4 -2)

# Partiendo de los parametros previos construimos los caminos que
# recorreran el centro del disco y un punto destacado del circulo
# (que cumple la funcion de especificar el radio del disco)
for i in {0..9}
do
    X[$i]=$((${DX[$i]} + $x0)) #coordenada x del centro del disco
    P[$i]=$((${X[$i]} + $r))   #coordenada x del punto destacado
    Y[$i]=$((${DY[$i]} + $y0)) #coordenada y comun a ambos puntos
done

# Generamos los sucesivos archivos JPEG, dibujando un disco sobre Campo.jpg
# en la posicion dada por los arreglos X,Y,P
for i in {0..9}
do
    center="${X[$i]},${Y[$i]}"
    point="${P[$i]},${Y[$i]}"
    convert Campo.jpg -draw "circle $center $point" Campo_$i.jpg
done

# Generamos el archivo GIF
# a partir de las imagenes creadas en el bucle anterior.
convert -delay 20 Campo_*.jpg gif-animado.gif