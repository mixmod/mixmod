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

data_folder = "./data/"
data = pd.read_csv(data_folder + "birds.csv", dtype="category")  # qualitative data must be of category dtype

print(data)

cluster = mixmod.cluster(data, 2, gm.QUALITATIVE)

# Barplot with default options
cluster.barplot()

# Customized barplot
cluster.barplot(colors=["yellow", "green"], variables=["gender", "eyebrow", "collar", "sub-caudal"])
