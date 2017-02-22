%PSet 4 Problem 2
clear;

% A)
load tide_data;
k=1:1:720;
newt=t(k);
newh=h(k);
T=[12.420601220444135;23.934469655965803;25.819341664737628;12.000000000000000];

for p=1:4
    figure;
    A=ones(length(newt),p*2+1);
    
    for i=2:p+1
        for j=1:length(newt)
            A(j,i)= cos(2*pi*newt(j)/T(i-1));
        end
    end
    for i=p+2:p*2+1
        for j=1:length(newt)
            A(j,i)= -sin(2*pi*newt(j)/T(i-(p+1)));
        end
    end
    
    Ata=A'*A;
    Atb=A'*newh;
    %f=gauss(Ata,Atb);
    f=Ata\Atb;
    i=2:1:p+1;
    x=f(i);
    y=f(i+p);
    h0=f(1);
    phi=atan2(y,x);
    a=x./cos(phi);
    
    ht= [];
    
    for k=1:length(newt)
        s=0;
        for i=1:p
            s=s+a(i)*cos(2*pi*newt(k)/T(i)+phi(i));
        end
        ht(k)=h0+s;
    end
    plot(newt,newh)
    hold all
    plot(newt,ht)
    string=sprintf('Sea Surface Height Over Time With %g Constituents',p);
    title(string)
    legend('Actual','Calculated')
    xlabel('Time (hours)')
    ylabel('Sea Height (meters)')
    residual=newh-ht';
    norm(residual)
end



