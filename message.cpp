/*
zajuszm@agh.edu.pl
plik z labow: 01a_nazwisko_nazwa.cpp
plik poprawiony z domu : 01b_nazwisko_nazwa.cpp

Sprawozdanie:
    1. Wstep  1 - 1,5 strony
    2. Opis problemu
    3. Wyniki + komentarze
    4. Podsumowanie

*/

#include <iostream>
#include <stdio.h>
#include <iomanip>
#include <fstream>
#include "/usr/include/gsl/gsl_math.h"
#include "/usr/include/gsl/gsl_linalg.h"

using namespace std;

void printMatrix(gsl_matrix *A, unsigned int size) {
    cout << "Macierz: " << endl;
    for(unsigned int i = 0; i < size; i++) {
        for(unsigned int j = 0; j< size; j++) {
            double v = gsl_matrix_get(A, i, j);
            cout << setw(15) << v << " ";
        }
        cout << endl;
    }
    cout << endl << endl;
}

int main()
{
    int n = 4;

    gsl_matrix *A = gsl_matrix_calloc(n, n);
    gsl_permutation *p = gsl_permutation_calloc(n);

    ofstream file("file.txt");

    ///Wpisanie wartosci do macierzy
    ///Wypisanie macierzy
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            double num = 1.0/(i + j + 2);
            gsl_matrix_set(A, i, j, num);
        }
    }
	printMatrix(A, 4);
	
	///Stworzenie kopii macierzy pierwotnej
    gsl_matrix *A_kopia = gsl_matrix_calloc(n, n);
	for(int i = 0; i < n; i++)
	{
		for(int j = 0; j < n; j++)
		{
			gsl_matrix_set(A_kopia, i, j, gsl_matrix_get(A, i, j));
		}
	}
	
	
	///Podpunkt 1
    int signum;
    int rozklad_macierzy_LU = gsl_linalg_LU_decomp(A, p, &signum);
	cout << "Rozkład LU\n";
	printMatrix(A, 4);

	///Podpunkt 2
	///Znalezienie wyznacznika i zapisanie diagonali do pliku
    double wyznacznik_A = 1;
    file << "Elementy diagonalne: \n";
    for(int i = 0; i < 4; i++)
    {
        wyznacznik_A *= gsl_matrix_get(A, i, i);
        file << gsl_matrix_get(A, i, i) << "\n";
    }

    cout << "Wyznacznik macierzy A = " << wyznacznik_A << endl;
	file << "\nWyznacznik macierzy A = " << wyznacznik_A << endl;

	///Podpunkt 3
    ///Znalezienie macierzy odwrotnej
    gsl_matrix *B = gsl_matrix_calloc(n, n);
	gsl_vector *b = gsl_vector_calloc(n);
	gsl_vector *x = gsl_vector_calloc(n);
	for(int i = 0; i < n; i++)
	{
		for(int j = 0; j < n; j++)
		{
			double val = 0.0;
			if(i == j)
				val = 1.0;
			gsl_vector_set(b, j, val);
		}
		gsl_linalg_LU_solve(A, p, b, x);
		for(int j = 0; j < n; j++)
		{
			gsl_matrix_set(B, j, i, gsl_vector_get(x, j));
		}
	}

	cout << "Macierz odwrotna\n";
	printMatrix(B, n);
	file << "\nMacierz odwrotna: \n";
	for(int i = 0; i < n; i++)
	{
		for(int j = 0; j < n; j++)
		{
			file << setw(7) << gsl_matrix_get(B, i, j) << " ";
		}
		file << "\n";
	}
	
	///Podpunkt 4
	///Mnozenie macierzy
	gsl_matrix *C = gsl_matrix_calloc(n, n);
	for(int i = 0; i < n; i++)
	{
		for(int j = 0; j < n; j++)
		{
			double sum = 0.0;
			gsl_matrix_set(C, i, j, 0.0);
			for(int k = 0; k < n; k++)
			{
				sum += gsl_matrix_get(A_kopia, i, k) * gsl_matrix_get(B, k, j);
			}
			gsl_matrix_set(C, i, j, sum);
		}
	}

	printMatrix(C, n);
	file << "\nIloczyn macierzy: \n";
	for(int i = 0; i < n; i++)
	{
		for(int j = 0; j < n; j++)
		{
			file << setw(13) << gsl_matrix_get(C, i, j) << " ";
		}
		file << "\n";
	}
	
	///Podpunkt 5
	///Znalezienie wartosci maksymalnej
	double maxValueA = abs(gsl_matrix_get(A_kopia, 0, 0));
	for(int i = 0; i < n; i++)
	{
		for(int j = 0; j < n; j++)
		{
			if(abs(gsl_matrix_get(A_kopia, i, j)) > maxValueA)
				maxValueA = abs(gsl_matrix_get(A_kopia, i, j));
		}
	}
	
	double maxValueB = abs(gsl_matrix_get(B, 0, 0));
	for(int i = 0; i < n; i++)
	{
		for(int j = 0; j < n; j++)
		{
			if(abs(gsl_matrix_get(B, i, j)) > maxValueB)
				maxValueB = abs(gsl_matrix_get(B, i, j));
		}
	}

	cout << "Max A: " << maxValueA << "\n";
	cout << "Max B: " << maxValueB << "\n";
	double cond = maxValueA * maxValueB;
	cout << "Wskaznik uwarunkowania macierzy = " << cond << "\n";
	file << "\nWskaznik uwarunkowania macierzy = " << cond << "\n";

    gsl_matrix_free(A);
    gsl_matrix_free(A_kopia);
    gsl_matrix_free(B);
    gsl_matrix_free(C);
    gsl_permutation_free(p);
    gsl_vector_free(b);
    gsl_vector_free(x);
	file.close();
    return 0;
}
