import numpy

#option variables
N = 50
L = 5
delta_x = 2 * L / N
offDiagonal = -1 * (1 / (2 * pow(delta_x, 2)))

#-----------

#FUNCTIONS

def generate_matrix_A():
  mtx = numpy.zeros((N, N))
  for i in range(N):
    for j in range(N):
      if (i == j): mtx[i][j] = pow(delta_x, -2) + pow((-L + i * delta_x), 2) / 2
      elif (i + 1 == j or j + 1 == i): mtx[i][j] = offDiagonal
  return mtx

def get_range(mtx):
  return [-(mtx[0][0] + abs(mtx[0][1])), mtx[0][0] + abs(mtx[0][1])]

def bisect(mtx, _a1, _a2, i, n):
    x = (_a1 + _a2)/2
    w = numpy.zeros(N)

    if(n == 0):
        return x

    generate(w, mtx, x);

    if(count(w) > i):
        _a2 = x;
    else:
        _a1 = x;

    x = (_a1 + _a2)/2;

    return bisect(mtx, _a1, _a2, i, n - 1);

def count(w):
  count = 0;
  for i in range(N-1):
      if((w[i] * w[i+1]) < 0):
          count += 1
  return count

def generate(w, mtx, x):
    w[0] = 1;
    w[1] = mtx[0][0] - x;
    for i in range(2, N):
      w[i] = (mtx[i-1][i-1] - x)*w[i-1] - pow(mtx[i][i-1],2)*w[i-2];


def calculate(vec, x, mtx):
    vec[0] = 1;
    vec[1] = (x-mtx[0][0])/mtx[0][1];
    for i in range(2, N-1):
        vec[i] = ((x-mtx[i][i])*vec[i-1]-mtx[i-1][i]*vec[i-2])/mtx[i][i+1];
#-----------

#MAIN

mtx = generate_matrix_A()
b = get_range(mtx)
w_n = 1
w_p = 0


#-----------

values = numpy.zeros(5)

#bisect
for i in range(5):
  values[i] = bisect(mtx, b[0], b[1], i, N);
print(values)

#calculate vector
f = open("results.txt", "w")

vect = numpy.zeros(N)
for i in range(5):
  calculate(vect, values[i], mtx);
  for j in range(50):
    f.write(str(round(vect[j], 4))+"\n")
  f.write("\n\n")

f.close()
#-----------
