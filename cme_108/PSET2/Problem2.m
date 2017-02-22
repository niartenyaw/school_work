clear;
N=256;
intervals=[4 8 16 32 64 128 256 512];
errors=[];

for i=1:length(intervals)
    [T,Terr]=matrix(intervals(i));
    errors=[errors Terr];
end

loglog(intervals,errors)
title('Error in Approximations vs Number of Intervals')
xlabel('Number of Intervals')
ylabel('Error')