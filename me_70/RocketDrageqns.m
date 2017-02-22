function g=RocketDrageqns(t,z)
global gr me ve

M=z(1);
y=z(2);
V=z(3);

Af=0.2;
Cd=0.5;
R=8.31432;%Universal gas constant
T=288.15;%Standard Temperature

ro=1.21*exp(-gr*y/(R*T));

Fd=1/2*Cd*ro*V*V*Af;

%This shows when the rocket uses up all of its fuel mass
if M<250%Determines when rocket should be staged
    if M<100%Determines if fuel is gone
      dMdt=0;%Once fuel is gone, no more mass is lost.
      dVdt=0;%Once fuel is gone, the rocket can no longer accelerate.
    else
	  dMdt=-me;
      dVdt=(-Fd+me*ve)/(M-50)-gr;
    end
else
    dMdt=-me;
    dVdt=(-Fd+me*ve)/M-gr;
end
dydt=V;

g=[dMdt dydt dVdt]'; %this needs to be a column vector