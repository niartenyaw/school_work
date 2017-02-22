clear;
%Given vectors and matrix
r=[0.1;0.2];
theta=[-3*pi/4 -pi/4 pi/4 3*pi/4];
u=[-0.26,-0.09,0.11,0.32;-0.42,-0.17,0.15,0.45];
Matrix_A=[1;1;1;1;1;1;1;1];

Aint=1;
rint=1;
% Form equation in form Ax=b
%Assigns values to our b vector
while rint<3
    for j=1:length(theta)
        b(Aint)=u(rint,j)/(sqrt(r(rint))*sin(theta(j)/2));
        Aint=Aint+1;
    end
    rint=rint+1;
end
b=b';

A=Matrix_A\b