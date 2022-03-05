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
int main() {
     // how many integer Factorization in a number?
     // for example 48
     // [1,2,3,4,6, 8 ,12, 16,24 48]
     // total 10
     // how to get it fastly? we need to use prime factorization
     // https://mathschallenge.net/library/number/number_of_divisors

     // roughly, it says digit(p^a * q^b)=(a+1)(b+1).
     // so when we use primefactorization, 48 becomes
     // 2^4 * 3^1
     // we take 4 and 1
     // and add +1 for each
     // 5 and 2 = 5 * 2 = 10
     // total 10 digits of number of divisors

     map<ll, int> mp;
     trial_division1(6);
     int sz = factorization.size();
     for (int i = 0; i < sz; i++) {
          mp[factorization[i]]++;
     }
     cout << factorization;
     ll p = 1;
     for (auto x : mp) {
          // cout << x.first << "^" << x.second << "\n";
          p *= x.second + 1;
     }
     // cout << mp;
     cout << p;

     return 0;
}