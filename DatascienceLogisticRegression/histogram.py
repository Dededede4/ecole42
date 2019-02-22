import numpy as np
import matplotlib.pyplot as plt
import csv
import sys

np.random.seed(19680801)

n_bins = 10

x = np.random.randn(10, 4)
print

quats = ['Arithmancy', 'Astronomy', 'Herbology', 'Defense Against the Dark Arts', 'Divination', 'Muggle Studiesk', 'Ancient Runes', 'History of Magic', 'Transfiguration Potions Care of Magical Creatures', 'Charms', 'Flying']
keysHouse = {}
for i, quat in enumerate(quats):
    keysHouse[quat] = []
numbers = {}
numbers['Ravenclaw'] = keysHouse
numbers['Slytherin'] = keysHouse
numbers['Gryffindor'] = keysHouse
numbers['Hufflepuff'] = keysHouse

with open(sys.argv[1], newline='') as csvfile:
    spamreader = csv.reader(csvfile, delimiter=',', quotechar='|')
    i = 0

    for row in spamreader:
        if (i == 0):
            i = i + 1
            continue
        if (row[6] == ''):
            continue
        i = i + 1
        y = 6
        while (y < 17):
            if (row[y] != ''):
                numbers[row[1]][quats[y - 6]].append(float(row[y]))
            y = y + 1

#x = np.array(numbers['Ravenclaw']) + np.array(numbers['Slytherin']) + np.array(numbers['Gryffindor']) + np.array(numbers['Hufflepuff'])
print(numbers)
exit(0)
x = []
y = 0
while y < len(numbers['Slytherin']):
    g = []
    if y < len(numbers['Ravenclaw']):
        g.append(numbers['Ravenclaw'][y])
    if y < len(numbers['Slytherin']):
        g.append(numbers['Slytherin'][y])
    if y < len(numbers['Gryffindor']):
        g.append(numbers['Gryffindor'][y])
    if y < len(numbers['Hufflepuff']):
        g.append(numbers['Hufflepuff'][y])
    x.append(g)
    y = y + 1
x = np.array(x)
print(x)

x_multi = [np.random.randn(n) for n in [1, 2, 3, 4]]

fig, axes = plt.subplots(nrows=2, ncols=7)
axs = axes.flatten()


for i, ax in enumerate(axs):
    ax.hist(x_multi, n_bins, histtype='bar')
    ax.set_title('different sample sizes')

fig.tight_layout()
plt.show()