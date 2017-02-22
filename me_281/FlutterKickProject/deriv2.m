function tDD = deriv2(theta,h)
N=length(theta);
o=ones(N,1);
oo=ones(N-1,1);

A=-2/h^2*diag(o,0);
A=A+1/(2*h^2)*diag(oo,-1);
A=A+1/(2*h^2)*diag(oo,1);
% Continuity between cycles
A(N,1)=1/(2*h^2);
A(1,N)=1/(2*h^2);

tDD=A*theta;

end

