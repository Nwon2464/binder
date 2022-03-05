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
#define repp(i, a, b) for (int i = a; i <= (b); ++i)
#define sz(x) (int)(x).size()
#define ms(arr, v) memset(arr, v, sizeof(arr))

// clang-format off
template<typename T> ostream &operator<<(ostream &os, const vector<T> &vec){ os << "["; for (auto v : vec) os << v << ","; os << "]"; return os; }
template<typename T_vector>void output_vector(const T_vector &v, bool add_one = false, int start = -1, int end = -1) {if (start < 0) start = 0; if (end < 0) end = int(v.size()); for (int i = start; i < end; i++) cout << v[i] + (add_one ? 1 : 0) << (i < end - 1 ? ' ' : '\n');}
template<typename T1, typename T2> ostream &operator<<(ostream &os, const pair<T1, T2> &pa){ os << "(" << pa.first << "," << pa.second << ")"; return os; }
template<typename TK, typename TV> ostream &operator<<(ostream &os, const map<TK, TV> &mp){ os << "{"; for (auto v : mp) os << "(" << v.first << ":" << v.second << ")" << ","; os << "}"; return os; }


auto random_address = [] {char *p = new char; delete p;return uint64_t(p);};
const uint64_t SEED = chrono::steady_clock::now().time_since_epoch().count() * (random_address() | 1);
mt19937_64 rng(SEED);
// clang-format on

// more efficient method O(maxlog log max) using sieve
// this is for multiple query
//
const int N = 10000000;
int lp[N + 1];
vector<int> pr;
void sieve() {
     for (int i = 2; i <= N; ++i) {
          if (lp[i] == 0) {
               lp[i] = i;
               pr.push_back(i);
          }
          for (int j = 0; j < (int)pr.size() && pr[j] <= lp[i] && i * pr[j] <= N;
               ++j)
               lp[i * pr[j]] = pr[j];
     }
}

ll sumFactors(ll n) {

     ll res = 1, prev = lp[n];
     ll term = prev, sum = 1 + prev;
     n = n / prev;
     while (n > 1) {
          if (lp[n] == prev) {
               term = term * prev;
               sum = sum + term;
          } else {
               prev = lp[n];
               res = res * sum;
               term = prev;
               sum = 1 + term;
          }
          n = n / prev;
     }
     res = res * sum;
     return res;
}

int main() {
     ios::sync_with_stdio(0);
     cin.tie(0);
     sieve();
     ll n;
     cin >> n;
     rep(i, 0, n) {
          int x;
          cin >> x;
          cout << sumFactors(x);
     }
}
