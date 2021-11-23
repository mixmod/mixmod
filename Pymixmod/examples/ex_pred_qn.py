"""
library(Rmixmod)
df=read.csv('/home/poli/mixmod/trunk/dev/components/Pymixmod/trunk/data/iris.csv')
#remaining.obs<-sample(1:nrow(df),10)
remaining.obs<-c(17, 101, 149,  33, 120,  73,  58,  25, 147, 148)
remaining.obs <- remaining.obs + 1
learn<-mixmodLearn(iris[-remaining.obs,1:4], iris$Species[-remaining.obs])
# create a MixmodPredict to predict those 10 observations
prediction <- mixmodPredict(data=iris[remaining.obs,1:4], classificationRule=learn["bestResult"])
# show results
prediction
# compare prediction with real results
paste("accuracy= ",mean(as.integer(iris$Species[remaining.obs]) == prediction["partition"])*100,"%",sep="")
"""
from __future__ import (absolute_import, division,
                        print_function, unicode_literals)

import pandas as pnd
import numpy as np
import exfiles
#from mixmod import *
import mixmod
from mixmod import gm # gm contains global constants (enum items etc.)
data = pnd.read_csv(filepath_or_buffer=exfiles.iris_csv,sep=',',header=False)
vec=data.ix[:,4].astype('category').cat.codes+1
#remaining_obs=np.random.choice(list(range(data.shape[0])),10)
remaining_obs = [17, 101, 149,  33, 120,  73,  58,  25, 147, 148]
#data.drop(remaining_obs)
iris_learn = mixmod.learn(data.drop(remaining_obs).ix[:,0:4], data.drop(remaining_obs).ix[:,4])
prediction = mixmod.predict(data.ix[remaining_obs,:].ix[:,0:4], iris_learn.best_result)
print(prediction)
