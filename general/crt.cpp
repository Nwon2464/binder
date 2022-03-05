#include <algorithm>
#include <array>
#include <cassert>
#include <chrono>
#include <cmath>
#include <cstring>
#include <functional>
#include <iomanip>
#include <ios>
#include <iostream>
#include <iterator>
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
const char el = '\n';

// clang-format off
template<typename T> ostream &operator<<(ostream &os, const vector<T> &vec){ os << "["; for (auto v : vec) os << v << ","; os << "]"; return os; }
template<typename T_vector>void output_vector(const T_vector &v, bool add_one = false, int start = -1, int end = -1) {if (start < 0) start = 0; if (end < 0) end = int(v.size()); for (int i = start; i < end; i++) cout << v[i] + (add_one ? 1 : 0) << (i < end - 1 ? ' ' : '\n');}
template<typename T1, typename T2> ostream &operator<<(ostream &os, const pair<T1, T2> &pa){ os << "(" << pa.first << "," << pa.second << ")"; return os; }
template<typename TK, typename TV> ostream &operator<<(ostream &os, const map<TK, TV> &mp){ os << "{"; for (auto v : mp) os << "(" << v.first << ":" << v.second << ")" << ","; os << "}"; return os; }


auto random_address = [] {char *p = new char; delete p;return uint64_t(p);};
const uint64_t SEED = chrono::steady_clock::now().time_since_epoch().count() * (random_address() | 1);
mt19937_64 rng(SEED);
// clang-format on

ll gcdex(ll a, ll b, ll& x, ll& y) {
     // Solves the equation ax + by = gcd(a, b)
     // returns gcd(a, b)
     // save x and y in given values
     //
     // Correctness tested on random tests.
     // Correctness tested on the following problem:
     // https://atcoder.jp/contests/tenka1-2017/tasks/tenka1_2017_f
     //
     if (a == 0) {
          x = 0, y = 1;
          return b;
     }
     ll x1, y1;
     ll g = gcdex(b % a, a, x1, y1);
     x = y1 - (b / a) * x1;
     y = x1;
     return g;
}

pair<ll, ll> crt(vector<ll> r, vector<ll> m) {
     // Finds such x, that x mod m[i] = r[i] for each i
     // if such x does not exist returns {0, 0}
     //
     // Correctness tested on random tests.
     // Correctness tested on the following problem:
     // https://atcoder.jp/contests/tenka1-2017/tasks/tenka1_2017_f
     //
     int n = r.size();
     for (int i = 0; i < n; i++)
          r[i] %= m[i];
     ll r0 = 0, m0 = 1;
     for (int i = 0; i < n; i++) {
          ll r1 = r[i], m1 = m[i];
          if (m0 < m1) {
               swap(m0, m1);
               swap(r0, r1);
          }
          if (m0 % m1 == 0) {
               if (r0 % m1 != r1) return { 0, 0 };
               continue;
          }
          ll x, y;
          ll g = gcdex(m0, m1, x, y);
          ll u = m1 / g;
          if ((r0 - r1) % g != 0)
               return { 0, 0 };
          ll z = (r1 - r0) / g % u * x % u;
          r0 += z * m0;
          m0 *= u;
          if (r0 < 0) r0 += m0;
     }
     return { r0, m0 };
}

int main() {
     ios::sync_with_stdio(0);
     cin.tie(0);
     //IgorI  << author solution
}
