import numpy as np
import matplotlib.pyplot as plt
import random
import math

from scipy import rand

# settings

m = 50
n = 201

x_min = -4
x_max = 4

x_0 = 2
sigma = (x_max - x_min) / 16

A = np.zeros((m+2, n))
X = np.zeros(n)

# functions

def set_x(X, len):
  X[0] = x_min
  for i in range(1, len):
    X[i] = X[i-1] + abs(x_min - x_max) / (len - 1)

def initialize_matrix(A, len):
  for i in range(len):
    A[0][i] = 0
    A[1][i] = 1

def get_c_rand():
  return (random.uniform(0.0, 1.0) - 0.5) / 5

def fun(x):
  return math.sin((14 * math.pi * x) / (x_max - x_min)) * (math.exp(-1 * (math.pow(x - x_0, 2) / (2 * sigma * sigma))) + math.exp(-1 * (math.pow(x + x_0, 2) / (2 * sigma * sigma))))

def calculate_alpha(j):
  nominator = 0
  for i in range(n):
    nominator = nominator + X[i] * math.pow(A[j - 1][i], 2)
  denominator = 0
  for k in range(n):
    denominator = denominator + math.pow(A[j - 1][k], 2)
  return nominator / denominator

def calculate_beta(j):
  if(j == 1):
    return 0
  nominator = 0
  for i in range(n):
    nominator = nominator + X[i] * A[j - 1][i] * A[j][i]
  denominator = 0
  for k in range(n):
    denominator = denominator + math.pow(A[j - 1][k], 2)
  return nominator / denominator
  
def calculate_polynomials(A, X):
  for i in range(1, m + 1):
    alfa = calculate_alpha(i + 1)
    beta = calculate_beta(i)
    for j in range(n):
      A[i + 1][j] = (X[j] - alfa) * A[i][j] - beta * A[i - 1][j]
      # normalizacja
      if(j == 0):
        normalize = A[i + 1][0]
      A[i + 1][j] = A[i + 1][j] / normalize

def return_value(k):
  sum1 = 0
  for i in range(n):
    sum1 += A[k][i] * (fun(X[i]))
  sum2 = 0
  for i in range(n):
    sum2 += math.pow(A[k][i],2)
  return sum1/sum2

def main_algo(id):
  sum = 0
  for i in range(2, m+2):
    sum += return_value(i)*A[i][id]
  return sum

# main

set_x(X, n)
initialize_matrix(A, n)
calculate_polynomials(A, X)


# ideal plot
ideal = []
ideal_argument = []
for i in np.arange(-4,4,0.01):
  ideal.append(fun(i) + get_c_rand())
  ideal_argument.append(i)
plt.plot(ideal_argument, ideal)

# ideal plot
ideal_org = []
ideal_argument_org = []
for i in np.arange(-4,4,0.01):
  ideal_org.append(fun(i))
  ideal_argument_org.append(i)
plt.plot(ideal_argument_org, ideal_org)

# approx
appr = []
appr_argument = []
for i in range(201):
  appr.append(main_algo(i))
  appr_argument.append(X[i])

# # 7 gram
# plt.plot(X, A[1 + 1])
# plt.plot(X, A[1 + 2])
# plt.plot(X, A[1 + 3])
# plt.plot(X, A[1 + 4])
# plt.plot(X, A[1 + 5])
# plt.plot(X, A[1 + 6])
# plt.plot(X, A[1 + 7])

plt.show()