import pandas as pd

import mixmod
from mixmod import gm  # gm contains global constants (enum items etc.)


def set_categories(df):
    for k in df.columns:
        if df[k].dtype.name == "int64":
            df[k] = df[k].astype("category")


data = pd.read_csv("Pymixmod/data/heterodata.train")
set_categories(data)
print(data)
print(data.dtypes)

cluster = mixmod.cluster(data, 2, gm.HETEROGENEOUS)
print(cluster)
