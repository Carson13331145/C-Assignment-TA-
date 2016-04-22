#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <string.h>
using namespace std;

class Matrix {
	public:
		Matrix();
		Matrix(string, int, int, int**);
		Matrix(const Matrix &);
		~Matrix();
		void setName(string);
		void print();
	private:
		string name;
		int width, height, **param;
};

#endif

