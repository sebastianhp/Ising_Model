import numpy as np
import matplotlib.pyplot as plt

with open('energyjawn.txt','r') as f:
    for line in f:
        currentline = line.split(",")
        arr = np.array([float(item) for item in currentline])

plt.plot(arr,'.')
plt.show()
