import math
import numpy as np
import matplotlib.pyplot as plt

def fun(x):
  return 1/(1+math.pow(x,2))

def cos2x(x):
  return math.cos(2*x)

# settings

# function
func = fun
# ilosc wezlow
n = 10
# 2 pochodna na lewym krancu przedzialu
alfa = 0
# 2 pochodna na prawym krancu przedzialu
beta = 0
# wektor wezlow
xw = np.zeros(n)
# wektor wartosci funkcji
yw = np.zeros(n)
# lewy kraniec przedzialu
a = -5
# prawy kraniec przedzialu
b = 5
#odleglosc miedzy wezlami
delta_x =  (b-a)/(n-1)


# funtions

def wyzM(xw, yw, n, alfa, beta):
  h = (b-a)/(n-1)
  lamb = 1/2
  my = 1 - lamb

  A = np.zeros((n,n))
  d = np.zeros(n)
  w = np.zeros(n)

  A[0][0] = 1.0
  A[n-1][n-1] = 1.0

  d[0] = alfa
  d[n-1] = beta

  for i in range(1, n-1):
    di = 6/(h+h) * ((yw[i+1]-yw[i])/h - (yw[i]-yw[i-1])/h)
    A[i][i] = 2.0
    A[i][i-1] = my
    A[i][i+1] = lamb
    d[i] = di

  m = np.linalg.solve(A,d)

  return m

def wyzSx(xw, yw, m, n, x):
  h = (b-a)/(n-1)
  for i in range(n):
    if x >= xw[i-1] and x <= xw[i]:
      A = (yw[i]-yw[i-1])/h - h*(m[i]-m[i-1])/6
      B = yw[i-1] - m[i-1] * h * h/6
      sx = m[i-1] * math.pow((xw[i]-x), 3)/(6*h) + m[i]*math.pow((x-xw[i-1]), 3)/(6*h) + A*(x-xw[i-1]) + B
  return sx

# main

# wyznacz wezly i ich wartosci
temp = a
for i in range(n):
  xw[i] = temp
  temp += delta_x
  yw[i] = func(xw[i])

# wyznacz M
m = wyzM(xw, yw, n, alfa, beta)

# wyznacz sx
sx = [wyzSx(xw, yw, m, n, i) for i in xw]

# ideal plot
ideal = []
ideal_argument = []
for i in np.arange(-5,5,0.1):
  ideal.append(func(i))
  ideal_argument.append(i)

plt.plot(ideal_argument, ideal)

# interpolated plot
plt.plot(np.arange(-5,5, 0.01), [wyzSx(xw,yw,m,n,i) for i in np.arange(-5,5, 0.01)])

# points plot
plt.plot([i for i in xw], [i for i in sx], linestyle='', marker="o")

# show plot
plt.show()