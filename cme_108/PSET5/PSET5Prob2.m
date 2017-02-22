clear;

first=0;
last=2*pi;

for n=2:4
    figure;
    x=linspace(first,last,101);
    
    %Plotting interpolant
    xpoints=linspace(first,last,n+1);
    ypoints=cos(xpoints);
    [a,b,c]=coefficients(first,last,ypoints,n);
    f=interpolant(x,xpoints,a,b,c,first,last);
    plot(x,f)
    
    hold all
    
    % Matlab Spline
    s=spline(xpoints,ypoints,x);
    plot(x,s)
    
    %Complete Spline
    ypoints=[0,ypoints,0];
    s=spline(xpoints,ypoints,x);
    plot(x,s)
    
    %Actual solution
    y=cos(x);
    plot(x,y)
    
    str=sprintf('Splines to y=cos(x) with N=%g',n);
    title(str)
    xlabel('x')
    ylabel('y')
    legend('Interpolant','Spline','Complete Spline','Actual')
end
