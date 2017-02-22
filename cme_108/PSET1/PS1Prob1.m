clear;
a = 100000;
p = 10000;
n = 20;
tol = 10^(-6);
lowBound = 0.0;
upBound = 0.1;


[x,err] = bisection(@(r) loan(r,a,p,n),lowBound,upBound,tol);
semilogy(err)
x
hold all

x0 = 0.01;
[x,err] = newton(@(r) loan(r,a,p,n),x0,tol);
semilogy(err)
x

x0 = 0.08;
x1 = 0.07;
[x,err] = secant(@(r) loan(r,a,p,n),x0,x1,tol);
semilogy(err)
x
title('Error in Interest Rate')
xlabel('Iterations')
ylabel('Error')
legend('Bisection','Newton','Secant')

