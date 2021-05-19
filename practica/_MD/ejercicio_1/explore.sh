#!/bin/bash

# greps for the keyword passed in the example lammps scripts

find /opt/lammps/examples/ -name in.* -exec grep $1 {} +
