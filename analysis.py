import numpy as np
import sys

#args = [ *.py , rows, numItr]
#args = sys.argv

rows = 5	#args[1]
numItr = 6	#args[2]

#arr = np.array([[]])
arr = np.empty([numItr,rows])

with open('out.txt','r') as f:
	i = 0
	for line in f:
		currentline = line.split(",")
		arr[i] = np.array([int(item) for item in currentline])
		i+=1

print arr
