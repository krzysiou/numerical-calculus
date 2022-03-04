#include <iostream>
#include <cmath>

using namespace std;

int main(){
  int cols = 5;
  int rows = 5;
  double X[5];
  double B[5] = {10, 2, 9, 9, 3};
  double var;
  double temp1;
  double temp2;

  //Jordan elimination

  for(double q = 0.2; q < 5; q += 0.15){
    double A[5][6] ={
        {2*q*pow(10,-4), 1, 6,  9, 10},
        {2*pow(10, -4),  1, 6,  9, 10},
        {1,              6, 6,  8, 6},
        {5,              9, 10, 7, 10},
        {3,              4, 9,  7, 9,}
    };
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
    //print results
    cout << "q = " << q << endl;
    for(int i = 0; i < rows; i++){
      cout << X[i] << "   ";
    }
    cout << endl;
    cout << "##############" << endl; 
  }
  return 0;
}