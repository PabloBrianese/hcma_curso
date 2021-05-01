#!/usr/bin/env python3

import sys
import numpy as np
import matplotlib.pyplot as plt

# Datos 1
archivo_sklearn = sys.argv[1]
datos_sklearn = np.genfromtxt(archivo_sklearn,
                              delimiter=',')

xs_sklearn = datos_sklearn[:, 0]
ys_sklearn = datos_sklearn[:, 1]

# Datos 2
archivo_numpy = sys.argv[2]
datos_numpy = np.genfromtxt(archivo_numpy,
                            delimiter=',')

xs_numpy = datos_numpy[:, 0]
ys_numpy = datos_numpy[:, 1]

# Grafica
fig, ax = plt.subplots()

ax.plot(xs_sklearn, ys_sklearn,
        label='sklearn')
ax.plot(xs_numpy, ys_numpy,
        label='numpy')

ax.set_xlabel('x')
ax.set_ylabel('y')

plt.legend()

plt.savefig('sklearn_vs_numpy.png')