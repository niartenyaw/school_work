function [ output_args ] = untitled( input_args )
%CME 102 PSET 4 3h

syms x;
ezplot(x^4/4-log(x)/2-1/4,[.005,1])
xlabel('X');
ylabel('T');


end

