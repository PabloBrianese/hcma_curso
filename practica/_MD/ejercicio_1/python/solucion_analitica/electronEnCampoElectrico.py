import numpy as np

initialPosition = (0.0, 0.0, 1e-8) # metros  # (0.0, 0.0, 100.0)  # angstroms
initialVelocity = (1e6, 0.0, 0.0) # metros / segundos  # (10.0, 0.0, 0.0)  # angstroms / femtosegundos
electricField = (0.0, 1e9, 0.0) # voltios / metros # (0.0, 0.1, 0.0)  # voltios / angstroms
electronCharge = -1.602176e-19 # Coulombios  # -1.0  # carga elemental
electronMass = 9.109384e-31 # kilogramos  # 0.00054854  # gramos / mol


t_span = (0, 1e-14) # segundos  # (0, 10) # femtosegundos
ts = np.linspace(*t_span, 1000)

t = ts.reshape((1, -1))  # vector fila
r0 = np.array(initialPosition).reshape((-1, 1))  # vector columna
v0 = np.array(initialVelocity).reshape((-1, 1))
E = np.array(electricField).reshape((-1, 1))
G = (electronCharge / electronMass) * E

r = G * t**2 / 2 + v0 * t + r0 * np.ones_like(t)

xs = r[0, :]
ys = r[1, :]
zs = r[2, :]

np.savetxt(
  'dat/solucionAnalitica.dat',
  np.column_stack((ts, xs, ys, zs)),
  delimiter=" ",
  header="t [s]  x [m]  y [m]  z [m]",
)
