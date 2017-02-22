function [u,x] = solve(N)
tol=10^(-6);
a=(-10);
[D,x]=cheb(N);

A=D*D;
A(:,1)=zeros(N+1,1);
A(:,N+1)=zeros(N+1,1);
A(N+1,:)=zeros(1,N+1);
A(1,:)=D(1,:);
A(N+1,N+1)=1;

u=ones(N+1,1);

for k=1:100
    b=exp(u.*a);
    b(1)=1;
    b(N+1)=0;
    
    r=A*u+b;
    
    z=[0;b(2:N).*a;0];
    grad_r=A+diag(z,0);
    
    grad_psi=grad_r'*r;
    M=grad_r'*grad_r;
    G=diag(z.*a.*r,0);
    grad2_psi=M+G;
    
    p=grad2_psi\(-grad_psi);
    if norm(p)<tol, break, end
	u=u+p;
end

end

