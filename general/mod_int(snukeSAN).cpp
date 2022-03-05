#include <algorithm>
#include <array>
#include <cassert>
#include <chrono>
#include <cmath>
#include <cstring>
#include <functional>
#include <iomanip>
#include <iostream>
#include <map>
#include <numeric>
#include <queue>
#include <random>
#include <set>
#include <vector>

using namespace std;

using ll = long long;
#define rep(i, a, b) for (int i = a; i < (b); ++i)
#define sz(x) (int)(x).size()
#define ms(arr, v) memset(arr, v, sizeof(arr))
#define f first
#define s second
#define pb push_back

// clang-format off
template<typename T> ostream &operator<<(ostream &os, const vector<T> &vec){ os << "["; for (auto v : vec) os << v << ","; os << "]"; return os; }
template<typename T_vector>void output_vector(const T_vector &v, bool add_one = false, int start = -1, int end = -1) {if (start < 0) start = 0; if (end < 0) end = int(v.size()); for (int i = start; i < end; i++) cout << v[i] + (add_one ? 1 : 0) << (i < end - 1 ? ' ' : '\n');}
template<typename T1, typename T2> ostream &operator<<(ostream &os, const pair<T1, T2> &pa){ os << "(" << pa.first << "," << pa.second << ")"; return os; }
template<typename TK, typename TV> ostream &operator<<(ostream &os, const map<TK, TV> &mp){ os << "{"; for (auto v : mp) os << "(" << v.first << ":" << v.second << ")" << ","; os << "}"; return os; }


auto random_address = [] {char *p = new char; delete p;return uint64_t(p);};
const uint64_t SEED = chrono::steady_clock::now().time_since_epoch().count() * (random_address() | 1);
mt19937_64 rng(SEED);
// auto mod int
// https://youtu.be/L8grWxBlIZ4?t=9858
// https://youtu.be/ERZuLAxZffQ?t=4807 : optimize
// https://youtu.be/8uowVvQ_-Mo?t=1329 : division
const int mod = 1000000007;
struct mint {
     ll x; // typedef long long ll;
     mint(ll x = 0)
         : x((x % mod + mod) % mod) { }
     mint operator-() const { return mint(-x); }
     mint& operator+=(const mint a) {
          if ((x += a.x) >= mod) x -= mod;
          return *this;
     }
     mint& operator-=(const mint a) {
          if ((x += mod - a.x) >= mod) x -= mod;
          return *this;
     }
     mint& operator*=(const mint a) {
          (x *= a.x) %= mod;
          return *this;
     }
     mint operator+(const mint a) const { return mint(*this) += a; }
     mint operator-(const mint a) const { return mint(*this) -= a; }
     mint operator*(const mint a) const { return mint(*this) *= a; }
     mint pow(ll t) const {
          if (!t) return 1;
          mint a = pow(t >> 1);
          a *= a;
          if (t & 1) a *= *this;
          return a;
     }

     // for prime mod
     mint inv() const { return pow(mod - 2); }
     mint& operator/=(const mint a) { return *this *= a.inv(); }
     mint operator/(const mint a) const { return mint(*this) /= a; }
};
istream& operator>>(istream& is, const mint& a) { return is >> a.x; }
ostream& operator<<(ostream& os, const mint& a) { return os << a.x; }
// combination mod prime
// https://www.youtube.com/watch?v=8uowVvQ_-Mo&feature=youtu.be&t=1619
struct combination {
     vector<mint> fact, ifact;
     combination(int n)
         : fact(n + 1)
         , ifact(n + 1) {
          assert(n < mod);
          fact[0] = 1;
          for (int i = 1; i <= n; ++i)
               fact[i] = fact[i - 1] * i;
          ifact[n] = fact[n].inv();
          for (int i = n; i >= 1; --i)
               ifact[i - 1] = ifact[i] * i;
     }
     mint operator()(int n, int k) {
          if (k < 0 || k > n) return 0;
          return fact[n] * ifact[k] * ifact[n - k];
     }
     mint p(int n, int k) {
          return fact[n] * ifact[n - k];
     }
} c(1000005);
// clang-format on

int main() {

     mint ans = 0;
     // combination nCr, nPr
     // mint now = c(n, i);
     // c.p(m, n);
     // c.p(m - i, n - i);

     // bin power
     // ll l=2;
     // mint x = mint(21).pow(l);

     return 0;
}