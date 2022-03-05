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

const int MOD = 1e9 + 7;

ll c(ll n) {
     return n % MOD * ((n - 1) % MOD) % MOD * ((MOD + 1) / 2) % MOD;
}

//https://cses.fi/problemset/task/1082/
//This method is sqrt(N),and only can be AC when using sqrt(N) because 1≤n≤10^12
//since constraint is huge enough, we have to use sqrt(N). O(n) gives me TLE

//This is a simple calculation for summation of σ(i) but huge traps because of MOD

//variation of this problem can be calculation for summation of σ(i) * i
//which is https://atcoder.jp/contests/abc172/tasks/abc172_d.  O(n) can be AC. 1<=N<=10^7
//when dealing with σ(i) * i, you just need to calculate
// ll f(ll n) {
//      return n * (n + 1) / 2;
// }
//f(n / i) * (f(r) - i * (i - 1) / 2)

// with this problem n/i is only diff(line66). this problem of solution is n/i, above σ(i) * i problem is f(n/i)
int main() {
     ios::sync_with_stdio(0);
     cin.tie(0);
     ll n;
     cin >> n;
     ll te = 0;
     for (ll i = 1; i <= n; i++) {
          ll r = n / (n / i);
          te += n / i % MOD * (c(r + 1) - c(i) + MOD) % MOD;
          i = r;
     }
     cout << te % MOD;
}