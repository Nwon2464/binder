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

const int MOD = 1e9 + 7;
int mul(int a, int b) { return (1LL * a * b) % MOD; }
int add(int a, int b) {
     int s = (a + b);
     if (s >= MOD) s -= MOD;
     return s;
}
int main() {
     //https://atcoder.jp/contests/abc177/tasks/abc177_c
     //sum of a[i] * a[j] over all pairs i,j such that 1 <= i < j <= n. mod 1e9+7
     //example 1,2,3
     //1 * 2 + 1 * 3 + 2 * 3 = 11

     //   1 2 3
     // 1
     // 2 x
     // 3 x x

     // only need to calculate x parts
     // 2 * (1)     = 2
     // 3 * (1 + 2) = 9
     //             = 11

     //example 3 1 4 1 5

     //      3 1 4 1 5
     //   3
     //   1  x
     //   4  x x
     //   1  x x x
     //   5  x x x x

     // 1 * (3)
     // 4 * (3 + 1)
     // 1 * (3 + 1 + 4)
     // 5 * (3 + 1 + 4 + 1)

     int n;
     cin >> n;
     vector<int> a(n);
     rep(i, 0, n) cin >> a[i];
     int x = 0;
     int s = 0;


     for (int i = 1; i < n; i++) {
          x = add(x, a[i - 1]); // x += a[i-1];
          s = add(s, mul(a[i], x)); // s += a[i] * x;
     }
     cout << s << endl;
}

     // using modint and modinverse

     //   3 1 4 1 5
     // 3 x
     // 1   x
     // 4     x
     // 1       x
     // 5         x


     //  ----------        \
     // |          |        \
     // |          |         \
     // |          |   -      \
     // |          |           \
     // |          |            \
     //  ----------

     //  --------------------------

     //              2



     // answer = (total width - diagonal) /  2  (divide 2 needs mod inv)
     // whole width of rectangle 14 * 14
     // diagonal 9 + 1 + 16 + 1 + 25
     // divide by 2
     // vector<ll> a(n);
     // modint sum = 0;
     // rep(i, 0, n) {
     //      ll x;
     //      cin >> x;
     //      a[i] = x;
     //      sum += (modint)x;
     // }
     // sum *= sum; //rec width
     // modint diagonal = 0;
     // rep(i, 0, n) {
     //      diagonal += a[i] * a[i];
     // }
     // cout << (sum - diagonal) / modint(2) << endl;

// clang-format on