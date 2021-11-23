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



def clustering_7_example():
    data = pnd.read_csv(filepath_or_buffer='data/iris.train', sep=',')
    data = data.ix[:,0:4] # exclude labels on 5th column

    # nb_cluster contains the numbers of clusters to be tested.
    # Here we assume that there are 2, 3 or 4 clusters.

    #--------------------------------------
    # Initialisation example  :
    # - SEM_MAX
    #   - nb_iteration = 100;
    #------------------------------------    
    ini = mixmod.init(name=gm.SEM_MAX, nb_iteration=100)
    strategy_ = mixmod.strategy(init=ini)
    return mixmod.cluster(data, nb_cluster=[2,3,4], strategy=strategy_)


if __name__ == '__main__':
    print(
        "-----------------------------------------------------------------------\n"
        "Clustering example : \n"
        "  - iris data (quantitative data)\n"
        "  - strategy initialisation : SEM_MAX\n"
        "     - nbIterationInInit = 100\n"
        "-----------------------------------------------------------------------\n\n"
        )
    print(clustering_7_example().summary())
