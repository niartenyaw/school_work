function [int,y] = Simpson(x,func)

for i=1:length(x)
    y(i)=func(x(i));
end

int=0;
for k=2:2:length(x)
    hi=x(k)-x(k-1);
    hi1=x(k+1)-x(k);
    term_1=y(k-1)*(hi+hi1)*(2*hi-hi1)/(6*hi);
    term_2=y(k)*(hi+hi1)^3/(6*hi*hi1);
    term_3=y(k+1)*(hi+hi1)*(2*hi1-hi)/(6*hi1);
    int=int+term_1+term_2+term_3;
end

end

