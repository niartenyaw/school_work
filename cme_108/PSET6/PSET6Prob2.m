clear;
figure;
[u,x]=solve(16);
plot(x,u)
title('u''''(x) + exp(a*u(x)) = 0')
xlabel('x')
ylabel('u(x)')

figure;
[u_exact,x_exact]=solve(512);
err=[];
for i=1:6
    N=2^i;
    [u,x]=solve(N);
    sum=0;
    for k=1:N+1
        index=acos(x(k))*512/pi;
        index=round(index)+1;
        sum=sum+(u(k)-u_exact(index))^2;
    end
    e=sqrt(1/(N+1)*sum);
    err=[err e];
end
i=[1 2 3 4 5 6];
semilogy(2.^i,err)
title('Error vs N')
xlabel('N')
ylabel('Error')

