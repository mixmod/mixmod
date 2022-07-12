"""
library(Rmixmod)
df <- read.csv('/home/poli/mixmod/Pymixmod/data/iris.csv')
learn.iris <- mixmodLearn(df[1:4], df$Species)
## get summary
summary(learn.iris)
"""
from __future__ import absolute_import, division, print_function, unicode_literals

# import numpy as np
import exfiles
import pandas as pnd

# from mixmod import *
import mixmod
from mixmod import gm  # gm contains global constants (enum items etc.)

data = pnd.read_csv(filepath_or_buffer=exfiles.iris_csv, sep=',', header=False)
# vec = data.ix[:, 4].astype('category').cat.codes+1
iris_learn = mixmod.learn(data.ix[:, 0:4], data.ix[:, 4])

print(iris_learn)
