#include <iostream>
#include <string.h>
#include "Matrix.h"
using namespace std;

Matrix::Matrix() {
	name = "";
	width = height = 0;
	param = NULL;
	cout << "construct an uninitialised matrix.\n";
}

Matrix::Matrix(string n, int h, int w, int **m) {
	name = n;
	width = w;
	height = h;
	param = new int*[height];
	for (int i = 0; i < height; i++) {
		param[i] = new int[width];
		for (int j = 0; j < width; j++)
			param[i][j] = m[i][j];
	}
	cout << "construct a matrix called " << name << ".\n";
}

Matrix::Matrix(const Matrix &otherMat) {
	name = otherMat.name;
	width = otherMat.width;
	height = otherMat.height;
	param = new int*[height];
	for (int i = 0; i < height; i++) {
		param[i] = new int[width];
		for (int j = 0; j < width; j++)
			param[i][j] = otherMat.param[i][j];
	}
	cout << "copy construct a matrix called " << name << ".\n";
}

Matrix::~Matrix() {
	for (int i = 0; i < height; i++) {
		delete [] param[i];
	}
	delete [] param;
	cout << "release memory from a matrix called " << name << ".\n";
}

void Matrix::setName(string newName) {
	name = newName;
}

void Matrix::print() {
	cout << name << " = [\n";
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			if (j == width-1) cout << param[i][j];
			else cout << param[i][j] << ", ";
		}
		cout << "\n";
	}
	cout << "]\n";
}

