#!/bin/bash

g++ probagsl.cpp -o probagsl.out -lgsl -lgslcblas -lm

./probagsl.out 10
