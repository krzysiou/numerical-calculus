#include <iostream>
#include <cmath>

using namespace std;

int main(){
    int size = 6;
    float var;
    float sum;

    float X[6] = {-2, -1, -0.5, 0.1, 0.3, 1.8};
    float C[6] = {1, -0.5, 1, 1.5, -2, -0.5};
    float C_results[6] = {0};
    float Y[6] = {0};
    float Z[6] = {0};
    float L[6][6] = {0};
    float U[6][6] = {0};

    //Gaussian elimination

    //generate A and U teplates
    for(int i = 0; i < size; i++){
      for(int j = 0; j < size; j++){
        U[i][j] = pow(X[i], j);
      }
    }

    //setup L matrix
    for(int i = 0; i < size; i++){
      L[i][i] = 1;
    }

    //calculate Y
    for(int i = 0; i < size; i++){
      for(int j = 0; j < size; j++){
          Y[i] += U[i][j] * C[j];
      }
    }

    //spacer
    cout << "====  Y  ====" << endl << endl;

    //print Y
    for(int i = 0; i < size; i++){
      cout << Y[i] << "  ";
    }
    cout << endl;

    //triangle matrix
    for(int i = 0; i < size; i++){
        for(int j = i + 1; j < size; j++){
            var = U[j][i] / U[i][i];
            L[j][i] = var;
            for(int k = 0; k < size; k++){
                U[j][k] = U[j][k] - var * U[i][k];
            }
        }
    }

    //spacer
    cout << endl << "====  U  ====" << endl << endl;

    //print matrix U
    for(int i = 0; i < size; i++){
      for(int j = 0; j < size; j++){
        cout << U[i][j] << "  ";
      }
      cout << endl;
    }

    //spacer
    cout << endl << "====  L  ====" << endl << endl;

    //print matrix L
    for(int i = 0; i < size; i++){
      for(int j = 0; j < size; j++){
        cout << L[i][j] << "  ";
      }
      cout << endl;
    }

    //calculate Z
    for(int i = 0; i < size; i++){
      Z[i] = Y[i];
      for(int j = 0; j < i; j++){
          Z[i] -= L[i][j] * Y[j];
      }
    }

    //spacer
    cout << endl << "====  Z  ====" << endl << endl;

    //print Y
    for(int i = 0; i < size; i++){
      cout << Y[i] << "  ";
    }
    cout << endl;

    //calculate new C
    for(int i = size - 1; i >= 0; i--) {
        C_results[i] = Z[i];
        for (int j = size - 1; j > i; j--) {
            C_results[i] += U[i][j] * Z[j];
        }
        C_results[i] /= U[i][i];
    }

    //spacer
    cout << endl << "====  C ====" << endl << endl;

    //print C_results
    for(int i = 0; i < size; i++){
      cout << C[i] << "  ";
    }
    cout << endl;

    //spacer
    cout << endl << "====  C_results  ====" << endl << endl;

    //print C_results
    for(int i = 0; i < size; i++){
      cout << C_results[i] << "  ";
    }
    cout << endl;
    return 0;
}