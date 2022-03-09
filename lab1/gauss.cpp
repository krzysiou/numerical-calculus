#include <iostream>
#include <cmath>

using namespace std;

int main(){
    int size = 5;
    float X[5];
    float B[5] = {10, 2, 9, 9, 3};
    float var;
    float sum;
    float deviation;

    //Gaussian elimination
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
    //main algorithm
    for(int i = 0; i < size; i++){
        for(int j = i + 1; j < size; j++){
            var = A[j][i] / A[i][i];
            for(int k = 0; k < size + 1; k++){
                A[j][k] = A[j][k] - var * A[i][k];
            }
        }
    }
    //calculate X vector
    X[size - 1] = A[size - 1][size] / A[size - 1][size - 1];
    for(int i = size - 2; i >= 0; i--){
        X[i] = A[i][size];
        for(int j = i + 1; j < size; j++){
            X[i] = X[i] - A[i][j] * X[j];
        }
        X[i] = X[i] / A[i][i];
    }

    
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            supposed_results[i] += backup_matrix[i][j] * X[j];
        }
    }

    cout << "q = " << q << "    " << "wynik = " << endl;
    for(int i = 0; i < size; i++){
        cout << supposed_results[i] << "    ";
    }
    cout << endl;

    sum = 0;
    for (int i = 0; i < size; i++){
        sum += pow(supposed_results[i] - B[i], 2);
    }
    deviation = sqrt(sum) / size;

    cout << "odchylenie = " << deviation << endl << endl;
    return 0;
}