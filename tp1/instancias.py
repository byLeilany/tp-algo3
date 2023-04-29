import numpy as np
import pandas as pd

import matplotlib.pyplot as plt
import random
import os

current_directory = os.getcwd()

print(current_directory)


for power in range(1, 18 ):
    n = 2 ** power
    f = open("inputs/input" + str(n) , "w")
    input = range(0, n)
    f.write(str(n) + " ")
    for num in input:
        start = random.randint(1,2*n - 1)
        f.write(str(start ) + " ")
        f.write(str(random.randint(start + 1 ,2*n)) + " ")
    f.close()