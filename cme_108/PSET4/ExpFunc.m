function [u,dx1,dx2] = ExpFunc(g1,g2,t)

u=g1*exp(g2*t);
dx1=exp(g2*t);
dx2=t*g1*exp(g2*t);

end

