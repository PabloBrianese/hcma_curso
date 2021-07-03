import numpy as np
from scipy.integrate import solve_ivp

initialPosition = (0.0, 0.0, 100.0)  # angstroms
initialVelocity = (10.0, 0.0, 0.0)  # angstroms/femtoseconds
electricField = (0.0, 0.1, 0.0)  # volts/angstroms
electronCharge = -1.0  # elementary charges
electronMass = 0.00054854  # grams/mol

avogadro_number = 6.02214076e23
proton_charge_in_coulombs = 1.602176634e-19
proportionality_constant = avogadro_number * proton_charge_in_coulombs * 1e-7


def derivative(t, y):
  x0, x1, x2, *v = y
  F = proportionality_constant * (electronCharge / electronMass) * np.array(electricField)
  y_prime = np.array((*v, *F))
  return y_prime

t_span = (0, 10) # femtosegundos
ts = np.linspace(*t_span, 1000)
initialConditions = np.array(initialPosition + initialVelocity)
sol = solve_ivp(derivative, t_span, initialConditions, t_eval=ts)

xs = sol.y[0, :]
ys = sol.y[1, :]
zs = sol.y[2, :]

np.savetxt(
  'dat/electronEnCampoElectrico.dat',
  np.column_stack((ts, xs, ys, zs)),
  delimiter=" ",
  header="t [femtosegundos]  x [Angstroms]  y [Angstroms]  z [Angstroms]",
)
