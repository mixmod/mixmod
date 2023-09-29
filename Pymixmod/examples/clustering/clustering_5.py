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

##     All information available on : http://www.mixmod.org
## ################################################################################


import pandas as pd

import mixmod
from mixmod import gm  # gm contains global constants (enum items etc.)


def clustering_5_example():
    folder_data = "data/"
    data = pd.read_csv(folder_data + "iris.train")
    data = data.iloc[:, :4]  # exclude labels on 5th column

    # nb_cluster contains the numbers of clusters to be tested.
    # Here we assume that there are 2, 3 or 4 clusters.

    # --------------------------------------
    # Initialisation example  :
    # - RANDOM
    #   - nb_try = 30 (i.e. "nb-try-in-init")
    # ------------------------------------
    ini = mixmod.init(name=gm.RANDOM, nb_try=30)
    strategy_ = mixmod.strategy(init=ini)
    return mixmod.cluster(data, nb_cluster=[2, 3, 4], strategy=strategy_)


if __name__ == "__main__":
    print(
        "-----------------------------------------------------------------------\n"
        "Clustering example : \n"
        "  - iris data (quantitative data)\n"
        "  - strategy initialisation : RANDOM\n"
        "     - nbTryInInit = 30\n"
        "-----------------------------------------------------------------------\n\n"
    )
    print(clustering_5_example().summary())
