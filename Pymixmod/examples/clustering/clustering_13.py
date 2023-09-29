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


def clustering_13_example():
    folder_data = "data/"
    data = pd.read_csv(folder_data + "heterodata.csv")
    data["B"] = data["B"].astype("category")
    data["B.1"] = data["B.1"].astype("category")
    # nb_cluster contains the numbers of clusters to be tested.
    # Here we assume that there are 2 clusters.

    return mixmod.cluster(data, nb_cluster=2, models=mixmod.composite_model(gm.ALL))


if __name__ == "__main__":
    print(
        "-----------------------------------------------------------------------\n"
        "Heterogeneous clustering: \n"
        "-----------------------------------------------------------------------\n\n"
    )
    print(clustering_13_example().summary())
