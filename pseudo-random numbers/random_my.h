#ifndef RANDOM_MY_H
#define RANDOM_MY_H

namespace RAND_GEN {
class mod_my {
  public:
    int m, a, c;
    mod_my(int _m, int _a, int _c) : m(_m), a(_a), c(_c) {}

    //  General case for x = (ax + c) mod m -- use Schrage's algorithm
    //  to avoid integer overflow.
    //  (ax + c) mod m can be rewritten as:
    //    a(x mod q) - r(x / q)  if >= 0
    //    a(x mod q) - r(x / q)  otherwise
    //  where: q = m / a , r = m mod a
    // 
    //  Preconditions:  a > 0, m > 0.
    //
    //  Note: only works correctly for m % a < m / a.
    int calc(int x) {
        if (a == 1) x %= m;
        else {
            static const int q = m / a;
            static const int r = m % a;
            int t1 = a * (x % q);
            int t2 = r * (x / q);
            if (t1 >= t2) x = t1 - t2;
            else x = m - t2 + t1;
        }
        if (c != 0) {
            const int d = m - x;
            if (d > c) x += c;
            else x = c - d;
        }
        return x;
    }
};

class linear_congruential_engine_my {
public:
    int multiplier, increment, modulus;
    unsigned int default_seed_my, seed_my;
    mod_my mod_temp;

    linear_congruential_engine_my()
    : multiplier(16807), increment(1), modulus(2147483647)
    , default_seed_my(1u), mod_temp(modulus, multiplier, increment)
    { seed(default_seed_my); }

    linear_congruential_engine_my(int _m, int _a, int _c, int _s)
    : multiplier(_a), increment(_c), modulus(_m)
    , default_seed_my(_s), mod_temp(modulus, multiplier, increment)
    { seed(default_seed_my); }

    void seed(unsigned int s)
    { seed_my = s; }

    int min()
    { return  increment == 0u ? 1u : 0u; }

    int max()
    { return modulus - 1u; }

    void discard(unsigned long long z)
    { for (; z != 0ULL; --z) (*this)(); }

    int operator()() {
        seed_my = mod_temp.calc(seed_my);
        return seed_my;
    }
};

}  // namespace RAND_GEN

#endif
