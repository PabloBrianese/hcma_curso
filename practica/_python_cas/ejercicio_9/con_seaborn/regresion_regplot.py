#! /usr/bin/env python3
# -*- coding: utf-8 -*-

import sys
import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns

datos = sys.argv[1]
df = pd.read_csv(datos)

df.columns = ['x', 'y']

ax = sns.regplot(x = 'x', y = 'y', data = df, 
                 label = 'datos', marker = '+', color = 'black',
                 line_kws={'label':'regresión lineal', 'color':'red'})

ax.set_title('Regresión lineal con Seaborn')
plt.legend()

# no se pueden obtener los parámetros de la regresión con seaborn

plt.savefig('regresion_regplot.png')