clear;

low=1;
high=3;
tol=10^(-6);

[x,f]=golden(@ptoq,low,high,tol);
x
f=-f;
f