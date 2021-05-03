#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import numpy as np
import matplotlib.pyplot as plt
from scipy.integrate import solve_ivp


def derivative(t, y): return t * np.exp(- y)


t_span = (0, 1000)
y0 = (1,)
sol = solve_ivp(derivative, t_span, y0)

t = sol.t
y = sol.y.T

plt.plot(t, y)

plt.xlabel('x')
plt.ylabel('y')

plt.savefig('pvi.png')
