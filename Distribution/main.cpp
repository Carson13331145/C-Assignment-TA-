#include <iostream>
#include <cstring>
#include <string>
#include "distribution.h"
using namespace std;
using namespace RAND_GEN;
using namespace DISTRIBUTION;

void test_adaptor() {
    cout << "---------- test_adaptor ----------\n";
    linear_congruential_engine_my lce;
    adaptor adp(lce);
    cout << "min = " << adp.min() << endl;
    cout << "max = " << adp.max() << endl;
    for (int i = 0; i < 19; i++)
        cout << adp() << ", ";
    cout << adp() << endl;
}

void test_normal_distribution() {
    cout << "---------- test_normal_distribution ----------\n";
    const int nrolls = 10000;  // number of experiments
    const int nstars = 100;  // maximum number of stars to distribute
    linear_congruential_engine_my lce;
    normal_distribution_my dist(5.0, 2.0, lce);
    cout << "min = " << dist.min() << endl;
    cout << "max = " << dist.max() << endl;
    int p[10] = { 0 };
    for (int i = 0; i < nrolls; ++i) {
        double number = dist();
        ++p[static_cast<int>(number)];
    }
    cout << "normal_distribution(5.0 , 2.0):\n";
    for (int i = 0; i < 10; ++i) {
        cout << i << "-" << (i + 1) << ": ";
        cout << string(p[i]*nstars/nrolls, '*') << endl;
    }
}

void hard_test() {
    int nrolls, nstars;
    cin >> nrolls >> nstars;
    linear_congruential_engine_my lce;
    double mean, stddev;
    cin >> mean >> stddev;
    normal_distribution_my dist(mean, stddev, lce);
    int p[10] = { 0 };
    for (int i = 0; i < nrolls; ++i) {
        double number = dist();
        ++p[static_cast<int>(number)];
    }
    for (int i = 0; i < 10; ++i) {
        cout << i << "-" << (i + 1) << ": ";
        cout << string(p[i]*nstars/nrolls, '*') << endl;
    }
}

int main() {
    int t;
    cin >> t;
    if (t == 0) {
        test_adaptor();
        test_normal_distribution();
    } else {
        hard_test();
    }
    return 0;
}

/*
namespace DISTRIBUTION {
struct adaptor {
  private:
      linear_congruential_engine_my my_gen;
  public:
    adaptor();

    adaptor(linear_congruential_engine_my& gen);

    double min() const;

    double max() const;

    double operator()();
};
class normal_distribution_my {
    double mean, stddev;
    adaptor aurng;
  public:
    normal_distribution_my();

    normal_distribution_my(double _mean, double _stddev, 
      linear_congruential_engine_my &gen);

    double getmean() const;

    double getstddev() const;

    void setparam(const double _mean, const double _stddev);

    double min() const;

    double max() const;

    double operator()();
};
}  // namespace DISTRIBUTION
*/
