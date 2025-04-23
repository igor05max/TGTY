import numpy as np


mass = (100 - 1) * np.random.rand(25) + 1

mass = mass.reshape(5, 5)
print(mass)