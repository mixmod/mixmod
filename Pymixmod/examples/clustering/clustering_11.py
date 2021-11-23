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

        
        
def clustering_11_example():

    data = pnd.read_csv(filepath_or_buffer='data/birds.dat', sep=',')
    mixmod.header_to_categories(data)
    # nb_cluster contains the numbers of clusters to be tested.
    # Here we assume that there are 3 clusters.
    models_ = [gm.Binary_p_E,
               gm.Binary_p_Ek,
               gm.Binary_p_Ej,
               gm.Binary_p_Ekj,
               gm.Binary_p_Ekjh,
               # proportion free  
               gm.Binary_pk_E,
               gm.Binary_pk_Ek,
               gm.Binary_pk_Ej,
               gm.Binary_pk_Ekj,
               gm.Binary_pk_Ekjh]
    return mixmod.cluster(data, nb_cluster=3, models=models_)




if __name__ == '__main__':
    print(
        "-----------------------------------------------------------------------\n"
        "Clustering example (number 2) : \n"
        "  - birds data (qualitative data)\n"
        "  - default options\n"
        "-----------------------------------------------------------------------\n\n"
        )
    print(clustering_11_example().summary())
