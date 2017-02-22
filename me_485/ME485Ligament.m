%%
nums=size(data);

lumbar=data(:,128);
kneeR=data(:,130);
kneeL=data(:,132);
sum=0;
time_step=0.5/nums(2);

for i=1:1424
    sum=sum+(time_step)*(lumbar(i+1)+lumbar(i))/2;
    sum=sum+(time_step)*(kneeR(i+1)+kneeR(i))/2;
    sum=sum+(time_step)*(kneeL(i+1)+kneeL(i))/2;
end
sum*.001


optimal=data(:,134);
time=data(:,135);
optimal_data=[];
time_data=[];
for i=1:94
    optimal_data=[optimal_data optimal(i)/75.1658];
    time_data=[time_data time(i)];
end

time_mine=[];
forces_mine=[];

for i=1:495
    time_mine=[time_mine data(i,1)];
    sum=data(i,87)+data(i,81)+data(i,117)+data(i,123);
    forces_mine=[forces_mine sum];
end

plot(time_data,optimal_data)
hold all
plot(time_mine,forces_mine)
title('Optimal and Observed Y-axis GRF')
legend('Optimal','Observed')
xlabel('Time (s)')
ylabel('GRF (N/kg)')


%%

resultants=[];
time=[];
for i=1:500
    time=[time data(i,1)];
    result=sqrt(data(i,11)^2+data(i,12)^2+data(i,13)^2);
    resultants=[resultants result/75.1658];
end

plot(time,resultants)
title('Resultant Hip Force Normalized by BW')
xlabel('Time (s)')
ylabel('Force in Hip (N/kg)')


%%

time=[];
excitation=[];
time2=[];
force=[];
for i=1:550
    time=[time controls(i,1)];
    excitation=[excitation controls(i,21)];
    time2=[time2 data(i,1)];
    force=[force data(i,21)];
end

plot(time,excitation)
hold all
plot(time2,force/6865)
title('Excitations and Normalized Forces in Vas Int')
xlabel('Time (s)')
ylabel('Excitation and Normalized Muscle Force')
legend('Excitation','Force','location','east')



