#!/usr/bin/octave -qf

disp("P(x) = 3x^3 -4x^2 + 2x -5");
P=[3,-4,2,-5]

disp("Raices de P");
roots(P)

disp("Q(x) = x^4 + 2x^2 -6x -8");
Q=[1,0,2,-6,-8];
disp("Raices de Q");
roots(Q)

disp("Z(x) = x^4 + 8x^3 -3x^2 -62x + 56");
Z=[1,8,-3,-62,56];
disp("Raices de Z");
roots(Z)
disp("Factorización de Z(x)");
disp("Z(x) = (x -1)(x -2)(x + 4)(x + 7)");
