clear;
smallLimit=-5;
largeLimit=5;
tol=10^(-6);
N=5;

roots = [];

intSize=(largeLimit-smallLimit)/N;

for i=smallLimit:intSize:largeLimit-intSize;
    x0=i+intSize/3;
    x1=i+intSize*2/3;
    
    [x,err,contains] = hybrid(@(t) P3(t),i,i+intSize,x0,x1,tol);
    if contains
        roots=[roots x];
    end
end

roots