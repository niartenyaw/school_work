function q = ptoq(p)
N=512;

h=pi/N;
x=[1:N-1]' *h;

o=ones(N+1,1);
a=[o -2*o o]/h^2;

As=spdiags(a,[-1 0 1],N+1,N+1);
As(1,1)=1;
As(1,2)=0;
As(N+1,N+1)=1;
As(N+1,N)=0;

f=-p.*x.^2.*sin(x);
f=[0; f; -exp(p)];

T=As\f;

q=-T(2)/h;

end

