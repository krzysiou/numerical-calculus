import numpy as np
import matplotlib.pyplot as plt

#settings

N = 5
b = 5
a = -5
delta_x = abs(b - a) / N

#main

#calculate polynomial
def polynomial(x):
  result = 0
  temp_val = 0
  for i in range(N+1):
    temp_val = values[i][i]
    for j in range(i):
      temp_val *= (x - points[j][0])
    result += temp_val
  return result

#calculate points vector
points = np.zeros((N+1, 2))
temp = a
for i in range(N+1):
  points[i][0] = temp
  temp += delta_x
  points[i][1] = 1/(1+pow(points[i][0],2))

#set primary values matrix
values = np.zeros((N+1,N+1))
for i in range(N+1):
  values[i][0] = points[i][1]

#calculate final values matrix
for i in range(1, N+1):
  for j in range(i, N+1):
    values[j][i] = (values[j][i-1]-values[j-1][i-1])/(points[j][0]-points[j-i][0])

#plot function
result = []
result_argument = []
for i in np.arange(-5,5,0.1):
  result.append(polynomial(i))
  result_argument.append(i)

plt.plot(result_argument, result)
plt.show()