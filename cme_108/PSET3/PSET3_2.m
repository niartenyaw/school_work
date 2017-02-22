clear;

eigens=[];
lambdas=[];

tol=10^(-6);

N=64;
h=pi/N;
e=ones(N-1,1);
a=[e -2*e e]/h^2;
A=spdiags(a,[-1 0 1],N-1,N-1);

for i=1:4
    x=newton(A,i);
    x=x./norm(x); %Normalized our guess.
    lambda=x'*A*x;
    
    for g=1:100
        J=[A-eye(size(A))*lambda,-x;2*x',0] %Jacobian
        
        f = [A*x-lambda*x;x'*x-1];
        p=-J\f;
        x=x+p(1:N-1); %Updates x_k
        lambda=lambda+p(end); %updates lambda
        
        if norm(p) < tol*(1+norm(x)) %Tolerance test
            eigens=[eigens x];
            lambdas=[lambdas lambda];
            break;
        end
    end
end
lambdas
t=[1:N-1]'*h;
hold all
for i=1:4
    plot(t,eigens(:,i))
end

title('Eigenvectors')
xlabel('x')
ylabel('Y')
legend('lambda=-0.9998','lambda=-3.9968',...
    'lambda=-8.9837','lambda=-15.9487',...
    'location','southwest')
