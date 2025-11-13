import numpy as np

a = np.matrix([[120, 150, 180],
			   [100, 160, 220],
			   [80, 140, 210]])

b = np.matrix([[0.6, 0.3, 0.1],
				[0.4, 0.4, 0.2],
				[0.3, 0.5, 0.2]])

x = a * b
z = b * a

print(f"x: {x}")
print(f"z: {z}")

price = np.matrix([[0.5],
				   [0.8],
				   [1.2]])

y = x * price

print(y)
