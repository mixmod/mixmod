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

folder_data = "data/"
data = pd.read_csv(folder_data + "iris.train")
data = data.iloc[:, :4]  # exclude labels on 5th column


labels = [1] * 40 + [2] * 70 + [3] * 40

ini = mixmod.init(name=gm.LABEL, labels=labels)

st = mixmod.strategy(init=ini)

cluster = mixmod.cluster(data, 3, strategy=st)
print(cluster.summary())
