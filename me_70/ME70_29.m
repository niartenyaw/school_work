function [ output_args ] = untitled( input_args )
%[x,y] = meshgrid(0:.5:5);
%M = 10*x + 20;
%N = -10*y;
%Plots the Velocity Field
%b = quiver(x,y,M./sqrt(M.^2+N.^2),N./sqrt(M.^2+N.^2));
%set(b, 'Color', 'b');
%hold on

%The slope of the vector at point (x,y) in the field is given by N/M.
%Solve and plot specific ODE solution where dy/dx = N/M and y(1)=2.
syms t v
e = dsolve('Dv = -10*v/(10*t+20)','v(1)=2');
h = ezplot(e,[0,5]);
set(h, 'Color', 'm');

text(1,2,'\leftarrow point (1,2)','HorizontalAlignment','left')
hold on

e = dsolve('Dv = -10*v/(10*t+20)','v(1)=1');
h = ezplot(e,[0,5]);
set(h, 'Color', 'm');
hold on

e = dsolve('Dv = -10*v/(10*t+20)','v(1)=3');
h = ezplot(e,[0,5]);
set(h, 'Color', 'm');

title('Streamlines for V = (Ax+B)i + (-Ay)j');
xlabel('X');
ylabel('Y');



end

