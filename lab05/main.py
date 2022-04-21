import zipimport
import numpy as np

#SETTINGS
A = [16 + 8j, -20 + 14j, 4 - 8j, -4 + 1j, 1 + 0j]
alfa = pow(10, -10)
IT_MAX = 20
N = 4
z0 = 10 + 10j
z1 = 10.1 + 10.1j

#FUNCTIONS
def calculate_b(z, A):
  b = [0 + 0j, 0 + 0j, 0 + 0j, 0 + 0j, 0 + 0j]
  for i in range (1, 5):
    b[4 - i] = A[5 - i] + z * b[5 - i]
  return b

def calculate_r(A, z):
  return A[0] + z * calculate_b(z, A)[0]

def calculate_z(r_curr, r_prev, z_curr, z_prev):
  return z_curr - (r_curr * (z_curr - z_prev)) / (r_curr - r_prev)

#MAIN
for l in range(1, N + 1):
  z = [0 +0j, 0 +0j, 0 +0j]
  r = [0 +0j, 0 +0j, 0 +0j]
  iterations = 0
  for j in range(IT_MAX):
    iterations = j
    if(j == 0):
      z[0] = z0
      z[1] = z1;
      r[0] = calculate_r(A, z[0])
      r[1] = calculate_r(A, z[1])
    z[2] = calculate_z(r[1], r[0], z[1], z[0])
    r[2] = calculate_r(A, z[2])
    if(abs(z[2] - z[1]) < alfa): break
    z[0] = z[1]
    z[1] = z[2]
    r[0] = r[1]
    r[1] = r[2]
  A = calculate_b(z[1], A)
  print(l, ": re: ", z[1].real, ": im: ", z[1].imag, " iterations : ", iterations)