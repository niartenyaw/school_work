function [f,dfdx]=loan(r,a,p,n)

% LOAN evaluates normalized balance
% for interested rate r, amount a,
% payment p, after n years

%f = (1+r).^n-p/a*((1+r).^n-1)./r;

f = (1+r).^n;
for k=0:n-1
  f = f-p/a*(1+r).^k;
end

dfdx= n*(r+1)^(n-1)-p/a*((n*r*(r+1)^(n-1)-(r+1)^n+1)/r^2);
end