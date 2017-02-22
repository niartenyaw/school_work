clear;
syms a b g;

A=[[1 0 0];[0 cos(a) -sin(a)];[0 sin(a) cos(a)]];
B=[[cos(b) 0 sin(b)];[0 1 0];[-sin(b) 0 cos(b)]];
C=[[cos(g) -sin(g) 0];[sin(g) cos(g) 0];[0 0 1]];
A*B*C