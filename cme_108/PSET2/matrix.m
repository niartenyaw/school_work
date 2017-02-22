function [T,Terr,time] = gauss(N)
h=pi/N;
x=[1:N-1]' *h;

e=ones(N+1,1);
ee=ones(N,1);

A=-2/h^2*diag(e,0);
A=A+1/h^2*diag(ee,1);
A=A+1/h^2*diag(ee,-1);
A(1,1)=1;
A(1,2)=0;
A(N+1,N+1)=1;
A(N+1,N)=0;

f=-sin(x);
f=[0; f; 1];

tic
T=gauss(A,f);
time=toc;

Exact=sin(x)+x./pi;
Exact=[0; Exact; 1];

diff=0;
for i=2:N
    diff=diff+(T(i)-Exact(i))^2;
end

Terr=sqrt(diff/N);

end

