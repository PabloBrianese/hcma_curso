#!/bin/bash

# Informa si el año introducido es bisiesto
year=$1

function bisiesto () { echo "El año $year es bisiesto."; }
function no_bisiesto () { echo "El año $year no es bisiesto."; }

yearMOD4=$(($year % 4))
yearMOD100=$(($year % 100))
yearMOD400=$(($year % 400))
if [ $yearMOD4 -eq 0 ]
then
  if [ $yearMOD100 -eq 0 ]
  then
    if [ $yearMOD400 -eq 0 ]
    then
      bisiesto
    else
      no_bisiesto
    fi
  else
    bisiesto
  fi
else
  no_bisiesto
fi