% Problem Set 8- 8.121

syms Q;
H=(1.667*10^(-5)*Q)^2*280.5/(2*9.8*pi^2*(0.01/2)^4);
ezplot(H,1,10)
title('Required reservoir height for given flow rate');
xlabel('Flow Rate (L/min)');
ylabel('Height of reservoir (meters)');