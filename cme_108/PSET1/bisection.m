function [p,err]=bisection(func,a,b,tol)

  fa = func(a);
  fb = func(b);

  if sign(fa)==sign(fb)
    disp('error: root not bracketed')
    p = NaN; err = NaN;
    return
  end

  n = 0; err = [];
  while b-a>tol
    n = n+1;
    err = [err b-a];
    p = (a+b)/2;
    fp = func(p);
    %disp([a p b])
    fprintf('%6i %20.10f %20.10f %20.10f\n',n,a,p,b)
    if sign(fp)==sign(fa)
      a = p;
    else
      b = p;
    end
  end