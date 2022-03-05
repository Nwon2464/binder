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

ll f(ll n) {
     return n * (n + 1) / 2;
}

// https://atcoder.jp/contests/abc172/tasks/abc172_d sum of divisors
// problem is find summation of σ(i) * i.  1<=N<=10^7
// since constraint is not huge like CSES Problem(10^12), three solution can be AC
// use O(N) or O(N*logN) or O(sqrt(N))(this is CSES problem sum of divisors approach. heavily math)

// watch O(NlogN) solution first for how i approach this

// O(NlogN)

// when n = 8
// 1 2 3 4 5 6 7 8
//   2   4   6   8
//     3     6
//       4       8
//         5
//           6
//             7
//               8
// d => [1,2,2,3,2,4,2,4] do you see the pattern?

// int main() {
//      ios::sync_with_stdio(0);
//      cin.tie(0);
//      ll ans = 0;
//      int n;
//      cin >> n;
//      vector<int> d(n + 1);
//      for (int i = 1; i <= n; i++) {
//           for (int j = i; j <= n; j += i) {
//                d[j]++;
//           }
//      }
//      for (int i = 1; i <= n; i++) {
//           ans += (ll)i * d[i];
//      }
//      cout << ans;
// }

// O(N)
// when n = 8
// see differently unlike above approach

// 1 2 3 4 5 6 7 8   -> 8
//   2   4   6   8   -> 4
//     3     6       -> 2
//       4       8   -> 2
//         5         -> 1
//           6       -> 1
//             7     -> 1
//               8   -> 1

// summation of 8 = 36 * idx1 =36 (why summation 8? because 1 means it has 8 number can divide by 8)
// summation of 4 = 10 * idx2 =20
// summation of 2 = 3 * idx3 = 9
// summation of 2 = 3 * idx4 = 12
// summation of 1 = 1 * idx5 = 5
// summation of 1 = 1 * idx6 = 6
// summation of 1 = 1 * idx7 = 7
// summation of 1 = 1 * idx8 = 8

// do you see the pattern?

// 8 divide by 1 = 8
// 8 divide by 2 = 4
// 8 divide by 3 = 2
// 8 divide by 4 = 2
// 8 divide by 5 = 1
// 8 divide by 6 = 1
// 8 divide by 7 = 1
// 8 divide by 8 = 1

// int main() {
//      ios::sync_with_stdio(0);
//      cin.tie(0);
//      ll ans = 0;
//      int n;
//      cin >> n;
//      for (int i = 1; i <= n; i++) {
//           ans += f(n / i) * i;
//           // ll a = f(n / i) * i;
//           // cout << a << " " << i << "\n";
//      }
//      cout << ans;
// }

// O(sqrt(N))
int main() {
     ios::sync_with_stdio(0);
     cin.tie(0);
     ll n;
     cin >> n;
     ll ans = 0;
     for (ll i = 1; i <= n; i++) {
          ll r = n / (n / i);
          // ans += f(n / i) * (r * (r + 1) / 2 - i * (i - 1) / 2);
          ans += f(n / i) * (f(r) - i * (i - 1) / 2);

          i = r;
     }
     cout << ans;
}
