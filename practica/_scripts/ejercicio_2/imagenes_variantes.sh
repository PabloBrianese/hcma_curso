# Cambiamos el nivel de compresión de la imagen original
convert ./datos/Ej2_aux.jpg -quality 1 ./datos/Ej2_aux_quality.jpg

# Suavizamos los bordes de la imagen original en estilo viñeta
convert ./datos/Ej2_aux.jpg -vignette 200x200 ./datos/Ej2_aux_vignette.jpg

# Cambiamos la imagen original para simular un dibujo en carbonilla
convert ./datos/Ej2_aux.jpg -charcoal 1 ./datos/Ej2_aux_quality.jpg