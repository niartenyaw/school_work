function SIR=sickeqns(t,y)

global gam beta

S=y(1);
I=y(2);
R=y(3);

dSdt=-beta*S*I;
dIdt=beta*S*I-gam*I;
dRdt=gam*I;



SIR=[dSdt dIdt dRdt]';

