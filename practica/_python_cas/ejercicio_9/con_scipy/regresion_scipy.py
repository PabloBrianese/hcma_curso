#!/usr/bin/env python
# -*- coding: utf-8 -*-

import sys
import numpy as np
import matplotlib.pyplot as plt
from scipy.stats import linregress

# Datos
archivo = sys.argv[1]
datos = np.genfromtxt(archivo, delimiter=',')

xs, ys = datos[:, 0], datos[:, 1]

gradient, intercept, _, _, _ = linregress(xs, ys)

ys_reg = gradient * xs + intercept


# Guardar los valores de la recta calculada
resultados = np.column_stack((xs, ys_reg))
np.savetxt('regresion_sklearn.csv',
           resultados,
           delimiter=',')

# Gráfica de los resultados
fig, ax = plt.subplots()

ax.scatter(xs, ys,
           label='Datos', marker='+', color='black')
ax.plot(xs, ys_reg,
        label='Regresión lineal', color='red')

ax.set_title('Regresión lineal con SciPy')
ax.set_xlabel(r'$x$')
ax.set_ylabel(r'$y$')
plt.legend()

plt.savefig('regresion_scipy.png')
