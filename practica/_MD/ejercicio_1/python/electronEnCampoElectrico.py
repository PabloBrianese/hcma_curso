import numpy as np
from scipy.integrate import solve_ivp

initialPosition = (0.0, 0.0, 1e-8) # metros  # (0.0, 0.0, 100.0)  # angstroms
initialVelocity = (1e6, 0.0, 0.0) # metros / segundos  # (10.0, 0.0, 0.0)  # angstroms / femtosegundos
electricField = (0.0, 1e9, 0.0) # voltios / metros # (0.0, 0.1, 0.0)  # voltios / angstroms
electronCharge = -1.602176e-19 # Coulombios  # -1.0  # carga elemental
electronMass = 9.109384e-31 # kilogramos  # 0.00054854  # gramos / mol


def derivative(t, y):
  x0, x1, x2, v0, v1, v2 = y
  F = (electronCharge / electronMass) * np.array(electricField)
  y_prime = np.array((v0, v1, v2, *F))
  return y_prime

t_span = (0, 1e-14) # segundos  # (0, 10) # femtosegundos
ts = np.linspace(*t_span, 1000)
initialConditions = np.array(initialPosition + initialVelocity)
sol = solve_ivp(derivative, t_span, initialConditions, t_eval=ts)

xs = sol.y[0, :]
ys = sol.y[1, :]
zs = sol.y[2, :]

np.savetxt(
  'electronEnCampoElectrico.dat',
  np.column_stack((ts, xs, ys, zs)),
  delimiter=" ",
  header="t [s]  x [m]  y [m]  z [m]",
)
