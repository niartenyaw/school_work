function [f,dfdx]=poly5(x)

  f = x.^5-x+1;
  dfdx = 5*x.^4-1;