% 1 a

clear;
% Given T*A=L*U
% Solve Ax=b for any b

% The algorithm will only require O(n^2) flops because there
% will be one nested for loop inside another which each solve
% in O(n) making it overall O(n^2)

% L*y=T*b solve for y
b=T*b;
y(1)=b(1); %first line
%Forward substitution
for i=2:n
    sumY=0;
    for j=1:i-1
        sumY=sumY+L(i,j)*y(j);
    end
    y(i)=(b(i)-sumY)./L(i,i);
end

%U*x=y solve for x
x(n)=y(n)/U(n,n); %Last line
%Backwards substitution
for i=n-1:-1:1
    sumX=0;
    for j=i+1:n
        sumX=sumX+U(i,j)*x(j);
    end
    x(i)=(y(i)-sumX)./U(i,i);
end
x

