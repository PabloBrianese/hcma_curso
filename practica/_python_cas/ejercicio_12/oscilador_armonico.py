# Este módulo contiene una función
# que resuelve el problema de valores iniciales
# del oscilador armónico.

import numpy as np
import matplotlib.pyplot as plt
from scipy.integrate import solve_ivp


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

