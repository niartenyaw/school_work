clear;

load hiking_trail;
dx=X(2)-X(1);
int=0;
for i=2:length(X)
    f(i)=evalfunc(X,Y,i);
end

for i=2:2:length(X)-1
    sum=f(i-1)+4*f(i)+f(i+1);
    
    int=int+(dx*2)/6*sum;
end
int