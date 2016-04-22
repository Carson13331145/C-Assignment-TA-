#ifndef DISTRIBUTION_H
#define DISTRIBUTION_H
#include <limits>
#include <cmath>
#include <algorithm>
#include <cstddef>
#include "random_my.h"
using namespace RAND_GEN;

namespace DISTRIBUTION {

struct adaptor {
  private:
      linear_congruential_engine_my my_gen;
  public:
    adaptor() { }

    explicit adaptor(const linear_congruential_engine_my& gen)
    : my_gen(gen) { }

    double min() const
    { return static_cast<double>(0); }

    double max() const
    { return static_cast<double>(1); }

    double operator()() {
        const size_t b =
        static_cast<size_t>(std::numeric_limits<double>::digits);
        const long double r = static_cast<long double>(my_gen.max())
            - static_cast<long double>(my_gen.min()) + 1.0L;
        const size_t log2r = std::log(r) / std::log(2.0L);
        size_t k = std::max<size_t>(1UL, (b + log2r - 1UL) / log2r);
        double sum = static_cast<double>(0);
        double tmp = static_cast<double>(1);
        for (; k != 0; --k) {
            sum += static_cast<double>(my_gen() - my_gen.min()) * tmp;
            tmp *= r;
        }
        return sum / tmp;
    }
};

class normal_distribution_my {
    double mean, stddev;
    adaptor aurng;
  public:
    normal_distribution_my() : mean(0), stddev(1)
    { }

    normal_distribution_my(double _mean, double _stddev,
      linear_congruential_engine_my &gen)
      : mean(_mean), stddev(_stddev), aurng(gen)
    { }

    double getmean() const
    { return mean; }

    double getstddev() const
    { return stddev; }

    void setparam(const double _mean, const double _stddev) {
        mean = _mean;
        stddev = _stddev;
    }

    double min() const
    { return std::numeric_limits<double>::min(); }

    double max() const
    { return std::numeric_limits<double>::max(); }

    double operator()() {
        double ret, x, y, r2;
        do {  // r2 = (0, 1];
            x = static_cast<double>(2) * aurng() -1.0;
            y = static_cast<double>(2) * aurng() -1.0;
            r2 = x * x + y * y;
        } while (r2 > 1.0 || r2 == 0.0);
        const double mult = std::sqrt(-2 * std::log(r2) / r2);
        ret = y * mult;
        ret = ret * stddev + mean;
        return ret;
    }
};

}  // namespace DISTRIBUTION

#endif
