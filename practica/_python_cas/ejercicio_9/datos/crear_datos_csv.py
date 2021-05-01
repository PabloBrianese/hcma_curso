#!/usr/bin/env python
# Crear archivos csv con datos

import numpy as np

xs = np.linspace(-10, 10, 500)
ruido = np.random.normal(0, 1, len(xs))
ys = 3 * xs + 5 + ruido

datos = np.column_stack((xs, ys))

np.savetxt('datos1.csv', datos, delimiter=',')

xs = np.linspace(1, 10, 100)
ruido = np.random.normal(0, 1, len(xs))
ys = np.sin(xs) + 0.1*xs**2 + 0.5*ruido

datos = np.column_stack((xs, ys))

np.savetxt('datos2.csv', datos, delimiter=',')
