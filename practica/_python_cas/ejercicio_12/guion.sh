#!/bin/bash

pipenv install &> /dev/null
pipenv run python3 oscilador_amortiguamiento.py
pipenv run python3 oscilador_amortiguamiento_fuerza.py
