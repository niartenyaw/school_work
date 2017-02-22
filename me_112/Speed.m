clear;

rwheel=0.32;
rpm=0:100:8000;
ratio=0.78*3.9;
t_max=220;
v=[];
v=[v rpm*2*pi*rwheel/(60*ratio)];

Fw=173.637+0.37975*v.^2;
Fp=t_max*ratio/rwheel;
plot(rpm,Fw)
hold all
plot(rpm,Fp)