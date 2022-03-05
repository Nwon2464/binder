#include <algorithm>
#include <array>
#include <cassert>
#include <chrono>
#include <cmath>
#include <cstdio>
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
#define sfint(a) scanf("%d", &a)
// clang-format off
template<typename T> ostream &operator<<(ostream &os, const vector<T> &vec){ os << "["; for (auto v : vec) os << v << ","; os << "]"; return os; }
template<typename T_vector>void output_vector(const T_vector &v, bool add_one = false, int start = -1, int end = -1) {if (start < 0) start = 0; if (end < 0) end = int(v.size()); for (int i = start; i < end; i++) cout << v[i] + (add_one ? 1 : 0) << (i < end - 1 ? ' ' : '\n');}
template<typename T1, typename T2> ostream &operator<<(ostream &os, const pair<T1, T2> &pa){ os << "(" << pa.first << "," << pa.second << ")"; return os; }
template<typename TK, typename TV> ostream &operator<<(ostream &os, const map<TK, TV> &mp){ os << "{"; for (auto v : mp) os << "(" << v.first << ":" << v.second << ")" << ","; os << "}"; return os; }
auto random_address = [] {char *p = new char; delete p;return uint64_t(p);};
const uint64_t SEED = chrono::steady_clock::now().time_since_epoch().count() * (random_address() | 1);
mt19937_64 rng(SEED);


int MOD = 1e9 + 7;

int mul(int a, int b) { return (1LL * a * b) % MOD; }
int sub(int a, int b) {int s = (a + MOD - b); if (s >= MOD) s -= MOD;return s;}
// clang-format on

// const int N = 1000001;  // dont change N. This is max you can set to. if you
// choose less, run time error.
const int N = 1 << 20;
ll fact_inverse[N + 1], factorial[N + 1];
ll inverse[N + 1];

void naive_factorial() {
     factorial[0] = 1;
     // precompute factorials
     for (int i = 1; i <= N; i++) {
          factorial[i] = mul(factorial[i - 1], i);
     }
}
void compute_inverse_for_every_number() {
     inverse[0] = inverse[1] = 1;
     for (ll i = 2; i <= N; ++i)
          inverse[i] = sub(MOD, mul((MOD / i), inverse[MOD % i]));
}

void inverse_factorial() {
     fact_inverse[0] = fact_inverse[1] = 1;
     for (ll i = 2; i <= N; i++)
          fact_inverse[i] = mul(fact_inverse[i - 1], inverse[i]);
}
ll nCr(ll n, ll r) {
     return mul(factorial[n], mul(fact_inverse[r], fact_inverse[n - r]));
}

ll nPr(ll n, ll r) { return mul(factorial[n], fact_inverse[n - r]); }
int main() {
     // this method computes binomial coefficient in O(1) time per query
     // because we precompute the inverses of all factorials in O(N log M)

     // computing all inverses
     // https://cp-algorithms.com/algebra/module-inverse.html#mod-inv-all-num
     // computing binomial coeff O(1)
     // https://cp-algorithms.com/combinatorics/binomial-coefficients.html
     compute_inverse_for_every_number();
     inverse_factorial();
     naive_factorial();
     int tests;
     scanf("%d", &tests);
     while (tests-- > 0) {
          int a, b;
          scanf("%d%d", &a, &b);
          cout << nCr(a, b) << " \n";
     }
     return 0;
}
