#!/usr/bin/env python3
# -*- coding: utf-8 -*-

# este guion de Python grafica una silla de montar junto con sus curvas de nivel
# el resultado se guarda en formato png

import numpy as np
import matplotlib.pyplot as plt

# figura y ejes
fig = plt.figure()
ax = plt.axes(projection='3d')

# variables
x_min, x_max = -5, 5
y_min, y_max = -5, 5
paso = 0.5
xs, ys = np.mgrid[x_min:x_max+.1:paso, y_min:y_max:paso]
zs = xs**2 - ys**2

# superficie
ax.plot_surface(xs, ys, zs, alpha=0.5)
# curvas de nivel
cset = ax.contour(xs, ys, zs, zdir='z', offset=-30)

# título
ax.set_title('Gráfica en matplotlib')

# anotación descriptiva
plt.annotate(r'$z = x^2 - y^2$', xy=(0,0), xytext=(0.019,0.04))

# configuración de los ejes
ax.set_xlabel('x')
ax.set_xlim(x_min +x_min/5, x_max + x_max/5)
ax.set_ylabel('y')
ax.set_ylim(y_min +y_min/5, y_max + y_max/5)
ax.set_zlabel('z')
ax.set_zlim(-30, 30)

# se guarda la imagen
plt.savefig('python_plot.png')
