function [x,err,contains] = hybrid(func,a,b,x0,x1,tol)

x=x1;
err = [];
contains=true;
%Checks for correct order
if a > b
    a=olda;
    a=b;
    b=olda;
end

for k=1:100
    fx0 = func(x0);
    fx1 = func(x1);
    fa=func(a);
    fb=func(b);
    
    if sign(fa)==sign(fb)
        contains=false;
        return
    end
    
    dx = fx1*(x1-x0)/(fx1-fx0);
    x2 = x1-dx;
    
    if x2 < a || x2 > b
        x2 = (b-a)/2+a;
        if(sign(func(x2))==sign(fb))
            b=x2;
        else
            a=x2;
        end
        x0=x1;
        x1=(b-a)/2+a;
        dx=b-a;
    else
        if sign(func(x2)) == sign(fa)
            a = x2;
        else
            b = x2;
        end
        x0=x1;
        x1=x2;
    end
    
    x=x2;
    err = [err abs(dx)];
    
    if abs(dx)<tol
        return
    end
end

end

