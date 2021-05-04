# Este guión crea una gráfica que compara el comportamiento
# de un oscilador armónico en presecia y ausencia
# de amortiguamiento y fuerza externa.

import numpy as np
import matplotlib.pyplot as plt
from scipy.integrate import solve_ivp
from oscilador_armonico import amplitud

# Variable temporal
t_min = 0
t_max = 100
num_muestreo = 400
ts = np.linspace(t_min, t_max, num_muestreo)

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
