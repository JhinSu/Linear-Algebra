/*
Michael Vu
21 October 2015
MATH-UA-2 Extra Credit Assignment #1

Program inputs a matrix from a file and displays it.
*/

#include "stdafx.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

void printMatrix(vector<vector<double>> a, double x, double y);

int main()
{
	//open and read from file
	fstream inputFile;
	inputFile.open("testmatrix.txt");

	//read first line of file
	string matrixParam;
	getline(inputFile, matrixParam);

	//declare and modify matrix parameters
	double m, n, N;
	stringstream ss (matrixParam);
	ss >> m >> n >> N;
	
	//create matrix
	vector<vector<double>> matrix(m, vector<double>(n));

	//fill matrix
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			matrix[i][j] = 0.00;
		}
	}
	
	//modify matrix with new values
	while (!inputFile.eof())
	{
		getline(inputFile, matrixParam);
		double a, b, c;
		stringstream ss(matrixParam);
		ss >> a >> b >> c;
		matrix[a -1][b -1] = c;
	}
	
	//display matrix
	printMatrix(matrix, m, n);
	
	system("pause>nul");
	return 0;
}

//Prints the Matrix
void printMatrix(vector<vector<double>> matrix, double m, double n)
{
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			if (j == 0)
				cout << "|";
			cout << "\t" << matrix[i][j];
			if (j == n - 1)
				cout << "\t|";
		}
		cout << endl;
	}
}