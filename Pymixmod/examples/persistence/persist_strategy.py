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


import pickle

import pandas as pd

import mixmod
from mixmod import gm  # gm contains global constants (enum items etc.)


def persist_strategy():
    # --------------------------------------
    # Strategy example :
    # - nbTry = 5
    # - algo 1 : SEM (nb_iteration = 80)
    # - algo 2 : EM (epsilon=0.0001)
    # Note : default algorithm is EM.
    # ------------------------------------
    algo1 = mixmod.algo(name=gm.SEM, nb_iteration=80)
    algo2 = mixmod.algo(name=gm.EM, epsilon=0.0001)
    strategy_ = mixmod.strategy(nb_try=5, algo=[algo1, algo2])
    with open("/tmp/pymixmod_persist_strategy.pkl", "wb") as fd:
        pickle.dump(strategy_, fd)


def clustering_with_persisted_strategy():
    folder_data = "data/"
    data = pd.read_csv(folder_data + "iris.train")
    data = data.iloc[:, :4]  # exclude labels on 5th column

    # nb_cluster contains the numbers of clusters to be tested.
    # Here we assume that there are 2, 3 or 4 clusters.

    with open("/tmp/pymixmod_persist_strategy.pkl", "rb") as fd:
        strategy_ = pickle.load(fd)
    return mixmod.cluster(data, nb_cluster=[2, 3, 4], strategy=strategy_)


if __name__ == "__main__":
    print(
        "-----------------------------------------------------------------------\n"
        "Clustering example : \n"
        "  - iris data (quantitative data)\n"
        "  - strategy :\n"
        "    - nbTry = 5 \n"
        "    - 2 chained algorithms\n"
        "      - SEM (80 iterations)\n"
        "      - EM (epsilon=0.0001)\n"
        "-----------------------------------------------------------------------\n"
    )
    persist_strategy()
    print(clustering_with_persisted_strategy().summary())
