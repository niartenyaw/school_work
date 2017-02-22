function x = newton(A,m)

%This function solves A*x=b where:
%b = sin(mx)*(-m^2) for 0 to pi

n=length(A);
h=pi/(n-1);
i=[1:n-2]'*h;

b=sin(m*i)*(-m^2);
b=[0;b;0];

x=A\b;

end