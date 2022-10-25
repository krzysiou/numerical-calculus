import math
from re import I
from runpy import _ModifiedArgv0
import numpy as np
import matplotlib.pyplot as plt

# Constants

y0 = 1
lamb = -1
tMin = 0
tMax = 5

tSteps = [0.01, 0.1, 1]

# Functions

def solution(x):
  return math.exp(lamb * x)

def euler(yN, dT, tN):
  return yN + dT * lamb * yN

def rk2(yN, dT, tN):
  k1 = lamb * yN;
  k2 = lamb * (yN + dT * k1)
  return yN + (dT / 2) * (k1 + k2)

def rk4(yN, dT, tN):
  k1 = lamb * yN;
  k2 = lamb * (yN + (dT / 2) * k1)
  k3 = lamb * (yN + (dT / 2) * k2)
  k4 = lamb * (yN + dT * k3)
  return yN + (dT / 6) * (k1 + 2 * k2 + 2 * k3 + k4)



def frame(func):
  plt.figure(0)
  plt.figure(1)

  # numeric with error
  
  for step in tSteps:
    x = [0]
    y = [y0]
    yIdeal = [y0 - solution(0)]
    i = 0

    for t in np.arange(step, 5 + step, step):
      x.append(t)
      y.append(func(y[i], step, t))
      yIdeal.append(func(y[i], step, t) - solution(t))
      i += 1

    plt.figure(0)
    plt.plot(x, y, label='step ' + str(step))

    plt.figure(1)
    plt.plot(x, yIdeal, label='error step ' + str(step))

  # analitic

  x = [x for x in np.arange(0, 5, 0.01)]
  y = []

  for xVal in x:
    y.append(solution(xVal));

  plt.figure(0)
  plt.plot(x, y, label='analitic')

  plt.figure(0)
  plt.legend()

  plt.figure(1)
  plt.legend()

  plt.show()

# Main

# 1 

frame(euler)

# 2

frame(rk2)

# 3

frame(rk4)

# 4

l = 0.1
r = 100
c = 0.001
omega0 = 1 / (math.sqrt(l * c))
t0 = (2 * math.pi) / omega0
tMin = 0
tMax = 4 * t0
step = math.pow(10, -4)
omegaV = [0.5 * omega0, 0.8 * omega0, omega0, 1.2 * omega0]

def v(omega, t):
  return 10 * math.sin(omega * t)

def f(t, q, i):
  return i

def g(t, q, i, omega):
  return (v(omega, t) / l) - (r / l) * i - (q / (l * c))

def calculate(qArr, iArr, t, q, i, omega):
  k1q = f(t, q, i)
  k1i = g(t, q, i, omega)
  k2q = f(t + 0.5 * step, q + (step / 2) * k1q, i + (step / 2) * k1i)
  k2i = g(t + 0.5 * step, q + (step / 2) * k1q, i + (step / 2) * k1i, omega)
  k3q = f(t + 0.5 * step, q + (step / 2) * k2q, i + (step / 2) * k2i)
  k3i = g(t + 0.5 * step, q + (step / 2) * k2q, i + (step / 2) * k2i, omega)
  k4q = f(t + step, q + step * k3q, i + step * k3i)
  k4i = g(t + step, q + step * k3q, i + step * k3i, omega)

  qArr.append(q + (step / 6) * (k1q + 2 * k2q + 2 * k3q + k4q))
  iArr.append(i + (step / 6) * (k1i + 2 * k2i + 2 * k3i + k4i))

for omega in omegaV:
  x = [0]
  q = [0]
  i = [0]
  index = 0

  for t in np.arange(step, tMax + step, step):
    x.append(t)
    calculate(q, i, t, q[index], i[index], omega)
    index += 1
  
  plt.plot(x, q, label='omega ' + str(omega))

plt.legend() 
plt.show()