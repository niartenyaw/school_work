function f = psi(x,y,v,a,gradient)

f=0;
update=x-a*gradient;
for i=1:length(x)-1
    partial = sqrt((y(i+1)-y(i))^2+(update(i+1)-update(i))^2);
    f=f+1/v(i)*partial;
end
end

