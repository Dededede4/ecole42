import pandas as pd
from matplotlib import pyplot as plt
import math;
#sns.set(style="ticks", color_codes=True)
df = pd.read_csv('dataset_train.csv')

df = df.dropna()

# Retourne la probabilté entre 0 et un que ce soit une maison
def g(z):
  return 1 / (1 + math.exp(0 - z))

def h(teta, x):
	return g(teta * x)

def j(teta, df, house, feature):
	result = 0
	for index, row in df.iterrows():
		y = 0
		x = row[feature]
		if row['Hogwarts House'] == house:
			y = 1
		result += ((0 - y) * math.log(h(teta, x)) - (1 - y) * math.log((1 - h(teta, x))))
	return 1 / len(df) * result

def trainning(df, house, feature):
	teta = 0
	a = 0.0000001
	i = 0
	while (i < 1000):
		teta = teta - a * j(teta, df, house, feature)
		i = i + 1
	return {'teta' : teta, 'err' : j(teta, df, house, feature), 'house' : house, 'feature' : feature }

quats = ['Arithmancy', 'Astronomy', 'Herbology', 'Defense Against the Dark Arts', 'Divination', 'Muggle Studiesk', 'Ancient Runes', 'History of Magic', 'Transfiguration Potions Care of Magical Creatures', 'Charms', 'Flying']
for i, quat in enumerate(quats):
	print(trainning(df, 'Ravenclaw', quat))
	print(trainning(df, 'Slytherin', quat))
	print(trainning(df, 'Gryffindor', quat))
	print(trainning(df, 'Hufflepuff', quat))





