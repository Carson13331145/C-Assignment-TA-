#include <iostream>
#include <windows.h>
#include <memory.h>
#include <assert.h>
#include "MyProgram.h"
using namespace std;

static int AI = -1;
static int MAP = 0;
static int YOU = 1;

static int chessTable[10][10] = { 0 };
static int ptable[10][10][192] = { false };
static int ctable[10][10][192] = { false };
static int pgrades[10][10] = { 0 }, cgrades[10][10] = { 0 };
static int win[2][192] = { 0 };  // 0 - YOU | 1 - AI
static int pgrade, cgrade;

static int mat, nat, mde, nde;
static int i, j, k, p, q = -1;
static int count = 0;

static bool computer = false, player = false, start_g = false;
static bool over = false, pwin = false, cwin = false, tie = false;

static MyProgram human;
static int human_x, human_y;
static int AI_x, AI_y;
static int ccount, pcount;

static int human_count = 0, computer_count = 0;

void init();
void display();
void start(int type);
void showGrades();
void showWin();

void check() {
    if (over) {
        if (tie) cout << "\nTie.\n";
        else if (pwin) cout << "\nYou win!\n";
        else if (cwin) cout << "\nYou lose!\n";
    }
}

void preFix() {
    if ((ccount == 50) && (pcount == 50))
        tie = over = true;
    for (i = 0; i < 192; i++) {
        if (ptable[human_x][human_y][i] && win[0][i] != 7)
            win[0][i]++;
        if (ctable[human_x][human_y][i]) {
			ctable[human_x][human_y][i] = false;
            win[1][i] = 7;
        }
    }
    if (!over) {
        for (i = 0; i <= 1; i++)
            for (j = 0; j < 192; j++) {
                if (win[i][j] == 5 && i == 0) {
                    pwin = over = true;
                    cwin = false;
                    break;
                } else if (win[i][j] == 5 && i == 1) {
                    cwin = over = true;
                    pwin = false;
                    break;
                }
                if (over) break;
            }
    }
    check();
}

void countScore() {
    // Count the score for player.
    for (i = 0; i <= 9; i++)
        for (j = 0; j <= 9; j++) {
            pgrades[i][j] = 0;
            if (chessTable[i][j] == 0)
                for (k = 0; k < 192; k++)
                    if (ptable[i][j][k]) {
                        switch (win[0][k]) {
                            case 1:
                            pgrades[i][j] += 5;
                            break;
                            case 2:
                            pgrades[i][j] += 50;
                            break;
                            case 3:
                            pgrades[i][j] += 100;
                            break;
                            case 4:
                            pgrades[i][j] += 400;
                            break;
                        }
                    }
		}
    // Count the score for computer.
    for (i = 0; i <= 9; i++)
        for (j = 0; j <= 9; j++) {
            cgrades[i][j] = 0;
            if (chessTable[i][j] == 0)
                for (k = 0; k < 192; k++)
                    if (ctable[i][j][k]) {
                        switch (win[1][k]) {
                            case 1:
                            cgrades[i][j] += 5;
                            break;
                            case 2:
                            cgrades[i][j] += 50;
                            break;
                            case 3:
                            cgrades[i][j] += 100;
                            break;
                            case 4:
                            cgrades[i][j] += 400;
                            break;
                        }
                    }
        }
}

void AINext() {
    preFix();
    if (start_g) {
        if (q == -1) {
            cout << "Input(0-15):";
            cin >> p;
            assert(p >= 0 && p <= 15);
            AI_x = p / 4 + 3;
            AI_y = p % 4 + 3;
            q = p;
        } else {
            AI_x = q / 4 + 3;
            AI_y = q % 4 + 3;
            while (chessTable[AI_x][AI_y] == 1) {
                q = (q + 1) % 16;
                AI_x = q / 4 + 3;
                AI_y = q % 4 + 3;
            }
            q = -1;
        }
        start_g = false;
    }
    else if (!over) {
        countScore();
        // Decide next step/
        for (i = 0; i < 10; i++)
            for (j = 0; j < 10; j++)
                if (chessTable[i][j] == 0 &&
                    cgrades[i][j] >= cgrade) {
                    cgrade = cgrades[i][j];
                    mat = i;
                    nat = j;
                } else if (chessTable[i][j] == 0 &&
                    pgrades[i][j] >= pgrade) {
                    pgrade = pgrades[i][j];
                    mde = i;
                    nde = j;
                }
        if (pgrade >= cgrade && pgrade > 100) {  // Defend
            AI_x = mde;
            AI_y = nde;
        } else {  // Attack
            AI_x = mat;
            AI_y = nat;
        }
    }
    cgrade = pgrade = 0;
    chessTable[AI_x][AI_y] = AI;
    ccount++;
    if ((ccount == 50) && (pcount == 50))
        tie = over = true;
    for (i = 0; i < 192; i++) {
        if (ctable[AI_x][AI_y][i] && win[1][i] != 7)
            win[1][i]++;
        if (ptable[AI_x][AI_y][i]) {
            ptable[AI_x][AI_y][i] = false;
            win[0][i] = 7;
        }
    }
    if (!over) {
        for (i = 0; i <= 1; i++)
            for (j = 0; j < 192; j++) {
                if (win[i][j] == 5 && i == 0) {  // Player win.
                    pwin = over = true;
                    cwin = false;
                    break;
                } else if (win[i][j] == 5 && i == 1) {  // Computer win.
                    cwin = over = true;
                    pwin = false;
                    break;
                }
                if (over) break;
            }
    }
    check();
}

