import csv
import sys

def ft_sqrt(nbr):
	x = nbr
	y = 1
	i = 0
	while (i < 100):
		average = (x + y) / 2
		x = nbr / average
		y = average
		i = i + 1
	return x

def merge(stack, inner_size, size):
	i = 0
	newStack = []
	g = 0
	while (i + 1 < size):
		stackA = stack[i]
		stackB = stack[i + 1]
		ya = 0
		yb = 0
		fusion = []
		while (ya < inner_size or yb < inner_size):
			if (yb >= inner_size):
				fusion.append(stackA[ya])
				ya = ya +1
			elif (ya >= inner_size):
				fusion.append(stackB[yb])
				yb = yb +1
			elif (stackA[ya] <= stackB[yb]):
				fusion.append(stackA[ya])
				ya = ya +1
			elif (stackA[ya] > stackB[yb]):
				fusion.append(stackB[yb])
				yb = yb +1
		g = g + 1
		newStack.append(fusion)
		i = i + 2
	if (1 == g):
		return newStack[0]
	return merge(newStack, inner_size + inner_size, g)

def merge_clean(array, size):
	i=0
	nwlist = []
	while(i < size):
		if (array[i] != False):
			nwlist.append(array[i])
		i = i + 1
	return nwlist

def merge_sort(array, size):
	stack = []
	i = 0
	while (i < size):
		stack.append([array[i]])
		i = i + 1
	limit = size
	limit = limit - 1;
	limit = limit | (limit >> 1)
	limit = limit | (limit >> 2)
	limit = limit | (limit >> 4)
	limit = limit | (limit >> 8)
	limit = limit | (limit >> 16)
	limit = limit + 1
	while (i < limit):
		stack.append([False])
		i = i + 1
	return merge_clean(merge(stack, 1, limit), limit)

def cals_col(col, spamreader):
	i = 0
	y = 0
	numbers = []
	total = 0
	for row in spamreader:
		if (i == 0):
			print(row[col]+" : ", end='')
			i = i + 1
			continue
		if (row[col] == ''):
			continue
		i = i + 1
		numbers.append(float(row[col]))
		total = total + float(row[col])
	numbers = merge_sort(numbers, i - 1)
	size = i - 1;
	#numbers.sort()
	padding = (size / 4) + 0.5
	P25 = round(padding)
	P75 = round(size - padding);

	if ((0 != size % 2)):
		P50Val = numbers[(size // 2)]
	else:
		P50Val = (numbers[round(size / 2)] + numbers[round((size / 2 + 0.5))]) / 2
	
	moy = total / size
	variance = 0
	i = 0
	while(i < size):
		variance = numbers[i] * numbers[i]
		i += 1
	variance = variance / (size - 1)
	std = ft_sqrt(variance)

	results = {
		'min' : numbers[0],
		'max' : numbers[size - 1],
		'std' : std,
		'count' : size,
		'25percent' : numbers[P25],
		'75percent' : numbers[P75],
		'50percent' : P50Val,
	}
	
	print("\t"+str(results['min'])+"\t"+str(results['max'])+"\t"+str(results['std'])+"\t"+str(results['count'])+"\t"+str(results['25percent']
	)+"\t"+str(results['75percent'])+"\t"+str(results['50percent']))
	return 42

def calc_min(col, spamreader):
	smaller = False
	i = 0
	for row in spamreader:
		if (i == 0 or row[col] == ''):
			i = i + 1
			continue
		if (smaller == False):
			smaller = row[col]
		if (float(smaller) > float(row[col])):
			smaller = row[col]
	return smaller


with open(sys.argv[1], newline='') as csvfile:
	spamreader = csv.reader(csvfile, delimiter=',', quotechar='|')
	datas = list(spamreader)

	print("min\tmax\tstd\tcount\t25percent\t75percent\t50percent")
	(cals_col(6, datas)) # Arithmancy
	(cals_col(7, datas)) # Astronomy
	(cals_col(8, datas)) # Herbology
	(cals_col(9, datas)) # Defense Against the Dark
	(cals_col(10, datas)) # Arts
	(cals_col(11, datas)) # Divination
	(cals_col(12, datas)) # Muggle Studies
	(cals_col(13, datas)) # Ancient Runes
	(cals_col(14, datas)) # History of Magic
	(cals_col(15, datas)) # Transfiguration
	(cals_col(16, datas)) # Potions
	(cals_col(17, datas)) # Care of Magical Creatures
	(cals_col(18, datas)) # Charms
	#print(cals_col(19, datas)) # Flying
	#			 									
	#for row in spamreader:
		# print(row[6]) 
	    #print(', "'.join(row)+'"')
