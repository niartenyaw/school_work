function [ output_args ] = untitled( input_args )

x = [0, .005, .01, .02, .04, .06, .08];
y = [0, .74, 1.51, 3.03, 6.37, 10.21, 14.43];
P = polyfit(x, y, 3)

syms v;
ezplot(P(1)*v^3 + P(2)*v^2 + P(3)*v, [0, .1])
axis([0 .1 0 20]);
title('u = 142.7y + 377.1y^2 + 1154.9y^3');
xlabel('y(ft)');
ylabel('u(ft/s)');


end

