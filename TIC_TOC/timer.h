#ifndef TIMER_H
#define TIMER_H
 
#include <stdio.h>
#include <memory.h>
 
#define MAX_LINE 10000
#define MAX_TIMER 5
#define _CLOCKS_PER_SEC 1000
 
static int _clock = 0;
 
inline void clock_f() { _clock += 50; }
inline double getTime() { return 1.0 * _clock / _CLOCKS_PER_SEC; }
 
namespace TIC_TOC {
class timer {
    double _timer[MAX_LINE];  // time for each line
    int _fromLine[MAX_LINE];  // line starting point
    int _lastLineNum;  // mark the ending line
    double _lastRdtsc;  // last time using getime()
    double _totalRdtsc;  // time for all lines
    public:
        timer() {
            memset(_timer, 0, sizeof(_timer));
            memset(_fromLine, 0, sizeof(_fromLine));
            _lastLineNum = -1;
            _lastRdtsc = _totalRdtsc = 0;
        }
        double getAllRdtsc() { return _totalRdtsc; }
        void tic_f(int line) {
            _lastLineNum = line;
            _lastRdtsc = getTime();
        }
        void toc_f(int line) {
            double t = getTime();
            _fromLine[line] = _lastLineNum;
            _timer[line] += t - _lastRdtsc;
            _totalRdtsc += _timer[line];
            _lastLineNum = line;
            _lastRdtsc = t;
        }
        void tictoc(FILE *out) {
            for (int i = 0; i < MAX_LINE; i++)
                if (_timer[i] != 0)
                    fprintf(out, "line %d - %d: %.3fms\n",
                        _fromLine[i], i, _timer[i]);
            fflush(out);
        }
};
class timer_controller {
    int count;  // count timers
    timer timePiece[MAX_TIMER];  // 5 timers at most for each timer_controller
    public:
        timer_controller() { count = 0; }
        void create(int input) { count = input; }
        timer& operator[](const int& input) { return timePiece[input]; }
        void display(FILE *out) {
            for (int i = 0; i < count; i++)
                fprintf(out, "#Timer_%d: %.3fms\n",
                    i+1, timePiece[i].getAllRdtsc());
            fflush(out);
        }
};
}  // namespace TIC_TOC
 
#endif

