import pandas as pd

import mixmod

data = pd.read_csv("Pymixmod/data/iris.csv")
vec = data["Species"].astype("category").cat.codes + 1

remaining_obs = [17, 101, 149, 33, 120, 73, 58, 25, 147, 148]

iris_learn = mixmod.learn(data.drop(remaining_obs).iloc[:, :4], data.drop(remaining_obs).iloc[:, 4])

prediction = mixmod.predict(data.iloc[remaining_obs, :4], iris_learn.best_result)
print(prediction)
