import numpy as np
import pandas as pd

import matplotlib.pyplot as plt
import random
import os

current_directory = os.getcwd()

print(current_directory)


for power in range(1, 20 ):
    n = 2 ** power
    f = open("/home/thiago/Desktop/prueba/inputsord/inputord" + str(n) , "w")
    input = range(0, n)
    f.write(str(n) + " ")
    for num in input:
  
        f.write(str(num+1 ) + " ")
        f.write(str(num + 2 ) + " ")
    f.close()