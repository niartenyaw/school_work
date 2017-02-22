%-------------------------Part 1-----------------------------%

Pmax=150*10^3;
Tmax=220;

RPM=(1:1:8000);
t=zeros(1,8000);
P=zeros(1,8000);

%Tmax=Pmax/wc --> wcutoff=Pmax/Tmax
wcutoff=Pmax/Tmax;
RPMcutoff=wcutoff*60/(2*pi);

for i=1:1:8000
    if i<=RPMcutoff
        t(i)=Tmax;
        P(i)=i*2*pi/60*Tmax;
    else
        t(i)=Pmax/(i*2*pi/60);
        P(i)=Pmax;
    end
end

figure
plot (RPM,t)
xlabel('RPM')
ylabel('Torque N-m')
title('RPM vs Torque of AC-150 Electric Motor')

figure
plot (RPM,P)
xlabel('RPM')
ylabel('Power (W)')
title('RPM vs Power for AC-150 Electric Motor')



%---------------------Part 2----------------------------------%

%Modified Holly's Example code to work with our new electric motor.


% Define constants needed for equations
Rw = 0.32; % wheel radius [m]
Rfifth = 0.78; % fifth gear ratio [unitless]
Rfinal = 3.90; % final drive ratio [unitless]
Cd = 0.31; % coefficient of drag [unitless]
A = 2; % vehicle frontal area [m^2]
rho = 1.225; % air density [kg/m^3]
m = 1770; % vehicle mass [kg]
g = 9.81; % gravity [m/s^2]
frr = 0.01; % rolling resistance coefficient
Frr = frr*m*g; % rolling resistance force
OGR = Rfifth*Rfinal; %Rfifth*Rfinal; % overall gear ratio

% plot required force and available force curves
tq = [140 143 148 152 155.5 159 162 163 ...
    160.5 156 147 134 120]; % vector of engine torques [Nm]
RPM = [1000 1500 2000 2500 3000 3500 ...
    4000 4500 5000 5500 6000 6500 7000]; % vector of engine speeds [rpm]
Fwheelfifth = tq*Rfifth*Rfinal/Rw;
Vfifth = RPM*(2*pi/60)*Rw/(Rfinal*Rfifth);
V = 0.01:.01:80;
Floadflat = frr*m*g + 0.5*rho*A*Cd.*V.*V;
Felectric=Pmax./V;


%----Q1 part 2------
Pv=P.*Rw;

length(V)
length(Pv)


figure;
hold on;
for i=.1:.5:2
    plot(V*2.2369,P,'b');
end

plot(V*2.2369,Floadflat.*V,'k')
xlabel('Velocity (mph)')
ylabel('Power (W)')
title('Velocity vs. Power for AC-150 installed in Subaru Legacy')

figure
maxV = 159.5/2.2369;
RPM = 6500:100:8000;
DR = (((2*pi)/60)*RPM*Rw)/maxV;
plot(RPM,DR)
xlabel('RPM')
ylabel('Drive Ratio for Maximum Velocity at each max power RPM')
title('RPM versus Optimal Drive Ratio')



%{
figure;
plot(V*2.2369,Felectric);
hold on;
plot(V*2.2369,Floadflat,'b')
hold on
plot(Vfifth*2.2369,Fwheelfifth,'g');
xlabel('vehicle velocity [mph]');
ylabel('force [N]');
title('Part 8: Flat ground, fifth gear force versus speed');
legend('required force','force generated in 5th gear');
%}


%{
% Define initial conditions for simulations
v0 = 70/2.2369; % starting velocity [m/s]
t0 = 0; % starting time [s]
dt = 0.2; % time step [s]
tf = 200; % final time [s]


% ODE45 integration (Runge-Kutta)
tspan = [t0,tf];
[t,v] = ode45(@(t,v) carODE(t,v,m,OGR,Rw,rho,A,Cd,Frr),tspan,v0);
t_rk = t;
v_rk = 2.2369*v;

figure;
plot(t_rk,v_rk,'r');
legend('Runge-Kutta');
xlabel('time [s]');
ylabel('vehicle speed [mph]');
title('Subaru Acceleration in 5th Gear');
%}

