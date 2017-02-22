clear;

N=16;
a=0;
b=1;
xx=linspace(0,1,100);
yy=sin(4*pi.*xx.^2);

% Even Spacing
x=linspace(a,b,N+1);
[even,y]=Simpson(x,@sinfunc);
figure;
plot(x,y,'o')
hold all
plot (xx,yy)
grid on
title('Evenly Spaced X')
xlabel('x')
ylabel('y')
even

%Uneven Spacing
x=sqrt(linspace(a,b,N+1));
[uneven,y]=Simpson(x,@sinfunc);
figure;
plot(x,y,'o')
hold all
plot (xx,yy)
grid on
hold all
title('Unevenly Spaced X')
xlabel('x')
ylabel('y')
uneven

% From Wolfram Alpha
actual=0.137168