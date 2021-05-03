# -*- coding: utf-8 -*-
"""
Created on Sun May 10 21:20:57 2020

@author: Pablo
"""

import numpy as np
import matplotlib.pyplot as plt
from scipy.integrate import solve_ivp

# Variable temporal
t_min = 0
t_max = 100
num_muestreo = 400
ts = np.linspace(t_min, t_max, num_muestreo)


def amplitud(ts, omega_0=1, gamma=0, B=0, omega=0):
    """Resolver la ecuación del oscilador armónico.

    Parametros
    ----------
    ts : numpy.ndarray
        Variable temporal
    omega_0 : float, opcional
        Frecuencia fundamental del sistema. Por defecto es 1.
    gamma : float, opcional
        Constante de amortiguamiento. Por defecto es 0.
    B : float, opcional
        Amplitud de la fuerza externa ejercida sobre el sistema.
        Por defecto es 0.
    omega : float, opcional
        Frecuencia de la fuerza externa ejercida sobre el sistema.
        Por defecto es 0.

    Returns
    -------
    ndarray
        Valores de la amplitud en los puntos especificados.

    """

    # Función derivada, lado derecho del sistema lineal
    def f(t, y):
        dy0_dt = y[1]  # A'
        dy1_dt = B*np.sin(omega * t) - omega_0**2 * y[0] - gamma*y[1]  # A''
        return [dy0_dt, dy1_dt]

    # Condiciones iniciales del sistema
    y0 = [1, 0]  # A0, A'0

    # Intervalo de definicion de la solución
    t_span = (np.amin(ts), np.amax(ts))

    # Solución del sistema
    solucion = solve_ivp(f, t_span, y0, t_eval=ts, vectorized=True)

    # Extracción de los valores de la variable de interés
    As = solucion.y[0, :]
    return As


# Figura: Oscilador armónico con y sin amortiguamiento
fig, axs = plt.subplots(nrows=2, sharex=True, sharey=True)

axs[0].plot(ts, amplitud(ts, gamma=0))
axs[0].set_title(r'$\gamma=0$')

axs[1].plot(ts, amplitud(ts, gamma=0.1))
axs[1].set_title(r'$\gamma = 0.1$')

axs[1].set_xlabel('Tiempo (segundos)')
axs[1].set_ylabel('Amplitud (metros)')

st = fig.suptitle(
    'Oscilador Armónico con y sin amortiguamiento\n'
    +
    r'$A^{\prime\prime} + \gamma \/ A^{\prime} + \omega_0^2 \/ A = 0$'
    )

# Ajustamos las posiciones de las subgráficas y del suptitulo
st.set_y(2.15)
fig.subplots_adjust(top=1.95)

plt.savefig('oscilador_amortiguamiento.png',
            bbox_inches='tight')

plt.clf()

# Figura: Oscilador armónico en presencia de una fuerza externa
omega_0 = 1  # Para facilitar la comparación en los argumentos
fig, axs = plt.subplots(nrows=3, ncols=2, sharex=True)

axs[0, 0].plot(ts, amplitud(ts, gamma=0, B=1, omega=10*omega_0))
axs[0, 0].set_title(r'$\gamma=0$, $B=1$, $\omega=10 \/ \omega_0$')

axs[0, 1].plot(ts, amplitud(ts, gamma=0.1, B=1, omega=10*omega_0))
axs[0, 1].set_title(r'$\gamma=0.1$, $B=1$, $\omega=10 \/ \omega_0$')

axs[1, 0].plot(ts, amplitud(ts, gamma=0, B=1, omega=omega_0))
axs[1, 0].set_title(r'$\gamma=0$, $B=1$, $\omega=\omega_0$')

axs[1, 1].plot(ts, amplitud(ts, gamma=0.1, B=1, omega=omega_0))
axs[1, 1].set_title(r'$\gamma=0.1$, $B=1$, $\omega=\omega_0$')

axs[2, 0].plot(ts, amplitud(ts, gamma=0, B=1, omega=0.1*omega_0))
axs[2, 0].set_title(r'$\gamma=0$, $B=1$, $\omega=0.1 \/ \omega_0$')

axs[2, 1].plot(ts, amplitud(ts, gamma=0.1, B=1, omega=0.1*omega_0))
axs[2, 1].set_title(r'$\gamma=0.1$, $B=1$, $\omega=0.1 \/ \omega_0$')

st = fig.suptitle(
    'Oscilador Armónico variando amortiguamiento y fuerza externa'
    + '\n'
    + r'$A^{\prime\prime} + \gamma \/ A^{\prime} + \omega_0^2 \/ A'
    + r'= B \/ \sin(\omega \/ t)$'
    )

# Ajustamos las posiciones de las subgráficas y del suptitulo
st.set_y(2.15)
fig.subplots_adjust(top=1.95)

plt.savefig('oscilador_amortiguamiento_fuerza.png',
            bbox_inches='tight')

plt.clf()
