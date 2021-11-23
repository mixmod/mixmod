## ################################################################################
##     copyright            : (C) MIXMOD Team - 2001-2014
##     email                : contact@mixmod.org
## ################################################################################

## ################################################################################
##     This file is part of MIXMOD
    
##     MIXMOD is free software: you can redistribute it and/or modify
##     it under the terms of the GNU General Public License as published by
##     the Free Software Foundation, either version 3 of the License, or
##     (at your option) any later version.

##     MIXMOD is distributed in the hope that it will be useful,
##     but WITHOUT ANY WARRANTY; without even the implied warranty of
##     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
##     GNU General Public License for more details.

##     You should have received a copy of the GNU General Public License
##     along with MIXMOD.  If not, see <http://www.gnu.org/licenses/>.

##     All informations available on : http://www.mixmod.org
## ################################################################################


from __future__ import (absolute_import, division,
                        print_function, unicode_literals)

import numpy as np
import pandas as pnd
import mixmod
from mixmod import gm # gm contains global constants (enum items etc.)

def create_gaussian_parameter(nb_cluster, pb_dimension):
    # proportions
    proportions = np.empty(nb_cluster, dtype=np.float64)
    for k in range(nb_cluster):
        proportions[k] = 1.0/nb_cluster
    # means
    means = np.empty([nb_cluster, pb_dimension], dtype=np.float64)
    for k in range(nb_cluster):
        for p in range(pb_dimension):
            means[k,p] = k + 1
    # variances
    variances = []
    for k in range(nb_cluster):
        mxvar = np.empty([pb_dimension, pb_dimension], dtype=np.float64)
        for p in range(pb_dimension):
            for l in range(pb_dimension):
                mxvar[p,l] = 1.0 if  p == l else 0.0
        variances.append(mxvar)
    return mixmod.GaussianParameter(proportions=proportions,
                                    mean=means,
                                    variance=variances)



data = pnd.read_csv(filepath_or_buffer='data/iris.train', sep=',')
data = data.ix[:,0:4] # exclude labels on 5th column

par = create_gaussian_parameter(3, 4)
ini = mixmod.init(name=gm.PARAMETER, parameter=par)

st = mixmod.strategy(init=ini)

cluster = mixmod.cluster(data, 3, strategy=st)
print(cluster.summary())
