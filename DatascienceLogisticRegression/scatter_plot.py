import pandas as pd
from matplotlib import pyplot as plt
import seaborn as sns;

sns.set(style="ticks", color_codes=True)
iris = pd.read_csv('dataset_train.csv')

iris = iris.dropna()

g = plt.plot(iris['Astronomy'], iris['Defense Against the Dark Arts'])

plt.show()