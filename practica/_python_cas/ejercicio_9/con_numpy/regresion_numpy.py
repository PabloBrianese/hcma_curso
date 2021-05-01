#!/usr/bin/env python
# -*- coding: utf-8 -*-

import sys
import numpy as np
import time
import matplotlib.pyplot as plt

# Datos
archivo = sys.argv[1]
datos = np.genfromtxt(archivo, delimiter=',')

xs, ys = datos[:, 0], datos[:, 1]

# Medimos tiempo de inicio
start = time.time()


# Normalización de los datos
def normalizacion01(v):
    m, M = np.amin(v), np.amax(v)
    return (v - m) / (M - m)


xs_normal = normalizacion01(xs)
ys_normal = normalizacion01(ys)

# Representación matricial de los datos
X = np.column_stack((np.ones_like(xs_normal), xs_normal))
Y = ys_normal[:, np.newaxis]

# Inicialización de los parámetros a aprender
# Para mejorar el rendimiento del algoritmo se eligen dos puntos al azar
# dentro del conjunto de datos y se inicializan los parámetros tomando los
# de la recta que pasa por ellos.
W = np.array([0, 0])[:, np.newaxis]
# Índices aleatorios (distintos)
i0 = np.random.randint(0, len(xs_normal))
i1 = np.random.randint(0, len(xs_normal))
while i1 == i0:
    i1 = np.random.randint(0, len(xs_normal))
# Selección de puntos aleatorios
P0 = (xs_normal[i0], ys_normal[i0])
P1 = (xs_normal[i1], ys_normal[i1])
# Pendiente inicial
W[1] = (ys_normal[i0] - ys_normal[i1]) / (xs_normal[i0] - xs_normal[i1])
# Intersección inicial
W[0] = ys_normal[i0] - xs_normal[i0] * W[1]


# Error
def calcular_error(W, X, Y):
    Y_estimada = X @ W  # y^ = w0 + w1 x
    error = Y - Y_estimada
    return error


# Gradiente del Error Cuadrático Medio
def calcular_gradiente_ECM(W, X, error):
    gradiente = (-2/len(X)) * np.transpose(X) @ error
    return gradiente


# Tasa de aprendizaje y tolerancia al error
alpha = 1/2
tolerance = 1e-4

# Descenso por gradiente, bucle while
iteracion = 1
delta = 10 * tolerance
while delta >= tolerance:
    # Cálculo del descenso
    error = calcular_error(W, X, Y)
    gradiente = calcular_gradiente_ECM(W, X, error)
    siguiente_W = W - alpha * gradiente
    # Error Cuadrático Medio
    siguiente_delta = np.sum(abs(error)**2) / len(error)

    # Actualización
    iteracion += 1
    if siguiente_delta >= delta:
        # Reducir la tasa de aprendizaje
        alpha = alpha / 2
    delta = siguiente_delta
    W = siguiente_W

    # Informes
    if iteracion % 100 == 0:
        print(f"Iteración: {iteracion}. Error Cuadrático Medio: {delta}.")

    # En caso de estancarse
    if iteracion > 1e3:
        print('Interrumpiendo el bucle.')
        break

# Denormalización de los parámetros aprendidos
m_y, M_y = np.amin(ys), np.amax(ys)
w = np.array([0, 0])
w[0] = (M_y - m_y) * W[0] + m_y
w[1] = (M_y - m_y) * W[1]

# Calculamos la recta
ys_pred = w[0] + w[1] * xs_normal

# Medimos tiempo de finalización
end = time.time()
# Reportamos el tiempo
print(f"Tiempo de cómputo: {end - start}")

# Guardar los valores de la recta calculada
resultados = np.column_stack((xs, ys_pred))
np.savetxt('regresion_numpy.csv',
           resultados,
           delimiter=','
           )

# Informar los parametros de la regresion
print('Término constante:', w[0])
print('Pendiente:', w[1])
print('Error Cuadrático Medio:', delta) 

# Gráfica de los resultados
fig, ax = plt.subplots()

ax.scatter(xs, ys,
           label='Datos', marker='+', color='black')
ax.plot(xs, ys_pred,
        label='Regresión lineal', color='red')

ax.set_title('Regresión lineal con numpy')
ax.set_xlabel(r'$x$')
ax.set_ylabel(r'$y$')
plt.legend()

plt.savefig('regresion_numpy.png')
