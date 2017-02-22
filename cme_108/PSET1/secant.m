function [x,err] = secant(func,x0,x1,tol)
  
  err = [];
  for k=1:100
      fx0 = func(x0);
      fx1 = func(x1);
      dx = fx1*(x1-x0)/(fx1-fx0);
      err = [err abs(dx)];
      x = x1-dx;
      if abs(dx) < tol 
          return
      end
      x0=x1;
      x1=x;
  end

end