clear;
torque_limit=220;
power_limit=150000;
speed_limit=8000;

[rpm,t,p]=torque(torque_limit, power_limit, speed_limit);

plot(rpm,p)
title('Power v RPM in First Gear')
xlabel('Engine (RPM)')
ylabel('Power (kW)')