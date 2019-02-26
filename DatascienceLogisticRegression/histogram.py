import pandas as pd
from matplotlib import pyplot as plt
import seaborn as sns;
import numpy as np


sns.set(style="ticks", color_codes=True)
iris = pd.read_csv('dataset_train.csv')

iris = iris.dropna()

#sns.distplot(iris[["Hogwarts House", "Care of Magical Creatures"]], hue="Hogwarts House", size=5)

#plt.show()


n_bins = 10
colors = ['red', 'tan', 'lime']


plt.hist([
	iris[iris['Hogwarts House'] == 'Ravenclaw']['Care of Magical Creatures'],
	iris[iris['Hogwarts House'] == 'Slytherin']['Care of Magical Creatures'],
	iris[iris['Hogwarts House'] == 'Gryffindor']['Care of Magical Creatures'],
	iris[iris['Hogwarts House'] == 'Slytherin']['Care of Magical Creatures'],
], n_bins, density=True, histtype='bar')


plt.show()