function [ output_args ] = untitled( input_args )
[x,y] = meshgrid(-5:.1:5);
M = 5;
N = 5*y;
b = quiver(x,y,M./sqrt(M.^2+N.^2),N./sqrt(M.^2+N.^2));
set(b, 'Color', 'b');
axis([0 1 0 1]);

end

