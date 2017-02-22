clear;

%Constants
V=36.0;
K=0.0333;
R=40.0;
tf=.000147;
ts=K*V/R;

%Omega at 36 Volts

wnl= V/K-R/K^2*tf;
slope=-wnl/ts;
t=tf:.00001:ts;
w=wnl+slope.*(t);

plot(t*10^3,w)
grid on
hold all

%Omega at 24 Volts
V=24.0;
ts=K*V/R;
t=tf:.00001:ts;
wnl= V/K-R/K^2*tf;
slope=-wnl/ts;
w=wnl+slope.*(t);

plot(t*10^3,w)
legend('36 Volts','24 Volts')
title('W vs T')
xlabel('Torque (mNm)')
ylabel('W (rad/s)')


%Power at 36 Volts
figure;
Volt=[36.0 24.0];
for i=1:length(Volt)
    V=Volt(i);
    ts=K*V/R;
    t=0:.00001:ts;
    Pout=-R/K^2.*(t+tf).^2+(V/K-R/K^2*tf).*(t+tf);
    plot(t*10^3,Pout)
    grid on
    hold all
end
legend('36 Volts','24 Volts')
title('Power vs Torque')
xlabel('Torque (mNm)')
ylabel('Power (W)')


%Efficiency vs Torque
figure;
V=[24.0 36.0];
for i=1:length(V)
    Volt=V(i);
    ts=K*Volt/R;
    t=0:.00001:ts;
    tl=t-tf;
    slope=-wnl/ts;
    w=wnl+slope.*(t);
    
    N=tl.*w./(Volt.*(tl+tf)/K);
    plot(t*10^3,N)
    hold all
end
title('Efficiency vs Torque')
xlabel('Torque (mNm)')
ylabel('Efficiency')
legend('36 Volts','24 Volts')


%Efficiency vs Current 36 Volts
figure;
V=36.0;
inl=tf/K;
is=V/R;
i=inl:.00001:is;
Pout=(i-inl).*(is-i).*R;
Pin=V.*i;
n=Pout./Pin;
plot(i,n)
hold all
grid on

%Efficiency vs Current 24 Volts
V=24.0;
inl=tf/K;
is=V/R;
i=inl:.00001:is;
Pout=(i-inl).*(is-i).*R;
Pin=V.*i;
n=Pout./Pin;
plot(i,n)
title('Efficiency vs Current')
xlabel('Current (A)')
ylabel('Efficiency')
legend('36 Volts','24 Volts')
