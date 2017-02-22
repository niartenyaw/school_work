clear;

T=0:.1:100;
V_plus=10;
R_sense=20+T./100*10;
f=zeros(2,1);



R1=100;
R2=10;
R_load=20*R1/R2;


V_out=3*V_plus.*(R_sense./(R_sense+R_load)-R2/(R1+R2));
V_out(1)
V_out(length(V_out))


C=ones(length(V_out),2);
C(:,1)=30*ones(length(V_out),1);
C(:,2)=-30*ones(length(V_out),1);


%[x,resnorm]=lsqnonneg(C,V_out);
%x