function [rpm,t,p] = torque(t_max,p_max,s_max)

rpm=[];
t=[];
p=[];
w=rpm.*2*pi/60;

for i=0:80
    w=i*100*2*pi/60;
    currT=t_max;
    currP=currT*w;
    if currT*w>p_max
        currT=p_max/w;
    end
    if currP>p_max
        currP=p_max;
    end
    rpm=[rpm i*100];
    t=[t currT];
    p=[p currP/1000];
    
end

end