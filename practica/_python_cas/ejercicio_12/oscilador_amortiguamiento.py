
import numpy as np
import matplotlib.pyplot as plt
from scipy.integrate import solve_ivp
from oscilador_armonico import amplitud

# Variable temporal
t_min = 0
t_max = 100
num_muestreo = 400
ts = np.linspace(t_min, t_max, num_muestreo)

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