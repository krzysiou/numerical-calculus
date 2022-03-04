#include <iostream>
#include <cmath>

using namespace std;

int main(){
  int cols = 5;
  int rows = 5;
  double X[5];
  double B[5] = {10, 2, 9, 9, 3};

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
    //main algorithm


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