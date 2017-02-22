function [ output_args ] = untitled( input_args )
%ME 70 Lab
DENw = 998;
Aj=3.167E-5;
Pair0=482500;
Vw0=2E-3;
Patm=101325;
gamma=1.4;
k=0.1;
Vair0=3.5E-3;
Vtot=5.5E-3;
dt=1/1000;

t= (0:dt:5);
n=length(t);
F=zeros(1,n);
Pa=zeros(1,n);
Vw=zeros(1,n);
Vj=zeros(1,n);

Pa(1)=Pair0;
Vw(1)=Vw0;

for i=1:n-1
    Vj(i)=sqrt(2*(Pa(i)-Patm)/(DENw*(1+k)));
    F(i)=DENw*(Vj(i))^2*Aj;
    Vw(i+1)=Vw(i)+dt*(-Vj(i)*Aj);
    Pa(i+1)=Pair0*(Vair0/(Vtot-Vw(i+1)))^gamma;
end

plot(t,Vw(1:n))
axis([0 4 0 2E-3]);


end

