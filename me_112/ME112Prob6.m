clear;
B=0.5;
Tact=0.12;
t1=0:0.001:.12;

at1=1-exp(-t1./Tact);
plot(t1,at1)
hold all
grid on

t2=0.12:.001:2;
at2=1.04219*exp(-t2.*B/Tact);
plot(t2,at2)
title('Muscle Activation')
xlabel('Time (sec)')
ylabel('a(t)')