from realUnitSystemConstants import *

import numpy as np
from scipy.integrate import solve_ivp

initialPosition = (0.0, 0.0, 100.0)  # angstroms
initialVelocity = (0.0, 0.0, 1.0)  # angstroms/femtoseconds
electricField = np.array((electronMass / electronCharge, -1.0, 0.0))  # volts/angstroms
magneticField = np.array((1, 0, 0))


def derivative(t, y):
  x0, x1, x2, v0, v1, v2 = y
  v = np.array((v0, v1, v2))
  proportionality_constant = avogadroNumber * protonCharge * 1e-7
  G = proportionality_constant * (electronCharge / electronMass) * (np.array(electricField) + np.cross(v, magneticField))
  y_prime = np.array((v0, v1, v2, *G))
  return y_prime

t_span = (0, 10) # femtosegundos
ts = np.linspace(*t_span, 1000)
initialConditions = np.array(initialPosition + initialVelocity)
sol = solve_ivp(derivative, t_span, initialConditions, t_eval=ts)

xs = sol.y[0, :]
ys = sol.y[1, :]
zs = sol.y[2, :]

np.savetxt(
  'dat/electronEnCampoElectromagnetico.dat',
  np.column_stack((ts, xs, ys, zs)),
  delimiter=" ",
  header="t [femtosegundos]  x [Angstroms]  y [Angstroms]  z [Angstroms]",
)
