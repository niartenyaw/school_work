% script illustrating how to call various subroutines,
% make plots, etc., as done in class on Jan 11, 2013

% to run this script, just put in your working directory
% (or path) and type "nonlinear" in the command line window

% first make plots for loan example

a = 100; % amount borrowed
p = 10;  % yearly payment
n = 20;  % number of years
r = linspace(0,0.1,100); % interest rates (vector)

f = loan(r,a,p,n); % evaluate function f(r)

plot(r,f), grid on
xlabel('interest rate, r')
ylabel('normalized balance')

pause % hit any key to continue

% you can see there is one solution,
% let's find it with bisection
% (note how to pass a function to a subroutine)

[R,err] = bisection(@(r) loan(r,a,p,n),0,0.1,1e-10);

% solution is R

R

% plot error as function of iteration

iter = [1:length(err)]; % vector of interation number

plot(iter,err,'bo') % plot with blue circles
xlabel('iteration'), ylabel('error')

pause

% a log-log or semilog plot is better

loglog(iter,err,'bo') % plot with blue circles
xlabel('iteration'), ylabel('error')

pause

semilogy(iter,err,'bo') % plot with blue circles
xlabel('iteration'), ylabel('error')

