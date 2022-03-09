#include <iostream>
#include <cmath>

using namespace std;

int main(){
  int cols = 5;
  int rows = 5;
  float X[5];
  float B[5] = {10, 2, 9, 9, 3};
  float var;
  float temp1;
  float temp2;
  float sum;
  float deviation;

  //Jordan elimination

  float q = 0.2;
  float A[5][6] ={
      {2*q*pow(10,-4), 1, 6,  9, 10},
      {2*pow(10, -4),  1, 6,  9, 10},
      {1,              6, 6,  8, 6},
      {5,              9, 10, 7, 10},
      {3,              4, 9,  7, 9,}
  };

  float backup_matrix[5][6] ={
          {2*q*pow(10,-4), 1, 6,  9, 10},
          {2*pow(10, -4),  1, 6,  9, 10},
          {1,              6, 6,  8, 6},
          {5,              9, 10, 7, 10},
          {3,              4, 9,  7, 9,}
      };

  float supposed_results[5] = {0};

  //add right side vector to main matrix
  for(int i = 0; i < 5; i++){
      A[i][5] = B[i];
  }
  for(int i = 0; i < rows; i++){
    temp1 = A[i][i];
    for(int k = 0; k <= rows; k++){
      A[i][k] = A[i][k] / temp1;
    }
    for(int j = 0; j < rows; j++){
      if(i != j){
        temp2 = A[j][i];
        for(int k = 0; k <=rows; k++){
          A[j][k] = A[j][k] - temp2 * A[i][k];
        }
      }
    }
  }
  //calculate X vector
  for(int i = 0; i < rows; i++){
    X[i] = A[i][rows];
  }

  for(int i = 0; i < rows; i++){
          for(int j = 0; j < rows; j++){
              supposed_results[i] += backup_matrix[i][j] * X[j];
          }
      }

  cout << "q = " << q << "    " << "wynik = " << endl;
  for(int i = 0; i < rows; i++){
      cout << supposed_results[i] << "    ";
  }
  cout << endl;

  sum = 0;
  for (int i = 0; i < rows; i++){
      sum += pow(supposed_results[i] - B[i], 2);
  }
  deviation = sqrt(sum) / rows;

  cout << "odchylenie = " << deviation << endl << endl;
  return 0;
}