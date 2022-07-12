"""
library(Rmixmod)
df <- read.csv('/home/poli/mixmod/Pymixmod/data/heterodata.train')
for (j in 1:3) {
    df[, j] <- as.factor(df[, j])
}
c <- mixmodCluster(df, 2)
c
"""
from __future__ import absolute_import, division, print_function, unicode_literals

import exfiles
import pandas as pnd

import mixmod
from mixmod import gm  # gm contains global constants (enum items etc.)


def set_categories(df):
    for k in df.columns:
        if df[k].dtype.name == 'int64':
            df[k] = df[k].astype('category')


data = pnd.read_csv(filepath_or_buffer=exfiles.heterodata_train, sep=',', header=False)
set_categories(data)
cluster = mixmod.cluster(data, 2, gm.HETEROGENEOUS)
print(cluster)
