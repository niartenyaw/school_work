clear;

A = [7,10,-1,3;1,0,6,5;3,-2,9,1;1,2,8,4];
[L,U,P] = lu(A);

for i=1:4
    b=[sin(i) cos(i) 0 1]';
    %Solving for L*y=P*b
    y=L\(P*b);
    
    %Now solving U*x=y
    x=U\y
end