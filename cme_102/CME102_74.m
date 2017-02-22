% HW 7 Number 4:

syms t;
f=2*(t-1)*(heaviside(t-1)-heaviside(t-2)) ...
    +(4-t)*(heaviside(t-2)-heaviside(t-4));
ezplot(f,0,6)
title('Heavyside Graph f=2(t-1)(u(t-1)-u(t-2))+(4-t)(u(t-2)-u(t-4))');
xlabel('t');
ylabel('f(t)');