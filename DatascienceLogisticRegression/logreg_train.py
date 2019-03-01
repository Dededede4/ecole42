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

def log42(x):
	return (math.log(x))

def j(teta, df, house, feature):
	mini = df[feature].min()
	maxi = df[feature].max()
	ratio = maxi - mini;
	result = 0
	l = 0
	for i in df.index:
		l = l + 1
		y = 0
		x = df.at[i, feature]
		x =  ((x - mini) / ratio) * 100
		if df.at[i, 'Hogwarts House'] == house:
			y = 1
		print([df.at[i, feature], x, y, ((0 - y) * log42(h(teta, x)) - (1 - y) * log42((1 - h(teta, x))))])
		result = result + ((0 - y) * log42(h(teta, x)) - (1 - y) * log42((1 - h(teta, x))))
	return result / len(df)

def trainning(df, house, feature):
	teta = 0
	a = 0.00001
	i = 0
	while (i < 1000):
		err =  j(teta, df, house, feature)
		print(err)
		teta = teta - a * err
		i = i + 1
	return {'teta' : teta, 'err' : j(teta, df, house, feature), 'house' : house, 'feature' : feature }

teta = trainning(df, 'Ravenclaw', 'Charms')
for index, row in df.iterrows():
	y = 0
	x = row['Charms']
	if row['Hogwarts House'] == 'Ravenclaw':
		y = 1
	plt.scatter(x, y)

mini = df['Charms'].min()
maxi = df['Charms'].max()
ratio = maxi - mini;

step = ratio / 1000
i = 0



while (i < 1000):
	x = mini + i * step
	x = ((x - mini) / ratio) * 100
	plt.scatter(mini + i * step, h(teta['teta'], x))
	i = i + 1

print(teta['teta'])

plt.show()


exit(0)

quats = ['Arithmancy', 'Astronomy', 'Herbology', 'Defense Against the Dark Arts', 'Divination', 'Muggle Studies', 'Ancient Runes', 'History of Magic', 'Transfiguration', 'Potions', 'Care of Magical Creatures', 'Charms', 'Flying']
for i, quat in enumerate(quats):
	print(trainning(df, 'Ravenclaw', quat))
	print(trainning(df, 'Slytherin', quat))
	print(trainning(df, 'Gryffindor', quat))
	print(trainning(df, 'Hufflepuff', quat))
