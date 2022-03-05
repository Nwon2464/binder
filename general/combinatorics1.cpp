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

const int MOD = 1e9 + 9;

int mul(int a, int b) { return (1LL * a * b) % MOD; }
int add(int a, int b) {
     int s = (a + b);
     if (s >= MOD) s -= MOD;
     return s;
}

ll binpow(ll a, ll b) {
     a %= MOD;
     ll res = 1;
     while (b > 0) {
          if (b & 1) res = res * a % MOD;
          a = a * a % MOD;
          b >>= 1;
     }
     return res;
}
int inv(int n) { return binpow(n, MOD - 2); }

const int N = 1e6;
ll fact[N];

void precal_factmod() {
     fact[0] = 1;
     for (ll i = 1; i < N; i++) fact[i] = mul(fact[i - 1], i);
}

ll nCr2(ll n, ll r) { return mul(fact[n], inv(mul(fact[r], fact[n - r]))); }
int main() {
     ios::sync_with_stdio(0);
     cin.tie(0);

     // clang-format on

     precal_factmod();
     int tests;
     cin >> tests;
     while (tests-- > 0) {
          ll l, k;
          cin >> l >> k;
          cout << mul((binpow(21, l - k) * binpow(5, k) % MOD), nCr2(l, k))
               << "\n";
     }

     // when exactly K vowel, and Length
     // the location of the vowel can be chosen in LCK, in given number of
     // length,how many vowels can we put ? LCK For each choice of location, it
     // can be filled with 5^K that leaves L-K empty locations, that can be
     // filled with consonants in 21^(L-K)
     // https://math.stackexchange.com/questions/246687/combinatorics-question-about-english-letters-with-consonants-and-vowels

     return 0;
}
