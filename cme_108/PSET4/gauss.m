function x = gauss(A,b)
%
% gauss(A,b) solves Ax=b for x using Gaussian
% elimination without pivoting
  
  n = length(b);
  [n1,n2] = size(A);

  x = zeros(n,1);
  
  if n1~=n || n2~=n
    disp('incorrect size of A or b')
    x = NaN;
    return
  end
  
  % transform A to upper triangular form
  
  for k=1:n-1 % loop over n-1 elimination stages
    for i=k+1:n % loop over all rows below k in each stage
      lik = A(i,k)/A(k,k); % scaling factor
      for j=k:n % loop through elements in each row 
		% (start from k instead of k+1 to zero out A(i,k)) 
	A(i,j) = A(i,j)-lik*A(k,j);
      end
      b(i) = b(i)-lik*b(k);
    end
  end
  
  %disp([A b]) % uncomment to print modified A and b to screen

  % backward substitution
  
  x(n) = b(n)/A(n,n);
  for i=n-1:-1:1
    x(i) = (b(i)-A(i,i+1:n)*x(i+1:n))/A(i,i);
  end