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

const int N = 12; //100000;
vector<int> prime;
vector<int> lp(N + 1);
void minprimefact() {
     // calculating minimum prime factor. it only prints value once if there
     // are multiples
     // 8 => [2], 6 => [2,3], 100000 => [2,5]
     // I have 2 methods written down. first one is understanding purpose but it
     // also works. second one is from cp algorithsm  "sieve - linear time
     // algorithms" and applied same logic for printing value as first one.
     // second one is more neat, but I recommend you to watch first approach if
     // you have to modify some codes as you wish.

     // first approach is only to calculate minimum prime factor. no use of
     // global "prime" vector second approach is both calculating minimum prime
     // factor and calculating prime as well

     // you may want to print out duplicate numbers ,then delete below, and
     // modify N value to 100 to check to see if that is what you want
     // while (lp[j] ==
     // temp) { j = j / lp[j];
     // }

     for (int i = 2; i <= N; i++) {
          lp[i] = i;
     }
     for (int i = 2; i * i <= N; i++) {
          if (lp[i] == i) {
               for (int j = i * i; j <= N; j += i) {
                    if (lp[j] == j) {
                         lp[j] = i;
                    }
               }
          }
     }
     cout << lp;
     for (int i = 2; i <= N; i++) {
          int j = i;
          cout << j << ": ";
          while (j != 1) {
               int temp = lp[j];
               cout << lp[j] << " ";
               j = j / lp[j];
               while (lp[j] == temp) {
                    j = j / lp[j];
               }
          }
          cout << "\n";
     }

     // for (int i = 2; i <= N; ++i) {
     //      if (lp[i] == 0) {
     //           lp[i] = i;
     //           prime.push_back(i);
     //      }
     //      for (int j = 0;
     //           j < (int)prime.size() && prime[j] <= lp[i] && i * prime[j] <= N;
     //           ++j) {
     //           lp[i * prime[j]] = prime[j];
     //      }
     // }
     // for (int i = 2; i <= N; i++) {
     //      int j = i;
     //      cout << j << ": ";
     //      while (j != 1) {
     //           int temp = lp[j];
     //           cout << lp[j] << " ";
     //           j = j / lp[j];
     //           while (lp[j] == temp) {
     //                j = j / lp[j];
     //           }
     //      }
     //      cout << "\n";
     // }
}

int main() {
     ios::sync_with_stdio(0);
     cout.tie(0);
     minprimefact();
}
