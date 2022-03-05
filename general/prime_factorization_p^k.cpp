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

vector<ll> prime;
vector<int> p, k;
void sieve(ll N, vector<ll> lp) {

     for (int i = 2; i <= N; ++i) {
          if (lp[i] == 0) {
               lp[i] = i;
               prime.push_back(i);
          }
          for (int j = 0;
               j < (int)prime.size() && prime[j] <= lp[i] && i * prime[j] <= N;
               ++j) {
               lp[i * prime[j]] = prime[j];
          }
     }
     // cout << lp;
     for (int i = N; i <= N; i++) {
          int j = i;
          // cout << j << ": ";
          while (j != 1) {
               int cnt = 0;
               cnt++;
               int temp = lp[j];

               p.emplace_back(lp[j]);
               cout << lp[j] << "^";

               j = j / lp[j];
               while (lp[j] == temp) {
                    cnt++;
                    j = j / lp[j];
               }

               cout << cnt << " ";
               k.emplace_back(cnt);
          }
          cout << "\n";
     }
     cout << p << k;
}

int main() {
     ios::sync_with_stdio(0);
     cout.tie(0);
     ll N;
     cin >> N;
     vector<ll> lp(N + 1);

     sieve(N, lp);
     // n = 12;
     // return 2^2 3^1
}
