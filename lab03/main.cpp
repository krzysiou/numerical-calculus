#include <iostream>
#include <fstream>
#include <math.h>

//macro
#define max(X,Y) ((X)>(Y)? (X):(Y))
#define min(X,Y) ((X)<(Y)? (X):(Y))
#define abs(X) ((X)>0? (X):-(X))

#define M 5
#define N 1000

using namespace std;

int main(){
  //open file
  ofstream myfile;
  myfile.open ("results.txt");
  //generate array
  double A[N][N];
  for(int i = 0; i < N; i++){
    for(int j = 0; j < N; j++){
      if(fabs(i - j) <= M) {
        A[i][j] = (double)1 / (double)(1 + fabs(i - j));
      } else {
        A[i][j] = 0;
      }
    }
  }

  //generate right side vector
  double B[N];
  for(int i = 0; i < N; i++){
    B[i] = i;
  }

  //set initial result vector
  double X[N] = {0};

  //set R vector
  double R[N];

  //algorithm
  double Y[N];
  double middleware[N];
  double sum[N];
  double jmin, jmax, len, X_sum, alpha, bottom, counter = 0;

  do {
    //calculate AX and store in Y
    for(int i = 0; i < N; i++){
      jmin=max(0,i - M);
      jmax=min(i + M, N - 1);
      Y[i] = 0;
      for(int j = jmin; j <= jmax; j++) Y[i] += A[i][j] * X[j];
    }

    //calculate R
    for(int i = 0; i < N; i++){
      R[i] = B[i] - Y[i];
    }

    //calculate R sum of squares
    len = 0;
    for(int i = 0; i < N; i++){
      len += pow(R[i], 2);
    }
    //calculate AR
    for(int i = 0; i < N; i++){
      jmin=max(0,i - M);
      jmax=min(i + M, N - 1);
      middleware[i] = 0;
      for(int j = jmin; j <= jmax; j++) middleware[i] += A[i][j] * R[j];
    }

    //calculate bottom
    bottom = 0;
    for(int i = 0; i < N; i++){
      bottom += R[i] * middleware[i];
    }

    //calculate alpha
    alpha = len / bottom;

    //calculate alpha * R
    for(int i = 0; i < N; i++){
      sum[i] = R[i] * alpha;
    }

    //calculate X sum of squares
    X_sum = 0;
    for(int i = 0; i < N; i++){
      X_sum += pow(X[i], 2);
    }

    //calculate new X
    for(int i = 0; i < N; i++){
      X[i] = X[i] + sum[i];
    }

    myfile << counter << "   norm R : " << sqrt(len) << " alpha : " << alpha << " norm X : " << sqrt(X_sum) << endl;
    counter++;
  } while(sqrt(len) > pow(10, -6));

  //close file
  myfile.close();
  return 0;
}