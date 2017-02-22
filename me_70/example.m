%% Equations
global gr me ve
%these are the constants used
gr=9.8;
me=5;
ve=3500;
%intitial conditions
y0=0;
v0=0;
m0=400;
%initial and final times
to=0;
tmx=80;
%initial condition vector (ode45 needs this)
zo=[m0;y0;v0];

%this is the only important line here:
[t,z]=ode23s('exampleeqns',[to, tmx], zo);
%% Mass
figure(1)
plot(t,z(:,1), 'c');
title('Mass of rocket over time');
xlabel('time(sec)');
ylabel('M(t)');
%% Altitude
figure(2)
plot(t,z(:,2), 'r');
title('Altitude of rocket over time');
xlabel('time(sec)');
ylabel('y(t)(meters)');
%% Velocity
figure(3)
plot(t,z(:,3), 'o');
title('Velocity of rocket over time');
xlabel('time(sec)');
ylabel('V(t)(meter/sec)');




