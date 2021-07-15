#!/usr/bin/python3

import os

volumes = range(10**6, 9 * 10**6 + 1, 10**6)
lengths = (volume**(1/3) for volume in volumes)
for length in lengths:
  os.system(f'lmp_ubuntu -var side {length} -in ArgonLJ.lammps')

