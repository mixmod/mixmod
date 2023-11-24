##--------------------------------------
## Code for testing the Rmixmod package
##--------------------------------------

# install packages

if (!require("Rmixmod")) install.packages("Rmixmod")
library("Rmixmod")

# 3.2. Companion functions for model definition

# Continuous variables: Gaussian models

all <- mixmodGaussianModel()
all

list.models <- mixmodGaussianModel(listModels = c("Gaussian_p_L_C", "Gaussian_p_L_Dk_A_Dk", 
  "Gaussian_pk_Lk_B"))
only.free.proportions <- mixmodGaussianModel(equal.proportions = FALSE)
family.models <- mixmodGaussianModel(family = c("general", "spherical"), free.proportions = FALSE)

# Categorical variables: Multinomial models

all <- mixmodMultinomialModel()
all
only.free.proportions <- mixmodMultinomialModel(equal.proportions = FALSE)
list.models <- mixmodMultinomialModel(listModels = c("Binary_p_E", "Binary_p_Ekjh", 
  "Binary_pk_Ekj", "Binary_pk_Ej"))
var.independent <- mixmodMultinomialModel(variable.independency = TRUE)
var.comp.independent <- mixmodMultinomialModel(variable.independency = TRUE, component.independency = TRUE)

# 3.3. Companion function for maximum likelihood estimation strategies

mixmodStrategy()
strategy1 <- mixmodStrategy(algo = "CEM", initMethod = "random", nbTry = 10, epsilonInInit = 1e-06)
strategy2 <- mixmodStrategy(algo = c("SEM", "EM"), nbIterationInAlgo = c(200, 100), 
  epsilonInAlgo = c(NA, 1e-04), seed = 2408)

# 4.1. Unsupervised classification

# Continuous variables: Geyser dataset NB: results may be different from the
# paper because of possible local maxima of the likelihood

data("geyser", package = "Rmixmod")
xem.geyser <- mixmodCluster(data = geyser, nbCluster = 2:8, criterion = c("BIC", 
  "ICL", "NEC"), models = mixmodGaussianModel(), strategy = strategy2)
xem.geyser
summary(xem.geyser)
plot(xem.geyser)
icl <- sortByCriterion(xem.geyser, "ICL")
icl["bestResult"]
xem.geyser["results"]
icl["results"]

# Categorical variables: Birds of different subspecies

data("birds", package = "Rmixmod")
xem.birds <- mixmodCluster(birds, 2, strategy = mixmodStrategy(seed = 2408))
plot(xem.birds)
barplot(xem.birds)

# 4.2. Supervised classification

# First step: Learning

data("finance", package = "Rmixmod")
ratios2002 <- subset(finance, Year == 2002, 3:6)
health2002 <- subset(finance, Year == 2002, 2, drop = TRUE)
ratios2003 <- subset(finance, Year == 2003, 3:6)
health2003 <- subset(finance, Year == 2003, 2, drop = TRUE)
learn <- mixmodLearn(ratios2002, health2002, nbCVBlocks = nrow(finance))
learn["bestResult"]
plot(learn)

# Second step: Prediction

prediction <- mixmodPredict(data = ratios2003, classificationRule = learn["bestResult"])
summary(prediction)
mean(as.integer(health2003) == prediction["partition"]) 
