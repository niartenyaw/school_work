function [f,dfdx]=diverge(x)

  f = x.*exp(-x.^2);
  dfdx = (1-2*x.^2).*exp(-x.^2);