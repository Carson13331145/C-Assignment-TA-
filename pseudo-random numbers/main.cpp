#include <iostream>
#include "random_my.h"
using namespace std;
using namespace RAND_GEN;

void test_calc() {
    mod_my mod_1(2147483647, 16807, 1);
    if (mod_1.calc(127774) != 13972 ||
        mod_1.calc(1277741) != 156518 ||
        mod_1.calc(12777412) != 1598785 ||
        mod_1.calc(127774123) != 16038262 ||
        mod_1.calc(1277741234) != 160449839)
        cout << "Your calc() is wrong.\n";
    else cout << "Pass all tests for calc().\n";
}

void test_engin() {
    linear_congruential_engine_my lce;
    int count = 1000;
    int num[1001] = {0};
    while (count--) num[lce()%5]++;
    if (num[0] != 216 || num[1] != 190 ||
        num[2] != 203 || num[3] != 216 ||
        num[4] != 175) {
        cout << "Your engin class is wrong in generator.\n";
        return;
    } else if (lce.min() != (lce.increment == 0u ? 1u : 0u)) {
        cout << "Your engin class is wrong in min().\n";
        return;
    } else if (lce.max() != (lce.modulus - 1u)) {
        cout << "Your engin class is wrong in max().\n";
        return;
    }
    else cout << "Pass all tests for class engin.\n";
}

void hard_test() {
    int m, a, c, s, n, num[5];
    cin >> m >> a >> c >> s;
    mod_my mod_1(m, a, c);
    for (int i = 0; i < 5; i++) {
        cin >> n;
        cout << "(MOD CALC) ";
        cout << n << ": " << mod_1.calc(n) << endl;
    }
    linear_congruential_engine_my lce(m, a, c, s);
    lce.discard(10);
    cin >> n;
    while(n--) num[lce()%5]++;
    for (int i = 0; i < 5; i++) {
        cout << "(ENGIN) ";
        cout << i << ": " << num[i] << endl;
    }
}

int main() {
    int t;
    cin >> t;
    if (t == 0) {
        test_calc();
        test_engin();
    } else hard_test();
    return 0;
}

/*

Carson's good friend Hannibal helps him design the frame of this
two classes. If you are good, you should design them by your own.

namespace RAND_GEN {
class mod_my {
  public:
    int m, a, c;
    mod_my(int, int, int);
    int calc(int);
};

class linear_congruential_engine_my {
public:
    int multiplier, increment, modulus;
    unsigned int default_seed_my, seed_my;
    mod_my mod_temp;

    linear_congruential_engine_my();

    linear_congruential_engine_my(int _m, int _a, int _c, int _s);

    void seed(unsigned int);

    int min();
    int max();

    void discard(unsigned long long);

    int operator()();
};
}  // namespace RAND_GEN

#endif
*/
