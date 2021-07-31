import numpy as np
data = np.genfromtxt("OutFlujoExtCilindro/postProcessing/perfil_axial_magU/0/line_mag(U).xy")
xs, speeds = data[:, 0], data[:, 1]

from matplotlib import pyplot as plt
plt.plot(xs, speeds)
plt.title("Simulación con OpenFOAM")
plt.xlabel("x")
plt.ylabel("rapidez")
plt.annotate("y = 2.5", xy=(4, 1.05))
plt.savefig("dat/horizontalLineSpeed.png")