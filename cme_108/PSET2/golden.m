function [x,f] = golden(func,a,b,tol)

% minimize function in 1D using golden section search

tau = (-1+sqrt(5))/2;

x1 = a+(1-tau)*(b-a);
x2 = a+   tau *(b-a);

fa = func( a);
f1 = func(x1);
f2 = func(x2);
fb = func( b);

if f1>fa||f1>fb
  disp('f(x1) larger than f(a) and/or f(b)')
  x = NaN; f = NaN;
  return
end

k = 0;
fprintf('%6i %20.10f %20.10f\n',k,x1,f1)

while b-a>tol

  k = k+1;
  fprintf('%6i %20.10f %20.10f\n',k,x2,f2)

  if f1<f2
    % minimum bracketed in (a,x2)
    b = x2; % move right endpoint
    x2 = x1; f2 = f1; % x2 <-- x1
    x1 = a+(1-tau)*(b-a); f1 = func(x1); % new x1
  else
    % minimum bracketed in (x1,b)
    a = x1; % move left endpoint
    x1 = x2; f1 = f2; % x1 <-- x2
    x2 = a+tau*(b-a); f2 = func(x2); % new x2
  end
end

% stopping criterion satisfied

x = x2; f = f2; % best guess at minimum
