import pandas as pd

import mixmod
from mixmod.data import load_iris

folder_data = "data/"
data = pd.read_csv(folder_data + "iris.csv")

iris_learn = mixmod.learn(data.iloc[:, :4], data.iloc[:, 4])

print(iris_learn)
