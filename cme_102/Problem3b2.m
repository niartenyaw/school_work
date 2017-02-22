function [ output_args ] = untitled( input_args )
[x,y] = meshgrid(-5:.5:5);
M = ones(size(x));
N = -4*x./y;
b = quiver(x,y,M./sqrt(M.^2+N.^2),N./sqrt(M.^2+N.^2));
set(b, 'Color', 'b');

hold on

syms t v
e = dsolve('Dv = -4*t/v','v(1)=1');
h = ezplot(e,[-5,5]);
set(h, 'Color', 'm');

hold on

e = dsolve('Dv = -4*t/v','v(0)=2');
h = ezplot(e,[-5,5]);
set(h, 'Color', 'm');


title('Slope Field and Specific Solutions');
xlabel('X')
ylabel('Y(X)')

end

