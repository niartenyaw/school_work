function [x,err]=newton(func,x0,tol)

  x = x0;
  err = [];

  for k=1:100
    [f,dfdx] = func(x);
    dx = -f/dfdx;
    err = [err abs(dx)];
    fprintf('%6i %20.10f %20.10f %20.10f\n',k,x,dx,f)
    if abs(dx)<tol, return, end
    x = x+dx;
  end

  disp('error: Newton not converged, possibly incorrect solution')
end