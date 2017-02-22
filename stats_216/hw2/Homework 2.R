# Homework 2
# Aaron Wayne
# STATS 216
# 2/14/14


## 1) (a) The Training RSS will (iii) increase steadily. This is because the model will be able to continue to fit the training data closer and closer as the sum maximum value is increased.
#     (b) The Test RSS will (ii) decrease initially and then curve up in a U shape. The model will fit the data better as the maximum sum is increased but at a certain point the training data will be overfitted and will no longer predict test data well.
#     (c) 
#     (d)
#     (e) The irreducible error will (v) stay the same.

## 2) (a) 1-1/n because it is 1 minus the probability that it is chosen. 
#     (b) 1-1/n because we are sampling with replacement so it is the same as the first.
#     (c) The probability of any given sample not being the jth observation is (1-1/n) we must multiply it by itself n times to find the probability that it is not any of the n bootstrap samples. This turns out to be (1-1/n)^n
#     (d) (1-1/5)^5 = 0.3277
#     (e) (1-1/100)^100 = 0.366
#     (f) (1-1/10000)^10000 = 0.368
#     (g) The plot very quickly reaches an asymptote of 0.36786 and does not vary from there. 

probs = seq(1,100000,by=1)
for(i in probs) {
  probs[i]=(1-1/i)^i
}
plot(probs)
plot[10000]

#     (h) The probability is 1 minus the probability asymptote acquired in part (g).
store = rep(NA,10000)
for(i in 1:10000){
  store [i]= sum(sample(1:100,rep=TRUE)==4) > 0
}
mean(store)

## 3) (a) The equation for p(X) must always be a number 0 < p(X) < 1 since e to the power of any number is positive and 1+e^x is always greater than e^x.
#         p*(1-p) = p - p^2
#         Derivative is dL/dp = 1 - 2p
#         1 = 2p
#         Function is a maximum at p = 0.5
#         L(p=0.5) = 0.25
p=seq(0,1,by=0.001)
L=rep(0,1000)
for(i in 1:1000){
  L[i]=p[i]*(1-p[i])
}
plot(L)
#     (b) When B0 << B1, e^(B0 + B1xi) << 1 and e^(B0 - B1|xi|) >> 1
#         D=e^(B0 + B1xi), D/(1+D)~1
#         F=e^(B0 - B1|xi|), 1-F/(1+F)~1
#         This means the product for all xi for which yi=1 is ~ 1
#         Similarly, the product for all xi for which yi=0 is ~ 1
#         The product of two numbers arbitrarily close to one is 1.
#         Since they work together to make a number arbitrarily close to one, there are many combinations of numbers for B0 and B1 that satisfy L>a.
#     (c) HERE
#     (d) 
x=c(seq(0,4,by=0.01),seq(5,10,by=0.01))
# 4 < a < 5
y=c(rep(0,401),rep(1,501))
glm.fit=glm(y~x, family=binomial(logit))
plot(x,y)
summary(glm.fit)
lines(x,predict(glm.fit))

## 4) (a) 
games <- read.csv("http://www.stanford.edu/~wfithian/games.csv",as.is=TRUE)
teams <- read.csv("http://www.stanford.edu/~wfithian/teams.csv",as.is=TRUE)
#Vector with all teams
all.teams <- sort(unique(c(teams$team,games$home,games$away)))

z <- with(games, homeScore>awayScore)
homeAdv <- 1-games$neutralLocation
## Construct a data frame of the right dimensions, with all zeros
X0 <- as.data.frame(matrix(0,nrow(games),length(all.teams)))
names(X0) <- all.teams
## Fill in the columns, one by one
for(tm in all.teams) {
  X0[[tm]] <- 1*(games$home==tm) - 1*(games$away==tm)
}
X0 <- X0[,names(X0) != "stanford-cardinal"]

reg.season.game<-which(games$gameType=="REG")
homeAdv.log.fit<-glm(z~0+homeAdv + ., family="binomial", data=X0)
homeAdv.coef <- coef(homeAdv.log.fit)[paste("`",teams$team,"`",sep="")]
names(homeAdv.coef) <- teams$team
rank.table <- cbind("Model Score"     = homeAdv.coef,
                    "Logistic Rank"   = rank(-homeAdv.coef,ties="min"),
                    "AP Rank"         = teams$apRank,
                    "USAT Rank"       = teams$usaTodayRank)
rank.table[order(homeAdv.coef,decreasing=TRUE)[1:25],]
# Not sure why I didn't get those schools on my top list?

#   (b)
X <- X0[,names(X0)]
for(tm in all.teams){
  if((sum(games$home==tm) + sum(games$away==tm)) < 5){
    X <- X[,names(X) != tm]
  }
}
X <- X[,names(X) != "stanford-cardinal"]
homeAdv.more4.log.fit<-glm(z~0+homeAdv + ., family="binomial", data=X)
homeAdv.more4.coef <- coef(homeAdv.more4.log.fit)[paste("`",teams$team,"`",sep="")]
names(homeAdv.more4.coef) <- teams$team
rank.table <- cbind("Model Score"     = homeAdv.more4.coef,
                    "Logistic Rank"   = rank(-homeAdv.more4.coef,ties="min"),
                    "AP Rank"         = teams$apRank,
                    "USAT Rank"       = teams$usaTodayRank)
rank.table[order(homeAdv.more4.coef,decreasing=TRUE)[1:25],]


#Linear
y <- with(games, homeScore-awayScore)
homeAdv.mod <- lm(y ~ 0 + homeAdv + ., data=X)
homeAdv.coef.lin <- coef(homeAdv.mod)[paste("`",teams$team,"`",sep="")]
names(homeAdv.coef.lin) <- teams$team

rank.table <- cbind("Model Score"     = homeAdv.coef,
                    "Logistic Rank"   = rank(-homeAdv.coef,ties="min"),
                    "Linear Rank"     = rank(-homeAdv.coef.lin,ties="min"),
                    "AP Rank"         = teams$apRank,
                    "USAT Rank"       = teams$usaTodayRank)
rank.table[order(homeAdv.coef,decreasing=TRUE)[1:25],]
# The log model seems to be closer to both the AP and USAT rankings.

# (c)
resids <- homeAdv.mod$resid
sigma <- sd(resids)
losing.teams <- c(teams$team,nrow(teams))
names(losing.teams) <-teams$team
for(tm in all.teams){
  mu <- coef(homeAdv.mod)["homeAdv"] + coef(homeAdv.mod)[tm] - 0
  losing.teams[tm]<-pnorm(-mu/sigma)
}
summary(losing.teams)

