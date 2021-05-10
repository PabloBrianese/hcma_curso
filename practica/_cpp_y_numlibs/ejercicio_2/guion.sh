#!/bin/bash

g++ celcius2farenheit.cpp -o celcius2farenheit.out

echo "La temperatura de fusión del agua es"
./celcius2farenheit.out 0
echo "La temperatura de ebullición del agua es"
./celcius2farenheit.out 100
