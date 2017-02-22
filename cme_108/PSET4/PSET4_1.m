% A)
clear;

%u(t)=g1*exp(g2*t)
% v(t) = ln(u(t)) = ln(g1)+g2*t
% x1=ln(g1)
% x2=g2
% v(t) = x1+x2*t

A=[1,0.0 ; 1,1.0 ; 1,2.0];
% b=ln(u);
b=[0.1 0.9 2]';
y=[exp(0.1) exp(0.9) exp(2)];
%A'Ax=A'b
Atb=A'*b;
AtA=A'*A;
x=AtA\Atb;
gamma1=exp(x(1));
gamma2=x(2);
fprintf('Linear Transformation:\n')
fprintf('v(t) = %g + %g*t\n',x(1),x(2))
fprintf('u(t) = %g*exp(%g*t)\n',gamma1,gamma2)
t=[0,1,2];
u=gamma1*exp(gamma2.*t);
residA=norm(y-u)

% B)
clear;
tol=10^(-6);
y=[exp(0.1) exp(0.9) exp(2)];
t=[0.0 1.0 2.0];
x=[1.05127 0.95];
f=[0 0 0]';

for k=1:100
    A=zeros(3,2);
    for i=1:length(y)
        [u,dx1,dx2] = ExpFunc(x(1),x(2),t(i));
        A(i,1)=dx1;
        A(i,2)=dx2;
        f(i)=u-y(i);
    end
    AtA=A'*A;
    Atf=A'*f;
    p=AtA\Atf;
    
    if norm(p) < tol
        break;
    end
    
    x(1)=x(1)-p(1);
    x(2)=x(2)-p(2);
end
gamma1=x(1);
gamma2=x(2);
fprintf('Gauss-Newton iterative:\n')
fprintf('u(t) = %g*exp(%g*t)\n',gamma1,gamma2)
u=gamma1*exp(gamma2.*t);
residB=norm(y-u)

% C)
clear;
tol=10^(-6);
b=[exp(0.1) exp(0.9) exp(2)];
t=[0.0 1.0 2.0];
x=[0 0];
f=[0 0 0]';

for k=1:100
    J=zeros(3,2);
    for i=1:length(b)
        [g,dx1,dx2] = ExpFunc(x(1),x(2),t(i));
        J(i,1)=dx1;
        J(i,2)=dx2;
        f(i)=g-b(i);
    end
    gradient_psi=J'*f;
    M=J'*J;
    N=zeros(2,2);
    for i=1:length(t)
        Hessian_resid=[0,t(i)*exp(x(2)*t(i)) ;...
            t(i)*exp(x(2)*t(i)),t(i)^2*x(1)*exp(x(2)*t(i))];
        N=N+f(i)*Hessian_resid;
    end
    N;
    H_Psi=M+N;
    p=-H_Psi\gradient_psi;
    if norm(p) < tol
        break;
    end
    x(1)=x(1)-p(1);
    x(2)=x(2)-p(2);
end
x(1);
x(2);

