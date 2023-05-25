import numpy as np
import pandas as pd

import matplotlib.pyplot as plt
import random
import os

current_directory = os.getcwd()

print(current_directory)


for power in range(2, 13):
    n = 2 ** power
    f = open("input/input" + str(n) , "w")
    input = range(1, n + 1)
    na = n-1
    r = random.randint(1,10000)
    w = random.randint(1,na)
    u = random.randint(1,10)
    v = random.randint(u,10)
    f.write(str(n) + " ")
    f.write(str(r) + " ")
    f.write(str(w) + " ")
    f.write(str(u) + " ")
    f.write(str(v) + " ")
    for num in input:
        x = random.randint(1,1000)
        f.write(str(x) + " ")
        y = random.randint(1, 1000 )
        f.write(str(y) + " ")
    f.close()



  #  2
#3 1 1 1 1
#0 0
#0 1
#1 0
#6 1 3 2 3
#0 0
#0 2
#2 0
#3 2
#2 3
#3 3