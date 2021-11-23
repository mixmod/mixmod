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

import pandas as pnd
import mixmod
from mixmod import gm # gm contains global constants (enum items etc.)
data = pnd.read_csv(filepath_or_buffer='../clustering/data/iris.train', sep=',')
data = data.ix[:,0:4] # exclude labels on 5th column
cluster = mixmod.cluster(data,[2,3,4], gm.QUANTITATIVE)
print(cluster.summary())
cluster.plot(y=data.columns)
cluster.hist(variables=data.columns)
