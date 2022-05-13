import numpy as np
import matplotlib.pyplot as plt
import math

# settings

h = 0.1
r = [-0.75, 1.75]
delta = math.pow(10, -4)
epsilon = math.pow(10, -2)
max_iterations = 1000

# functions

def fun(x, y):
  return (5 / 2) * math.pow((math.pow(x, 2) - y), 2) + math.pow((1 - x), 2)

def get_next_r(r):
  x = r[0] - h * ((fun(r[0] + delta, r[1]) - fun(r[0] - delta, r[1])) / (2 * delta))
  y = r[1] - h * ((fun(r[0], r[1] + delta) - fun(r[0], r[1] - delta)) / (2 * delta))
  return [x, y]

def minimize(r):
  previous = get_next_r(r)
  for i in range(max_iterations):
    next = get_next_r(previous)
    if(np.linalg.norm(np.subtract(next, previous)) < epsilon):
      return next, i
    previous = next
  return next, max_iterations
# main
result = minimize(r)
print(result[0], result[1])