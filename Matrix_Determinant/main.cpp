#include <iostream>
using namespace std;

int n, **matrix;

int det(int **m, int size) {
    if (size == 2) return m[0][0]*m[1][1]-m[0][1]*m[1][0];
    int temp = 0;
    for (int i = 0; i < size; i++) {
        int **m0 = new int*[size-1];
        for (int v = 0; v < size-1; v++)
            m0[v] = new int[size-1];
        for (int p = 0; p < size-1; p++) {
            for (int q = 0; q < size-1; q++)
                if (q < i) m0[p][q] = m[p+1][q];
                else m0[p][q] = m[p+1][q+1];
        }
        // positive for even position and negative for odd position.
        if (i%2 == 0) temp += m[0][i]*det(m0, size-1);
        else if (i%2 == 1) temp -= m[0][i]*det(m0, size-1);
        // delete the int** we new before.
        for (int v = 0; v < size-1; v++) delete [] m0[v];
        delete [] m0;
    }
    return temp;
}

int main() {
    cin >> n;  // Matrix n * n ( n >= 2)
    matrix = new int*[n];
    for (int i = 0; i < n; i++) matrix[i] = new int[n];
    for (int i = 0; i < n*n; i++) cin >> matrix[i/n][i%n];
    cout << det(matrix, n) << endl;
    for (int i = 0; i < n; i++) delete [] matrix[i];
    delete [] matrix;
    return 0;
}

