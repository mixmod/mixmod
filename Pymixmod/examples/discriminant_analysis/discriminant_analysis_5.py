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


def discriminant_analysis_5_example():
    folder_data = "data/"
    raw_data = pd.read_csv(folder_data + "birds_other.train")
    mixmod.header_to_categories(raw_data)
    data = raw_data.iloc[:, :5]  # exclude labels on 6th column
    known_labels = raw_data.iloc[:, 5]
    birds_learn = mixmod.learn(data, known_labels)
    birds_pred = None
    return birds_learn, birds_pred


if __name__ == "__main__":
    print(
        "-----------------------------------------------------------------------\n"
        "Discriminant analysis example : \n"
        "  - birds 'other data (qualitative data)\n"
        "  - default options\n"
        "-----------------------------------------------------------------------\n\n"
    )
    learn_step, prediction_step = discriminant_analysis_5_example()
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

    # print(prediction_step.summary())
