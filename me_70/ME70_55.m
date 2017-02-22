function [ output_args ] = untitled( input_args )
%ME 70 Week 5 PSET
M0=400;
me=5;
Ve=3500;
g=9.8;
syms t;

int(-Ve*log((M0-me*t)/M0)-g*t,t,0,60)

end

