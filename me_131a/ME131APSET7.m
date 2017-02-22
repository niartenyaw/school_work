clear;

x=0.01:0.001:0.1;
h1=403./x.^(1/2);
h2=403./(x+0.1).^(1/2);

plot(x,h1)
hold all
plot(x,h2)
title('Heated plate at (1) and behind (2) leading edge')
xlabel('X (m) (from front of hot plate)')
ylabel('h (W/m^2K)')
legend('Scenario 1','Scenario 2')
%%
clear;

x=0:0.001:0.2;
x1=0:0.001:0.15;
x2=0:0.001:0.1;
qPP1=9.29./(x1+0.05).^(1/2);
qPP2=9.29./(x2+0.05).^(1/2);
qTOT=zeros(length(x),1);
for i=1:length(x)
    qPP=0;
    if x(i)>.049
        qPP=qPP1(i-50);
    end
    if x(i)>0.099
        qPP=qPP+qPP2(i-100);
    end
    qTOT(i)=qPP;
end
qTOT

plot(x,qTOT)
title('Heat Flux from flat Plate')
xlabel('X (m)')
ylabel('q" (W/m^2)')

%%
clear;
time=[0 30 60 90 120 150 180];
temparm=[26.4 25.2 28.1 30.0 31.0 30.7 31.9];
temphead=[19.4 27.1 30.2 32.0 32.8 33.6 34.2];
%plot(time,temparm)
%hold all
%plot(time,temphead)
%legend('forearm','forehead')
%title('Average temperature over time')
%xlabel('Time (s)')
%ylabel('Temperature (C)')

TS1=(temparm-temparm(1))/(temparm(7)-temparm(1));
TS2=(temphead-temphead(1))/(temphead(7)-temphead(1));
%plot(time,TS1)
%hold all
%plot(time,TS2)
%title('Nondimensionalized Temperature over time')
%xlabel('Time (s)')
%ylabel('Non-Dimensional Temperature (T-T(i))/(T(f)-T(i))')
%legend('forearm','forehead')

t1=[33.8

33.6

33.3

33.3

33.7

33.1

33

32.8

32.1

31.3

30

28.4

25.5

22.2

19.6

17.6

16.8

16.3

16.2

16.3

16.2

16.1

16.5

16.9

16.8

16.4

17.1

17.8

18.6

20.5

22.3

24.8

27

28.9

30.3

31.1

32.2

32.2

32.3

32.5

32.6

32.3

32.8

32.4

32.5

32.6

32.5

32.4];

t2=[34

34.1

33.8

33.5

33.1

32.1

31.1

29.7

27.8

25.9

24.2

22.4

20.8

19.7

18.8

18.3

17.6

17.7

17.6

17.4

18.2

18.3

18.8

18.6

18.3

18.4

18.8

18.9

19.9

21

22.5

25

27

28.8

30.6

31.3

32.1

32.2

32.4

32.6

32.5

32.7];

t3=[34.2

34

33.7

33.8

33.5

33.8

33.7

33.6

33.3

32.8

32.3

31.6

30.6

29.6

28.4

27

25.6

24.6

23.7

23

22.4

21.9

21.9

21.7

21.8

21.7

22.5

22.4

22.8

22.2

22.1

22.2

22.2

22.6

23.3

24.2

25.2

27

28.7

29.9

30.6

31.7

31.9

32.3

32

32.2

32.2

32.8

32.8

32.6

32.8];

t4=[34.2

33.9

34

34

33.7

33.5

33.5

33.3

33.3

33.3

32.7

32.3

31.5

30.4

29.4

28.4

27.3

26.2

25.6

24.8

24.4

24.3

24.1

24.5

24.9

25.3

25.9

25.8

26

25.5

25.5

25.4

25.9

26.7

28

29

30.1

30.8

31.6

32.3

32.6

33

33.2

33.5

33.3

33.2

33.1

33.4

33.6

33.5

33.7

33.4];

t5=[34.3

34.2

34.4

34.2

34.1

34.1

34.2

33.9

33.6

33.6

33.7

33.8

33.6

33.3

33.3

33.1

32.5

32.2

31.7

30.9

30.3

29.2

28.6

27.6

26.9

26.3

25.5

25.4

25.4

25.6

26.5

27

27

27.3

27.2

26.8

26.7

26.7

27.3

28

28.9

29.8

30.5

31.3

32.1

32.6

32.8

33.2

33.5

33.7

33.7

33.7

33.5

33.7

33.8

33.7

33.7

34];

t6=[33.7

33.8

33.4

33.2

33.4

32.9

32.7

32.5

32

31.7

30.9

30.3

29.8

28.9

28.5

27.9

27.4

27

26.9

26.7

27.1

27.1

27.5

27.6

27.6

28.6

28.2

27.9

28.2

28.2

28.7

29

29.6

30.2

30.7

31.3

31.9

32.4

32.7

32.9

32.9

33.2

33.3

33.4

33.3

33.7

33.5

33.6

33.8

33.9];

t7=[34.1

34.3

33.9

33.8

34

33.8

33.5

33.5

33.2

33.2

32.8

32.3

31.9

31

30.6

30.1

29.7

29.1

28.5

28.4

28.5

28.5

28.4

29

29.2

29.1

29.3

29.4

29.3

29.3

29.5

29.8

30.3

31

31.7

32.2

32.4

34.3

34.3

34.5

34.6

34.3

34.2

33.9

34.2

34.3

34.2

34.5

34.4

34.6];
x=0:1:size(t1)-1;
xnew=x/length(x);
plot(xnew,t1)
hold all
x=0:1:size(t2)-1;
xnew=x/length(x);
plot(xnew,t2)
x=0:1:size(t3)-1;
xnew=x/length(x);
plot(xnew,t3)
x=0:1:size(t4)-1;
xnew=x/length(x);
plot(xnew,t4)
x=0:1:size(t5)-1;
xnew=x/length(x);
plot(xnew,t5)
x=0:1:size(t6)-1;
xnew=x/length(x);
plot(xnew,t6)
x=0:1:size(t7)-1;
xnew=x/length(x);
plot(xnew,t7)
legend('1','2','3','4','5','6','7');
title('Temperature profiles of the forearm over time')
ylabel('Temperature (C)')
xlabel('Nondimensional Horizontal Distance')

