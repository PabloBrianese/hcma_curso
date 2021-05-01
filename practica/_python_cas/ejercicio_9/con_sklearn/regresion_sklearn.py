#!/usr/bin/env python
# -*- coding: utf-8 -*-

import sys
import numpy as np
import matplotlib.pyplot as plt
from sklearn.linear_model import LinearRegression

# Datos
archivo = sys.argv[1]
datos = np.genfromtxt(archivo, delimiter=',')

xs, ys = datos[:, 0].reshape(-1,1), datos[:, 1].reshape(-1,1)

reg = LinearRegression()

reg.fit(xs, ys)

ys_pred = reg.predict(xs)

# Guardar los valores de la recta calculada
resultados = np.concatenate((xs, ys_pred), axis=1)
np.savetxt('regresion_sklearn.csv',
           resultados,
           delimiter=',')

# Gráfica de los resultados
fig, ax = plt.subplots()

ax.scatter(xs, ys,
           label='Datos', marker='+', color='black')
ax.plot(xs, ys_pred,
        label='Regresión lineal', color='red')

ax.set_title('Regresión lineal con Scikit-learn')
ax.set_xlabel(r'$x$')
ax.set_ylabel(r'$y$')
plt.legend()

plt.savefig('regresion_sklearn.png')
