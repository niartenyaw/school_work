function [ output_args ] = untitled( input_args )

syms x;
y = 10^(-3)*1.875*pi*x.^3;
ezplot(y,[0,15]);
title('Power = 1.875\piV^3');
xlabel('V (m/s)');
ylabel('Power (kW)');


end

