function [ output_args ] = untitled( input_args )
%E30 Problem Set 4-3D
%% T2=300 T3=1200
syms x;
ezplot((3+4*log(x))/(10.5+4*log(x)),[3,10])
xlabel('Rv');
ylabel('n');

%% T2=300 T3=600
syms x;
ezplot((1+2*log(x))/(10.5+2*log(x)),[3,10])
xlabel('Rv');
ylabel('n');

end

