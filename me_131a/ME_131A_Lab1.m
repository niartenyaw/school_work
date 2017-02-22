%%
clear;

temp=[30,45,60,75];
resist=[1116,1176,1234,1294];

plot(temp,resist);
title('Electrical Resistance vs. Temperature');
xlabel('Temperature (celsius)');
ylabel('Resistance (ohms)');

%%

clear;

dist=[1.25,2.5,4.75,9.5,17.75];
copper=[51.3,46.5,40.0,34.2,30.3];
alum=[43.7,39.7,33.9,29.1,26.8];
steel=[31.3,26.8,25.9,25.7,25.6];

copperPIC=[42.7,37.2,43.9,45.8,44.1,36.3,33.3,35.1,37.8,42.3,43.5,43.3,42.8,42.0,40.4,35.8,38.1,40.3,39.3,37.6,35.6,38.3,39.2,39.0,38.8,38.9,38.7,38.2,37.8,37.4,36.9,37.1,37.0,36.8,36.8,36.6,36.3,36.0,35.9,35.6,35.7,35.6,35.3,34.5,32.4,33.4,34.4,34.0,33.8,33.9,32.1,31.2,33.4,33.4,33.2,33.0,33.5,33.3,33.2,33.0,32.9,32.8,32.5,32.6,32.3,32.0,32.2,32.2,31.8,31.7,31.7,31.5,31.5,31.2,30.9,31.9,32.1,31.9,31.8,31.8,31.4,31.1,30.0,31.1,31.0,30.2,29.7,30.7,31.0,31.0,31.3,31.1,30.9,30.3,29.4,30.0,30.6,30.5,30.5,30.5,30.5,30.3,30.2,30.3,30.0,30.1,29.8,29.0,29.8,29.6,29.4,29.3,29.6,29.7,29.3];
dist2=0:0.1614:18.5;
length(copperPIC)
length(dist2)
plot(dist,copper);
hold all
plot(dist,alum);
plot(dist,steel);
plot(dist2,copperPIC);
title('Normalized Fin Temperature Distributions');
xlabel('Distance from base (Inches)');
ylabel('Temperature (Celsius)');
legend('Copper','Aluminum','Steel','Copper Thermal Image');

%%
clear;
dist=[1.25,2.5,4.75,9.5,17.75];
copper=[51.3,46.5,40.0,34.2,30.3];
alum=[43.7,39.7,33.9,29.1,26.8];
steel=[31.3,26.8,25.9,25.7,25.6];

plot(dist,copper/51.3);
hold all
plot(dist,alum/43.7);
plot(dist,steel/31.3);
title('Fin Temperature Distributions');
xlabel('Distance from base (Inches)');
ylabel('Normalized Temperature');
legend('Copper','Aluminum','Steel');