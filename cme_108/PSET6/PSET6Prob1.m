clear;
N=32;
e=0.01;

%Even Spacing
x=0:1/N:1;
h=1/N;

o=ones(N+1,1);
oo=ones(N,1);

A=-2*e/h^2*diag(o,0);
A=A+(2*e-h)/(2*h^2)*diag(oo,-1);
A=A+(2*e+h)/(2*h^2)*diag(oo,1);
A(1,1)=1;
A(1,2)=0;
A(N+1,N+1)=1;
A(N+1,N)=0;


y=zeros(N,1);
y=[y;1];
u=A\y;
plot(x,u)
axis([0 1 0 1.4])
hold all
grid on

%Uneven spacing
x=[];
for i=0:N
    x=[x e*(i/N)+(1-e)*(i/N)^4];
end

A=zeros(N+1,N+1);
for i=2:N
    hi=x(i)-x(i-1);
    hi1=x(i+1)-x(i);
    
    A(i,i-1)=(2*e-hi1)/(hi*(hi+hi1));
    A(i,i)=(hi1-hi-2*e)/(hi*hi1);
    A(i,i+1)=(2*e+hi)/(hi1*(hi+hi1));
end
A(1,1)=1;
A(N+1,N+1)=1;
f=zeros(N,1);
f=[f;1];
u=A\f;
plot(x,u)


%Actual Solution
x=0:.001:1;
y=1-exp(-100.*x);
plot(x,y)

legend('Equal','Nonequal','Exact')
