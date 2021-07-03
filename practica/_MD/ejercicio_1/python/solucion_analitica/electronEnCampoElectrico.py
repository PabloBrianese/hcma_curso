import numpy as np

initialPosition = (0.0, 0.0, 100.0)  # angstroms
initialVelocity = (10.0, 0.0, 0.0)  # angstroms/femtoseconds
electricField = (0.0, 0.1, 0.0)  # volts/angstroms
electronCharge = -1.0  # elementary charges
electronMass = 0.00054854  # grams/mol

avogadro_number = 6.02214076e23
proton_charge_in_coulombs = 1.602176634e-19
proportionality_constant = avogadro_number * proton_charge_in_coulombs * 1e-7


t_span = (0, 10) # femtosegundos
ts = np.linspace(*t_span, 1000)

ts_row = ts.reshape((1, -1))  # vector fila
r0 = np.array(initialPosition).reshape((-1, 1))  # vector columna
v0 = np.array(initialVelocity).reshape((-1, 1))
E = np.array(electricField).reshape((-1, 1))
G = proportionality_constant * (electronCharge / electronMass) * E

r = G * ts_row**2 / 2 + v0 * ts_row + r0 * np.ones_like(ts_row)

xs = r[0, :]
ys = r[1, :]
zs = r[2, :]

np.savetxt(
  'dat/electronEnCampoElectrico.dat',
  np.column_stack((ts, xs, ys, zs)),
  delimiter=" ",
  header="t [s]  x [m]  y [m]  z [m]",
)
