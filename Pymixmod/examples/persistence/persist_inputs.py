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
import pickle

def persist_inputs():
    
    data = pnd.read_csv(filepath_or_buffer='data/iris.train', sep=',')
    data = data.ix[:,0:4] # exclude labels on 5th column
    # save all input arguments as a dictionary
    inputs = dict(data=data, nb_cluster=[2,3,4],
               criterion=[gm.BIC, gm.ICL, gm.NEC],
               models=[gm.Gaussian_p_L_B,
                       gm.Gaussian_p_L_Bk,
                       gm.Gaussian_p_Lk_Ck])
    with open("/tmp/pymixmod_persist_inputs.pkl","wb") as fd:
        pickle.dump(inputs, fd)

def clustering_with_persisted_inputs():

    with open("/tmp/pymixmod_persist_inputs.pkl","rb") as fd:
        inputs = pickle.load(fd)
    # use previously persisted inputs
    # NB: the following call is equivalent to :
    # mixmod.cluster(data=inputs['data'],nb_cluster=inputs['nb_cluster']...)
    res = mixmod.cluster(**inputs)
    return res


if __name__ == '__main__':
    print(
        "-----------------------------------------------------------------------\n"
        "Clustering example : \n"
        "  - iris data (quantitative data)\n"
        "  - several criteria\n"
        "  - several model types\n"
        "-----------------------------------------------------------------------\n\n"
        )
    persist_inputs()
    print(clustering_with_persisted_inputs().summary())   
