#include <iostream>
#include "Matrix.cpp"
using namespace std;

int main() {
	int h, w, n;
	string name, newName;
	cin >> name >> h >> w;
	int **mat1_arr = new int*[h];
	for (int i = 0; i < h; i++) {
		mat1_arr[i] = new int[w];
		for (int j = 0; j < w; j++) {
			cin >> mat1_arr[i][j];
		}
	}
	Matrix mat1(name, h, w, mat1_arr);
	mat1.print();
	Matrix mat2(mat1);
	cin >> newName;
	mat2.setName(newName);
	mat2.print();
	for (int i = 0; i < h; i++) {
		delete [] mat1_arr[i];
	}
	delete []mat1_arr;
	return 0;
}

