function [a,b,c] = coefficients(first,last,ypoints,n)

h=(last-first)/n;
y_prime=0;
a = zeros(1,n-1);
b = zeros(1,n-1);
c = zeros(1,n-1);

for i=1:n
    a(i)=ypoints(i);
    b(i)=y_prime;
    c(i)=1/h^2*(ypoints(i+1)-a(i)-b(i)*h);
    
    %Update to y_prime
    y_prime= b(i) + 2*c(i)*h;
end

end

