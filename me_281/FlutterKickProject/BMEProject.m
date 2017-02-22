clear;
close all
%close all

% 3=hip & thigh
% 2=knee & shank
% 1=ankle & foot

% Parameters of the leg
% 'r' is the distance to the center of mass from cadaver studies
l3=.7;
r3=l3*.43;
l2=.5;
r2=l2*.444;
l1=.3;
r1=l1*.42;

% Masses in kg
m1=1.30;
m2=4.31;
m3=9.52;

% Moments of Inertia from cadaver studies
I1=.015;
I2=.043;
I3=.103;

% Density of water in kg/m^3
p=1000;

% Coronal area of each limb in m^2
Area3=0.05;
Area2=0.02;
Area1=0.03;

% Angle Data (in degrees)
% Each is measured from the horizontal
% Hip
hip=[-20,-10,-8,-6,-5,-9,-14,-19,-25,-29,-27,-22]';
knee=[-11,-11,2,9,22,33,37,37,29,14,6,-7]';
ankle=[-45,-40,-33,-28,-23,6,5,16,2,-3,-16,-30]';
theta3=hip;
theta2=knee;
theta1=ankle;
% Time step
h=1/30;

% Plotting Angle data
xx=0:h:h*length(theta1)-h;
figure;
plot(xx,theta3)
axis([0 0.4 -60 60])
hold all
grid on
plot(xx,theta2)
plot(xx,theta1)
title('Angle of limb from Horizontal')
xlabel('Time (seconds)')
ylabel('Angle From Horizontal (degrees)')
legend('Thigh','Shank','Foot')

%Ankle Flexibility
figure;
plot(xx,theta1-theta2)
title('Ankle Flexibility (0 degrees is when foot and shank are in line)')
xlabel('Time (seconds)')
ylabel('Angle between shank and foot')

% Change degrees to radians
theta3=theta3.*pi/180;
theta2=theta2.*pi/180;
theta1=theta1.*pi/180;

% Finding angular velocities
t1D=deriv(theta1,h);
t2D=deriv(theta2,h);
t3D=deriv(theta3,h);
figure;
plot(xx,t3D)
hold all
grid on
plot(xx,t2D)
plot(xx,t1D)
title('Angular Velocity at joints')
xlabel('Time (seconds)')
ylabel('Angular Velocity (rad/s)')
legend('Thigh','Shank','Foot','Location','northwest')

% Finding angular accelerations
t1DD=deriv2(theta1,h);
t2DD=deriv2(theta2,h);
t3DD=deriv2(theta3,h);

%x and y velocities at each limb
x3D=-l3.*sin(theta3).*t3D;
y3D=l3.*cos(theta3).*t3D;

x2D=x3D-l2.*sin(theta2).*t2D;
y2D=y3D+l2.*cos(theta2).*t2D;

x1D=x2D-r1.*sin(theta1).*t1D;
y1D=y2D+r1.*cos(theta1).*t1D;

%x and y accelerations at each limb
x3DD=-l3.*cos(theta3).*t3D-l3.*sin(theta3).*t3DD;
y3DD=-l3.*sin(theta3).*t3D+l3.*cos(theta3).*t3DD;

x2DD=x3DD-l2.*cos(theta2).*t2D-l2.*sin(theta2).*t2DD;
y2DD=y3DD-l2.*sin(theta2).*t2D+l2.*cos(theta2).*t2DD;

x1DD=x2DD-r1.*cos(theta1).*t1D-r1.*sin(theta1).*t1DD;
y1DD=y2DD-r1.*sin(theta1).*t1D+r1.*cos(theta1).*t1DD;

