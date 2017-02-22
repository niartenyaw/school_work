clear;
L = 1;
m = 1;
g = 9.81;
x=pi/3:.01:2*pi/3;

theta0=2*pi/3;
thetaD0=-1;
thetaDD=-1;
t=0:.01:.76;

thetaD=thetaDD.*t+thetaD0;
theta=1/2*thetaDD*t.^2 + thetaD0.*t+theta0;

Fy=m*g*(sin(theta).^2) - L.*sin(theta)*m.*thetaD.^2;
theta = theta*180/pi;

thet=1;
F=m*g*(sin(x).^2) - L.*sin(x)*m*thet^2;
x=x*180/pi;

plot(x,F);

title('Ground Reaction Force with Constant Angular Velocity');
xlabel('Theta (Degrees)');
ylabel('Vertical Reaction Force (Newtons)');