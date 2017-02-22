clear;

I=0:0.01:10;

R=10./(I+1);

plot(I,R)
title('Resistance vs. Light Intensity')
xlabel('Intensity (W/cm^2)')
ylabel('Resistance (Kohms)')