#include <algorithm>
#include <array>
#include <cassert>
#include <chrono>
#include <cmath>
#include <cstdint>
#include <cstring>
#include <functional>
#include <iomanip>
#include <ios>
#include <iostream>
#include <map>
#include <numeric>
#include <ostream>
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
using u128 = __uint128_t;

int main() {
     //https://atcoder.jp/contests/abc169/tasks/abc169_c
     //Compute A×B, truncate its fractional part, and print the result as an integer

     //198 * 1.10   = 217  = 198*1.10
     //664706138336385 * 9.79

     //tip1
     // if you cin 9.79 as double, when you debeg it, you will see 9,79 is stored as 9.7899999999999991 (it happens always +- 0.5) that's why we should +0.5

     //tip2
     //always get rid of floating points by multiplication of 100 or  1000 if floating points are 3 digits
     // 9.79 >> 979 by multiplying 100 and dont forget +0.5

     // Multiplying as floating point numbers does not provide sufficient precision. By multiplying B by
     // 100 and calculating (A×( B × 100 + 0.5))/100.
     ios::sync_with_stdio(0);
     cin.tie(0);
     ll a;
     double b;
     cin >> a >> b;
     ll ans = (b * 100 + 0.5);
     cout << (ans * a) / 100;
}
