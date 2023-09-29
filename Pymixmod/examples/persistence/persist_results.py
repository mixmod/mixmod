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


def persist_clustering_results():
    folder_data = "data/"
    data = pd.read_csv(folder_data + "iris.train")
    data = data.iloc[:, :4]  # exclude labels on 5th column

    # nb_cluster contains the numbers of clusters to be tested.
    # Here we assume that there are 2, 3 or 4 clusters.

    res = mixmod.cluster(data, nb_cluster=[2, 3, 4])

    with open("/tmp/pymixmod_persist_results.pkl", "wb") as fd:
        pickle.dump(res, fd)
    return res


def get_clustering_persisted_results():
    with open("/tmp/pymixmod_persist_results.pkl", "rb") as fd:
        res = pickle.load(fd)
    return res


if __name__ == "__main__":
    print(
        "-----------------------------------------------------------------------\n"
        "Persistence example (with pickle) : \n"
        "  - iris data (quantitative data)\n"
        "  - default options\n"
        "-----------------------------------------------------------------------\n\n"
    )
    persist_clustering_results()
    print(get_clustering_persisted_results().summary())
