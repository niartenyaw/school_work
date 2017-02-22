clear;
N=4;
intervals=[4 8 16 32 64 128 256 512];
timerS=[];
timerR=[];

for i=1:length(intervals)
    [T,time]=smatrix(intervals(i));
    timerS=[timerS time];
    
    [T,Terr,time]=matrix(intervals(i));
    timerR=[timerR time];
end

loglog(intervals,timerS)
hold all
loglog(intervals,timerR)

title('Sparse vs Full Matrix Completion Time')
xlabel('Number of Intervals')
ylabel('Time (sec)')
legend('Sparse','Full')