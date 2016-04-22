#include <iostream>
#include "timer.h"
using std::cin;
using std::cout;
using std::endl;
using std::string;
using namespace TIC_TOC;

// f(n) = 0, n = 1
// f(n) = 1, n = 2
// f(n) = f(n-1) + f(n-2), n > 2
int fabonaci(int n) {
    clock_f();  // it takes 50 clocks (0.050ms)
    if (n == 1) return 0;
    else if (n == 2) return 1;
    else return fabonaci(n-1) + fabonaci(n-2);
}

// f(n) = 1, n = 1
// f(n) = n * f(n-1), n > 1
int factorial(int n) {
    clock_f();
    if (n == 1) return 1;
    return n*factorial(n-1);
}

timer_controller T;  // create a timer_controller
int number[5];  // input for test
int count;  // count the lines(tic -> toc)

void testTicToc(int n, string function) {
    count = 0;
    cin >> number[0] >> number[1] >> number[2]
        >> number[3] >> number[4];
    for (int i = 0; i < 5; i++) {
        T[n].tic_f(count++);  // tic for starting time
        cout << "input: " << number[i] << ", result: ";
        if (function == "fabonaci")
            cout << fabonaci(number[i]) << endl;
        else if (function == "factorial")
            cout << factorial(number[i]) << endl;
        T[n].toc_f(count);  // toc for ending time
    }
    T[n].tictoc(stdout);  // print out the line-time information
}

int main(void) {
    T.create(2);
    testTicToc(0, "fabonaci");
    testTicToc(1, "factorial");
    T.display(stdout);  // print out the total time of each timer
    return 0;
}

// Carson's girlfriend helped him design the frame of time.h,
// But if you are good, you should design a better one!

/* ------- timer.h -------
static int _clock;
inline void clock_f();
inline double getTime();

namespace TIC_TOC {
class timer {
    public:
    timer();
    double getAllRdtsc()
    void tic_f(int);
    void toc_f(int);
    void tictoc(FILE*);
};
class timer_controller {
    timer timePiece[MAX_TIMER];
    public:
    timer_controller();
    void create(int);
    timer& operator[](int&);
    void display(FILE*);
};
}
*/
