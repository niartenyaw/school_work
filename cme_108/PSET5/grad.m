function g = grad(x,y,v)

g=zeros(length(x),1);
g(1)=0;
g(end)=0;
for i=2:length(x)-1
    first_term = (x(i)-x(i-1))/(v(i-1)*sqrt((y(i)-y(i-1))^2+(x(i)-x(i-1))^2));
    second_term = (x(i+1)-x(i))/(v(i)*sqrt((y(i+1)-y(i))^2+(x(i+1)-x(i))^2));
    g(i) = first_term-second_term;
end
end

