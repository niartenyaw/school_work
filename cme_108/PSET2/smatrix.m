function [T,time] = smatrix(N)

h=pi/N;
x=[1:N-1]' *h;

e=ones(N+1,1);
a = [e -2*e e]/h^2;

As = spdiags(a,[-1 0 1],N+1,N+1);
As(1,1)=1;
As(1,2)=0;
As(N+1,N+1)=1;
As(N+1,N)=0;

f=-sin(x);
f=[0; f; 1];

tic
T=As\f;
time=toc;

end

