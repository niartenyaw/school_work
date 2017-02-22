function [ output_args ] = untitled( input_args )
%CME 102 PSET #6-4

J0(8,5)
besselj(0,8)

function a = J0coef(n)
    a(1)=1;
    a(2)=0;
    for k=3:n+1
        a(k)=-a(k-2)/(k-1)^2;
    end
end

function j = J0(x,n)
    % Compute the power series sum using a for loop.
    % Note that this code allows for the input x to
    % be a vector.
    j = 0;
    a = J0coef(n);
    for i = 0:(n-1)
      j = j + a(i+1) * x.^i;    
      % ".^" makes the code work with a vector x
    end
end

end

