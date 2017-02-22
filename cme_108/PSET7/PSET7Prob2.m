clear;

b=[pi 0 pi/2]';
A=[[1 1 1];[-1 0 1];[1 0 1]];
w=(A\b);

%g(x)=sin(x)
g(1)=sin(4);
g(2)=sin(6.5);
g(3)=sin(9);

I=g*w