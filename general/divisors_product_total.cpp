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
const int mod = 1e9 + 7;
vector<int> factorization;

void trial_division1(ll n) {
     for (ll d = 2; d * d <= n; d++) {
          while (n % d == 0) {
               factorization.push_back(d);
               n /= d;
          }
     }
     if (n > 1) {
          factorization.push_back(n);
     }
}
using u64 = uint64_t;
u64 binpower(u64 base, u64 e) {
     //integer range [2 <= N <= 2^63-1] can be AC
     //                       = 9*10^18
     u64 result = 1;
     base %= mod;
     while (e) {
          if (e & 1) {
               result = (u128)result * base % mod;
          }
          base = (u128)base * base % mod;
          e >>= 1;
     }
     return result;
}

ll multiplyFactors(ll n, ll numFactor) {

     // Calculate product of factors
     ll product = binpower(n, numFactor / 2);

     // If numFactor is odd return
     // power(n, numFactor/2) * sqrt(n)
     if (numFactor & 1)
          product = (product * (int)sqrt(n)) % mod;

     return product;
}

int main() {

     int n;
     cin >> n;
     // n = 12
     // 1 * 2 * 3 * 4 * 6 * 12 = 1728
     //https://www.geeksforgeeks.org/product-factors-number/
     map<ll, int> mp;
     trial_division1(n);
     int sz = factorization.size();
     for (int i = 0; i < sz; i++) {
          mp[factorization[i]]++;
     }
     cout << factorization;
     ll p = 1;
     for (auto x : mp) {
          p *= x.second + 1; // counting how many power in n
     }
     ll bb = multiplyFactors(n, p);
     cout << bb;
     return 0;
}