void setXY(int x, int y, int type) {
    if (type == -1) {
        chessTable[x][y] = AI;
        human.setTable(x, y);
        pcount++;
    } else if (type == 1) {
        chessTable[x][y] = YOU;
        ccount++;
    }
}

void start(int type) {
    init();
    human.reset();
    if (type == 1) {
    	AINext();
    	human.setTable(AI_x, AI_y);
    }
    system("cls");
    display();
    while (!over) {
        human.getNext(human_x, human_y);
        setXY(human_x, human_y, 1);
        AINext();
        setXY(AI_x, AI_y, -1);
        human.setTable(AI_x, AI_y);
        system("cls");
        //showGrades();
        //showWin();
        display();
        check();
        Sleep(1000);
    }
    if (cwin) computer_count++;
    else if (pwin) human_count++;
}

void init() {
    start_g = true;
    computer = player = over = tie = pwin = cwin = false;
    count = pcount = ccount = pgrade = cgrade = 0;
    for (i = 0; i < 2; i++)
        for (j = 0; j < 192; j++)
            win[i][j] = 0;
    for (i = 0; i < 10; i++)
        for (j = 0; j < 10; j++)
            chessTable[i][j] = pgrades[i][j] = cgrades[i][j] = 0;
    for (i = 0; i < 10; i++)
        for (j = 0; j < 6; j++) {
            for (k = 0; k < 5; k++) {
                ptable[j+k][i][count] = true;
                ctable[j+k][i][count] = true;
            }
            count++;
        }
    for (i = 0; i < 10; i++)
        for (j = 0; j < 6; j++) {
            for (k = 0; k < 5; k++) {
                ptable[i][j+k][count] = true;
                ctable[i][j+k][count] = true;
            }
            count++;
        }
    for (i = 0; i < 6; i++)
        for (j = 0; j < 6; j++) {
            for (k = 0; k < 5; k++) {
                ptable[j+k][i+k][count] = true;
                ctable[j+k][i+k][count] = true;
            }
            count++;
        }
    for (i = 0; i < 6; i++)
		for (j = 9; j >= 4; j--) {
            for (k = 0; k < 5; k++) {
                ptable[j-k][i+k][count] = true;
                ctable[j-k][i+k][count] = true;
            }
            count++;
        }
}

void showGrades() {
	cout << "# Player\n";
	for (i = 0; i < 10; i++) {
        for (j = 0; j < 10; j++)
            cout << pgrades[i][j] << " ";
        cout << "\n";
	}
	cout << "\n# Computer\n";
	for (i = 0; i < 10; i++) {
        for (j = 0; j < 10; j++)
            cout << cgrades[i][j] << " ";
        cout << "\n";
	}
	cout << "\n";
}

void showWin() {
    cout << "# Player\n";
    for (i = 0; i < 192; i++)
        cout << win[0][i] << " ";
    cout << "\n";
    cout << "\n# Computer\n";
    for (i = 0; i < 192; i++)
        cout << win[1][i] << " ";
    cout << "\n";
}

void display() {
    cout << "  ";
    for (i = 0; i < 10; i++)
        cout << i << " ";
    cout << "\n";
    for (i = 0; i < 10; i++) {
        cout << i << " ";
        for (j = 0; j < 10; j++)
            switch (chessTable[i][j])
            {
                case -1:
                cout << "@ ";
                break;
                case 0:
                cout << "O ";
                break;
                case 1:
                cout << "# ";
                break;
                default:
                cout << "X ";
            }
        cout << "\n";
    }
}

void nextGame() {
    cout << "Enter 'c' to continue:";
    char in;
    cin >> in;
    //Sleep(5000);
}

void compete() {
    start(1);
    nextGame();
    start(0);
    nextGame();
    start(1);
    nextGame();
    system("cls");
    cout << "AI: " << computer_count << " / You: " << human_count << "\n";
    if (computer_count == human_count) cout << "Tie!\n";
    else if (computer_count > human_count) cout << "You lose!\n";
    else cout << "You win!\n";
}

int main() {
    compete();
    return 0;
}


/* ----- DEMO for MyProgram.h -----

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

*/
