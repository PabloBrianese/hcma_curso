import numpy as np
from scipy.integrate import solve_ivp
import matplotlib.pyplot as plt

initialPosition = (0.0, 0.0, 100.0)  # unidades = angstroms
initialVelocity = (10.0, 0.0, 0.0)  # unidades = angstroms sobre femtosegundos
electricField = (0.0, 0.1, 0.0)  # unidades = voltios sobre angstroms
electronCharge = -1.0  # unidades = carga elemental
electronMass = 0.00054854  # unidades = gramos sobre mol


def derivative(t, y):
  x0, x1, x2, v0, v1, v2 = y
  F = (electronCharge / electronMass) * np.array(electricField)  # unidades = mol * electronvoltios / (angstrom * gramos)
  y_prime = np.array((v0, v1, v2, *F))
  return y_prime

t_span = (0, 10)
t_eval = np.linspace(*t_span, 1000)
initialConditions = np.array(initialPosition + initialVelocity)
sol = solve_ivp(derivative, t_span, initialConditions, t_eval=t_eval)

xs = sol.y[0, :].T
ys = sol.y[1, :].T
zs = sol.y[2, :].T

fig = plt.figure()
ax = plt.axes(projection = '3d')
ax.plot(xs=xs, ys=ys, zs=zs)
ax.set_xlabel('x')
ax.set_ylabel('y')
ax.set_zlabel('z')

plt.savefig('pvi.png')
