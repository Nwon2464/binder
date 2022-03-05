#include <algorithm>
#include <array>
#include <cassert>
#include <chrono>
#include <cmath>
#include <cstdint>
#include <cstring>
#include <functional>
#include <iomanip>
#include <iostream>
#include <map>
#include <numeric>
#include <ostream>
#include <queue>
#include <random>
#include <set>
#include <vector>

using namespace std;

#define endl "\n"

// clang-format off
int MOD = 1e9 + 7;

int mul(int a, int b){return (1LL * a * b) % MOD;}
int add(int a, int b){int s = (a + b);if (s >= MOD)s -= MOD; return s;}
int sub(int a, int b){int s = (a + MOD - b);if (s >= MOD)s -= MOD;return s;}
int binpow(int a, ll deg){if (deg == 0) return 1;if (deg % 2 == 1) return mul(a, binpow(a, deg - 1)); int t = binpow(a, deg / 2); return mul(t, t);}
int inv(int n){return binpow(n, MOD - 2);}

// neal's template

template<const int &MOD>
struct modint {
    int64_t n;
     
    modint(int64_t v = 0) {
        if (v < 0) v = v % MOD + MOD;
        if (v >= MOD) v %= MOD;
        n = int(v);
    }
 
    modint(uint64_t v) {
        if (v >= MOD) v %= MOD;
        n = int(v);
    }
 
    modint(int v) : modint(int64_t(v)) {}
    modint(unsigned v) : modint(uint64_t(v)) {}
    explicit operator int() const { return n; }
    explicit operator unsigned() const { return n; }
    explicit operator int64_t() const { return n; }
    explicit operator uint64_t() const { return n; }
    explicit operator double() const { return n; }
    explicit operator long double() const { return n; }
    modint& operator++() {
          n = n == MOD - 1 ? 0 : n + 1;
          return *this;
    }
    modint& operator--() {
      n = n == 0 ? MOD - 1 : n - 1;
      return *this;
    }
    modint operator++(int) {
      modint before = *this;
      ++*this;
      return before;
    }
    modint operator--(int) {
      modint before = *this;
      --*this;
      return before;
    }
    modint operator-() const { return n == 0 ? 0 : MOD - n; }
    friend bool operator==(const modint& a, const modint& b) { return a.n == b.n; }
    friend bool operator!=(const modint& a, const modint& b) { return a.n != b.n; }
    friend bool operator<(const modint& a, const modint& b) { return a.n < b.n; }
    friend bool operator>(const modint& a, const modint& b) { return a.n > b.n; }
    friend bool operator<=(const modint& a, const modint& b) { return a.n <= b.n; }
    friend bool operator>=(const modint& a, const modint& b) { return a.n >= b.n; }
    modint& operator+=(const modint& a) {
      n += a.n;
      if (n >= MOD) n -= MOD;
      return *this;
    }
    modint& operator-=(const modint& a) {
      n -= a.n;
      if (n < 0) n += MOD;
      return *this;
    }
    modint& operator*=(const modint& a) {
      n = ((int64_t)n * a.n) % MOD;
      return *this;
    }
    modint& operator/=(const modint& a) { return *this *= a.inv(); }
    modint inv() const { return pow(MOD - 2); }
 
    friend modint operator/(const modint& a, const modint& b) { return modint(a) /= b; }
    friend modint operator+(const modint& a, const modint& b) { return modint(a) += b; }
    friend modint operator-(const modint& a, const modint& b) { return modint(a) -= b; }
    friend modint operator*(const modint& a, const modint& b) { return modint(a) *= b; }
    friend modint operator^(modint a, int64_t n) {
      if (n == 0) return modint(1);
      modint res = (a * a) ^ (n / 2);
      if (n % 2) res = res * a;
      return res;
    }
 
    modint pow(int64_t p) const {
      if (p < 0) return inv().pow(-p);
      modint a = *this, result = 1;
      while (p > 0) {
           if (p & 1) result *= a;
           p >>= 1;
           if (p > 0) a *= a;
      }
      return result;
    }
    friend ostream& operator<<(ostream& os, const modint& a) { return os << a.n; }
};
 
extern const int MOD = 998244353;
using mod_int = modint<MOD>;
 
const int max_n = 1000005;  // 1 << 20;
mod_int fact[max_n], inv_fact[max_n];
void prepare_factorial() {
     fact[0] = mod_int(1);
     for (int i = 0; i < max_n - 1; i++) {
          fact[i + 1] = fact[i] * mod_int(i + 1);
     }
     inv_fact[max_n - 1] = mod_int(1) / fact[max_n - 1];
     for (int i = max_n - 2; i >= 0; i--) {
          inv_fact[i] = inv_fact[i + 1] * mod_int(i + 1);
     }
}

mod_int factorial(int64_t n) {
     if (n < 0) return 0;
     return fact[n];
}

mod_int inv_factorial(int64_t n) {
     if (n < 0) return 0;
     return inv_fact[n];
}
mod_int combination(int a, int b) {
     if (a < 0 || b < 0 || a < b) return 0;
     return fact[a] * inv_fact[b] * inv_fact[a - b];
}
mod_int permutation(int a, int b) {
     if (a < 0 || b < 0 || a < b) return 0;
     return fact[a] * inv_fact[a - b];
}

mod_int inv_combination(int64_t n, int64_t r) {
     assert(0 <= r && r <= n);
     return inv_fact[n] * fact[r] * fact[n - r];
}

mod_int inv_permutation(int64_t n, int64_t r) {
     assert(0 <= r && r <= n);
     return inv_fact[n] * fact[n - r];
}
// clang-format on

const int E_MAX = 1000005;

int main() {
    ios::sync_with_stdio(false);

    vector<mod_int> p2(E_MAX + 1, 1);
    return 0;
}