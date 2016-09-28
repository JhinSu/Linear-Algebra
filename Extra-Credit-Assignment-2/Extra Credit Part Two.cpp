/*
Michael Vu
21 October 2015
MATH-UA-2 Extra Credit Assignment #2

Program inputs a matrix from a file, displays it, and performs Gauss-Jordan eliminaion.
*/

#include "stdafx.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <fstream>
#include <vector>
#include <numeric>

using namespace std;

void printMatrix(vector<vector<double>> a, double x, double y);

int main() {
	//open and read from file
	fstream inputFile;
	inputFile.open("testmatrix.txt");

	//read first line of file
	string matrixParam;
	getline(inputFile, matrixParam);

	//declare and modify matrix parameters
	double m, n, N;
	stringstream ss(matrixParam);
	ss >> m >> n >> N;

	//create matrix
	vector<vector<double>> matrix(m + 1, vector<double>(n + 1));
	vector<double> temp(n + 1);

	//fill matrix
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			matrix[i][j] = 0.00;
		}
	}

	//modify matrix with new values
	while (!inputFile.eof()) {
		getline(inputFile, matrixParam);
		double a, b, c;
		stringstream ss(matrixParam);
		ss >> a >> b >> c;
		matrix[a - 1][b - 1] = c;
	}	

	//display matrix
	cout << "Original Matrix: " << endl;
	printMatrix(matrix, m, n);

	double rowCheck = 0;

	//partial pivot
	int lead = 0;
	for (int i = 1; i < m; i++) 
	{
		for (int j = 0; j < n; j++) 
		{
			if (matrix[lead][lead] == 0) 
			{
				matrix[lead][lead] = matrix[i][j];
				matrix[i][j] = 0;
			}
			/*
			rowCheck += matrix[j][i];
			if (rowCheck == 0)
				lead--;
			else
				rowCheck = 0;
			*/
		}
		lead++;
	}
	
	//display matrix
	cout << "Matrix after pivoting: " << endl;
	printMatrix(matrix, m, n);
	
	//EROS
	lead = 0;
	while (lead < n) {
		for (int i = 0; i < m; i++) {
			double d = matrix[lead][lead];
			double m = matrix[i][lead] / matrix[lead][lead];

			for (int j = 0; j < n; j++) {
				if (i == lead && matrix[lead][lead] != 0)
					matrix[i][j] /= d;
				else if (matrix[lead][lead] != 0)
					matrix[i][j] -= matrix[lead][j] * m;
			}
		}
		lead++;

		//display matrix
		cout << "Matrix after EROs" << endl;
		printMatrix(matrix, m, n);
	}
	
	system("pause>nul");
	return 0;
}

//Prints the Matrix
void printMatrix(vector<vector<double>> matrix, double m, double n) {
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			if (j == 0)
				cout << "|";
			cout << "\t" << setprecision(3) << matrix[i][j];
			if (j == n - 1)
				cout << "\t|";
		}
		cout << endl;
	}
	cout << endl;
}