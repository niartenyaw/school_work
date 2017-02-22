% HW 7 Number 6:

syms t;
f=t-sin(t)+heaviside(t-1)*(sin(t)-t+1-cos(t))...
    +heaviside(t-10)*(cos(t)-1);
ezplot(f,0,20)
title('Heavyside Graph f=t-sin(t)+u(t-1)*(sin(t)-t+1-cos(t))+u(t-10)*(cos(t)-1)');
xlabel('t');
ylabel('y(t)');