#include <iostream>
#include <cmath>

using namespace std;

int main(){
    //main variables
    int size = 5;

    for(float q = 0.2; q < 5; q += 0.15){
        //reset values
        float var = 0;
        float sum = 0;
        float X[5] = {0};
        float supposed_results[5] = {0};

        //matrix copies

        float backup_B[5] = {10, 2, 9, 9, 3};
        float backup_matrix[5][5] ={
            {2*q*pow(10,-4), 1, 6,  9, 10},
            {2*pow(10, -4),  1, 6,  9, 10},
            {1,              6, 6,  8, 6},
            {5,              9, 10, 7, 10},
            {3,              4, 9,  7, 9,}
        };

        //original matrixes
        float B[5] = {10, 2, 9, 9, 3};
        float A[5][5] ={
            {2*q*pow(10,-4), 1, 6,  9, 10},
            {2*pow(10, -4),  1, 6,  9, 10},
            {1,              6, 6,  8, 6},
            {5,              9, 10, 7, 10},
            {3,              4, 9,  7, 9,}
        };

        //Gaussian elimination

        //triangle matrix
        for (int column = 0; column < size - 1; column++) {
            for (int row = column + 1; row < size; row++) {
                var = A[row][column] / A[column][column];

                for (int columnToSubtract = column; columnToSubtract < size; columnToSubtract++) {
                    A[row][columnToSubtract] -= A[column][columnToSubtract] * var;
                }
                B[row] -= B[column] * var;
            }
        }

        //x vector
        for (int row = size - 1; row >= 0; row--) {
            X[row] = B[row];
            for (int column = size - 1; column > row; column--) {
                X[row] -= A[row][column] * X[column];
            }
            X[row] /= A[row][row];
        }
        
        //calculate results
        for(int i = 0; i < size; i++){
            for(int j = 0; j < size; j++){
                supposed_results[i] += backup_matrix[i][j] * X[j];
            }
        }

        //o(q)
        for (int i = 0; i < size; i++){
            sum += pow(supposed_results[i] - backup_B[i], 2);
        }

        //print
        cout << "q = " << q << "    " << "odchylenie = " <<  sqrt(sum) / size << endl;
    }
    return 0;
}