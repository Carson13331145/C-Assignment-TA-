#include <iostream>
#include <stdlib.h>
using namespace std;

static int step = 1;

class MyProgram {
  private:
    int myTable[10][10];
  public:
    MyProgram() {
        for (int i = 0; i < 10; i++)
            for (int j = 0; j < 10; j++)
                myTable[i][j] = 0;
    }
    void setTable(int x, int y) {
        myTable[x][y] = -1;
    }
    void reset() {
        for (int i = 0; i < 10; i++)
            for (int j = 0; j < 10; j++)
                myTable[i][j] = 0;
    }
  	void getNext(int &x, int &y) {
		srand(step++);
        int next[2] = { 0 };
        next[0] = rand() % 10;
        next[1] = rand() % 10;
        while (myTable[next[0]][next[1]] != 0) {
            next[0] = rand() % 10;
            next[1] = rand() % 10;
        }
        myTable[next[0]][next[1]] = 1;
        x = next[0];
        y = next[1];
  	}
};
