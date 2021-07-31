xMin, xMax = -5, 5
yMin, yMax = 0, 4
cylinderRadius = 0.5
inletVelocity = 1


def velocityPotential(x, y):
  return inletVelocity * (1 + cylinderRadius**2 / (x**2 + y**2)) * x


def streamFunction(x, y):
  return inletVelocity * (1 - cylinderRadius**2 / (x**2 + y**2)) * y


def velocity(x, y):
  quotient = cylinderRadius**2 / (x**2 + y**2)**2
  return (
    inletVelocity * (1 - quotient * (x**2 - y**2)),
    inletVelocity * quotient * (- 2 * x * y),
  )


def speed(x, y):
  xComponent, yComponent = velocity(x, y)
  return (xComponent**2 + yComponent**2)**(1 / 2)


import numpy as np
xs = np.linspace(xMin, xMax, 100, endpoint=True)
speeds = np.vectorize(lambda x: speed(x, 2.5))(xs)

from matplotlib import pyplot as plt
plt.plot(xs, speeds)
plt.title("Solución analítica")
plt.xlabel("x")
plt.ylabel("rapidez")
plt.annotate("y = 2.5", xy=(4, 1.05))
plt.savefig("dat/horizontalLineSpeed.png")
