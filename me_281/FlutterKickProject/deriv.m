function tD = deriv(theta,h)
N=length(theta);

oo=ones(N-1,1);

A=1/(2*h)*diag(oo,-1);
A=A-1/(2*h)*diag(oo,1);

% Continuity between cycles
A(N,1)=-1/(2*h);
A(1,N)=1/(2*h);

tD=A*theta;

end
