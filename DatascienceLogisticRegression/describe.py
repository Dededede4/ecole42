import csv
import sys

with open(sys.argv[1], newline='') as csvfile:
	spamreader = csv.reader(csvfile, delimiter=',', quotechar='|')
	for row in spamreader:
	    print(', '.join(row))
