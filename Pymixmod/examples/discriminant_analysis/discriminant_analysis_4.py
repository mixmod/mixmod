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


def discriminant_analysis_4_example():

    raw_data = pnd.read_csv(filepath_or_buffer='data/heterodata.train', sep=',')
    data = raw_data.ix[:,1:] # exclude labels on first (index=0) column
    data['B']=data['B'].astype('category')
    data['B.1']=data['B.1'].astype('category')    
    known_labels =  raw_data.ix[:,0]
    models = mixmod.composite_model(gm.ALL)
    hetero_learn = mixmod.learn(data, known_labels, models=models)
    test_data = pnd.read_csv(filepath_or_buffer='data/heterodata.test', sep=',')
    test_data = test_data.ix[:,1:] # exclude labels on first (index=0) column
    test_data['B']=test_data['B'].astype('category')
    test_data['B.1']=test_data['B.1'].astype('category')        
    prediction = mixmod.predict(test_data, hetero_learn.best_result)
    return hetero_learn, prediction


if __name__ == '__main__':
    print(
        "-----------------------------------------------------------------------\n"
        "Heterogeneous discriminant analysis: \n"

        "-----------------------------------------------------------------------\n\n"
        )
    learn_step, prediction_step = discriminant_analysis_4_example()
    print(
        "-----------------------------------------------------------------------\n"
        "Learn step: \n"
        "-----------------------------------------------------------------------\n\n"
        )
    
    print(learn_step.summary())
    print(
        "-----------------------------------------------------------------------\n"
        "Prediction step: \n"
        "-----------------------------------------------------------------------\n\n"
        )
    
    print(prediction_step.summary())
