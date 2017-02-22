function f = evalfunc(X,Y,i)
dx=X(2)-X(1);
if i==1
    dy=Y(i+1)-Y(i);
elseif i==length(X)
    dy=Y(i)-Y(i-1);
else
    dy=(Y(i+1)-Y(i-1))/2;
end
dydx=dy/dx;

norm=sqrt(dx^2+dy^2);
D=sqrt(1+dydx^2+0.1*(exp(Y(i)-(X(i)-1)^2)*(3*pi/2*cos(3*pi*Y(i)/2)*dydx+sin(3*pi*Y(i)/2)*(dydx-2*X(i)+2)))^2);
m=0.1*exp(Y(i)-(X(i)-1)^2)*(sin(3*pi*Y(i)/2)*(2+dydx)+3*pi/2*cos(3*pi*Y(i)/2)*dydx)*dx/norm;
f=exp(-m)*D;
end