thrust=[];
% Drag force
for i=1:length(theta1)
    %Af determined by projection
    %Cd determined linearly between a body in streamline and a body that is
    %horizontal
    
    % Foot
    Cd=0.7+0.3*cos(theta1(i));
    Af=Area1*cos(theta1(i));
    Fdy1(i)=1/2*p*Cd*Af*y1D(i)^2;
    
    Cd=0.7+0.3*sin(theta1(i));
    Af=Area1*sin(theta1(i));
    Fdx1(i)=1/2*p*Cd*Af*x1D(i)^2;
    
    % Shank
    Cd=0.7+0.3*cos(theta2(i));
    Af=Area2*cos(theta2(i));
    Fdy2(i)=1/2*p*Cd*Af*y2D(i)^2;
    
    Cd=0.7+0.3*sin(theta2(i));
    Af=Area2*sin(theta2(i));
    Fdx2(i)=1/2*p*Cd*Af*x2D(i)^2;
    
    % Thigh
    Cd=0.7+0.3*cos(theta3(i));
    Af=Area3*cos(theta3(i));
    Fdy3(i)=1/2*p*Cd*Af*y3D(i)^2;
    
    Cd=0.7+0.3*sin(theta3(i));
    Af=Area3*sin(theta3(i));
    Fdx3(i)=1/2*p*Cd*Af*x3D(i)^2;
    
    %Determines if limb is producing drag or forward thrust
    % Foot
    if theta1(i)<0
        if y1D(i)>0
            Fdy1(i)=-Fdy1(i);
            Fdx1(i)=-Fdx1(i);
        end
    elseif theta1(i)>0
        if y1D(i)<0
            Fdy1(i)=-Fdy1(i);
            Fdx1(i)=-Fdx1(i);
        end
    end
    % Shank
    if theta2(i)<0
        if y2D(i)>0
            Fdy2(i)=-Fdy2(i);
            Fdx2(i)=-Fdx2(i);
        end
    elseif theta2(i)>0
        if y2D(i)<0
            Fdy2(i)=-Fdy2(i);
            Fdx2(i)=-Fdx2(i);
        end
    end
    % Thigh
    if theta3(i)<0
        if y3D(i)>0
            Fdy3(i)=-Fdy3(i);
            Fdx3(i)=-Fdx3(i);
        end
    elseif theta3(i)>0
        if y3D(i)<0
            Fdy3(i)=-Fdy3(i);
            Fdx3(i)=-Fdx3(i);
        end
    end
    forward_force=Fdx1(i)+Fdx2(i)+Fdx3(i);
    thrust=[thrust forward_force];
end

% Make horizontal vectors vertical
Fdy1=Fdy1';
Fdx1=Fdx1';
Fdy2=Fdy2';
Fdx2=Fdx2';
Fdy3=Fdy3';
Fdx3=Fdx3';

% Equations for Forces at each joint
Fy1=Fdy1-m1.*y1DD;
Fx1=Fdx1-m1.*x1DD;

Fy2=Fy1-Fdy2-m2.*y2DD;
Fx2=Fx1+Fdx2-m2.*x2DD;

Fy3=Fy2+Fdy3-m3.*y3DD;
Fx3=Fx2+Fdx3-m3.*x3DD;

% Equations for Torques at each joint
T3=-Fy3*l3;
T2=T3-Fy2.*(l3-r3).*cos(theta3)-Fx2.*(l3-r3).*sin(theta3)...
    -Fx3.*r3.*sin(theta3)-Fy3.*r3.*cos(theta3)+I3.*t3DD;
T1=T2-Fy1.*(l2-r2).*cos(theta2)-Fy2.*r2.*cos(theta2)+Fx1.*(l2-r2).*sin(theta2)...
    +Fx2.*r2.*sin(theta2)+I2.*t2DD;

% Convert Nm to kNm
T3=T3/1000;
T2=T2/1000;
T1=T1/1000;

figure;
plot(xx,T3)
title('Torque over time')
xlabel('Time (seconds)')
ylabel('Torque (kNm)')
hold all
grid on
plot(xx,T2)
plot(xx,T1)
legend('Hip','Knee','Ankle')

figure;
plot(xx,thrust)
title('Total Force Produced in the Direction of Motion')
xlabel('Time (seconds)')
ylabel('Thrust (N)')

