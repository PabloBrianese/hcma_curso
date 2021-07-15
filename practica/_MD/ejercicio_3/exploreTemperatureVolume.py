#!/usr/bin/python3

import os
from itertools import product

temperatures = range(100, 1000 + 1, 100)
volumes = range(10**6, 9 * 10**6 + 1, 10**6)
lengths = (volume**(1/3) for volume in volumes)
for temperature, length in product(temperatures, lengths):
  os.system(
    'lmp_ubuntu' 
    + f' -var Temperatura {temperature}'
    + f' -var side {length}'
    + ' -in ArgonLJ.lammps'
  )

