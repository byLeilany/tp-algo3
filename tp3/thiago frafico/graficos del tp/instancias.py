import numpy as np
import pandas as pd

import matplotlib.pyplot as plt
import random
import os
import math

current_directory = os.getcwd()

print(current_directory)


for power in range(2, 13):
    n = 2 ** power
    f = open("/home/dani/Documents/uba/algo3/tp-algo3/tp3/thiago frafico/graficos del tp/input/input" + str(n) , "w")
    
    na = n-1
    #ralo
    hasta = 4*n #math.pow(n, 1.3)
    m = random.randint(1, int(hasta))

    # #denso
    # m = int((n)*(n-1)//2) 
    # m = int(m)

    input = range(0, m )
    k = random.randint(1,min(n * n,300))
    input2 = range(0, k)
    s = random.randint(1,n)
    t = random.randint(s + 1,n)
    f.write(str(n) + " ")
    f.write(str(m) + " ")
    f.write(str(k) + " ")
    f.write(str(s) + " ")
    f.write(str(t) + " ")
    for num in input:
        x = random.randint(1,n)
        f.write(str(x) + " ")
        y = random.randint(1, n)
        f.write(str(y) + " ")
        costo = random.randint(1, 1000)
        f.write(str(costo) + " ")

    for num in input2:
        x = random.randint(1,n)
        f.write(str(x) + " ")
        y = random.randint(1, n)
        f.write(str(y) + " ")
        costo = random.randint(1, 1000)
        f.write(str(costo) + " ")



    f.write("0") 
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