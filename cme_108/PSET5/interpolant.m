function f = interpolant(x,xpoints,a,b,c,first,last)

h=101/length(a);

f=[];
for i=1:length(a)
    x_curr = x(1+floor((i-1)*h):floor(i*h));
    z=a(i)+b(i)*(x_curr-xpoints(i))+c(i)*(x_curr-xpoints(i)).^2;
    f=[f,z];
end
end