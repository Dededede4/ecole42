import csv
import sys

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
		#print("-----------")
		#print(stackA)
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
	for row in spamreader:
		if (i == 0):
			i = i + 1
			continue
		if (row[col] == ''):
			continue
		i = i + 1
		numbers.append(float(row[col]))
	numbers = merge_sort(numbers, i - 1)
	#numbers.sort()
	padding = ((i - 2) / 4) + 0.5
	P25 = round(padding)
	P75 = round((i - 2) - padding);

	if ((0 == (i - 2) % 2)):
		P50Val = numbers[((i - 2) % 2)]
	else:
		P50Val = (numbers[round((i - 2) / 2)] + numbers[round(((i - 2) / 2 + 0.5))]) / 2
	results = {
		'min' : numbers[0],
		'max' : numbers[i - 2],
		'len' : i - 2,
		'25percent' : numbers[P25],
		'75percent' : numbers[P75],
		'50percent' : P50Val,
	}
	print(results)
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
	print(cals_col(6, spamreader)) # Arithmancy
	#	Astronomy	Herbology	Defense Against the Dark Arts	Divination	Muggle Studies	Ancient Runes	History of Magic	Transfiguration	Potions	Care of Magical Creatures	Charms	Flying
	#for row in spamreader:
		# print(row[6]) 
	    #print(', "'.join(row)+'"')
