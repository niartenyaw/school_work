# Aaron Wayne
# Stats 216
# 2/1/14

setwd("./")
college <- read.csv("College.csv")
rownames(college)=college[,1]
college=college[,-1]
summary(college)
pairs(college[,1:10])
par(mfrow=c(1,2))
plot(college$Outstate)
plot(college$Private)

Elite=rep("No",nrow(college))
Elite[college$Top10perc>50]="Yes"
Elite=as.factor(Elite)
college=data.frame(college,Elite)
summary(Elite)
plot(college$Outstate,Elite)

par(mfrow=c(2,2))
hist(college$Apps, breaks=10)
hist(college$Apps, breaks=20)
hist(college$Apps, breaks=50)
hist(college$Apps, breaks=100)

par(mfrow=c(2,2))
hist(college$PhD, breaks=10)
hist(college$PhD, breaks=50)
hist(college$PhD, breaks=100)
hist(college$PhD, breaks=200)

par(mfrow=c(2,2))
hist(college$Room.Board, breaks=10)
hist(college$Room.Board, breaks=25)
hist(college$Room.Board, breaks=50)
hist(college$Room.Board, breaks=100)

collegetraining = college[1:350,]
collegetest=college[350:777,]

fit<-lm(Apps~.-Elite-Enroll-Accept,collegetraining)
summary(fit)

# The regression has a very significant p-value of 2.2e-16 with a residual standard error of 1345.
# This standard error is very high considering our mean Apps is only 3002.
# A A single standard error from the mean cuts the prediction in half.
# Our model is not a very accurate predictor of Apps.
# The important predictors are: PrivateYes, Top10perc, F.Undergrad, Outstate, Room.Board.
# Expend, perc.alumni, and Grad.Rate for p < 0.05

Y=rep(0,nrow(collegetraining))
Y[collegetraining$Apps>1557]=1;
fit2<-lm(Y~.-Apps-Elite-Enroll-Accept,collegetraining)
summary(fit2)
#The most important predictors are: PrivateYes, Top25perc, F.Undergrad, Outstate, PhD, and Grad.Rate.
pred = predict(fit2,collegetraining)
scores=rep(0,nrow(collegetraining))
scores[pred>=0.5]=1
misclass=rep(0,nrow(collegetraining))
for (i in 1:length(scores)){
  if(scores[i]==Y[i]){
    misclass[i]=0;
  }
  else{
    misclass[i]=1;
  }
}
#Misclassification rate for training data:
sum(misclass)/length(misclass)

Y2=rep(0,nrow(collegetest))
Y2[collegetest$Apps>1557]=1;
pred2 = predict(fit2,collegetest)
scores2=rep(0,nrow(collegetest))
scores2[pred2>=0.5]=1;
misclass2=rep(0,nrow(collegetest))
for (i in 1:length(scores2)){
  if(scores2[i]==Y2[i]){
    misclass2[i]=0;
  }
  else{
    misclass2[i]=1;
  }
}
#Misclassification rate for test data:
sum(misclass2)/length(misclass2)
# Our first model was not very good at predicting the number of Apps
# because its Standard Error was so large.
# Our second model is decent because it misclassifies our test
# data almost 15% of the time. Its performance on the training data
# is very similar. This is better than the first analysis but still
# not great.
