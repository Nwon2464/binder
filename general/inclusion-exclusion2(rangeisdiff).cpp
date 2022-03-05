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
// clang-format on

ll gcd(ll a, ll b);

ll lcm(ll a, ll b) {
     return a / gcd(a, b) * b;
}

ll gcd(ll a, ll b) {
     return b == 0 ? a : gcd(b, a % b);
}

int main() {
     ios::sync_with_stdio(0);
     cin.tie(0);
     //https://www.spoj.com/problems/EASYMATH/
     //this is almost identical to inclusion-exclusion implementation
     //only diff is original one is always range from 1 to N
     //but this problem, range is given like 20 ~ 100
     // (20 - 100)   3 multiples
     //to solve this problem, need to calculate one by one.
     // a = 20 , b = 100 (inclusive)
     // a-- < because it is inclusive so 19 ~100 means total 80 numbers same as b - a +1

     //calculate one by one ll d1 = a , ll d2 = b ;
     // if(bit&1) a -= d1/ mult and b -= d2/mult

     ll a, b, x, y;
     cin >> a >> b >> x >> y;
     vector<ll> v;

     for (int i = 0; i < 5; i++) {
          ll c = x + (i * y);
          v.push_back(c);
     }
     a--;
     ll d1 = a;
     ll d2 = b;

     for (ll msk = 1; msk < (1 << sz(v)); ++msk) {
          ll mult = 1; // double in used  to prevent from multiplying overflow
          ll bits = 0;
          for (ll i = 0; i < sz(v); ++i)
               if (msk & (1 << i)) {
                    ++bits;
                    // mult *= v[i]; // when r is 10^18 (ll) The number of relative primes in a given interval
                    mult = lcm(v[i], (ll)mult); // when r is 10^9 (int) The number of integers in a given interval which are multiple of at least one of the given numbers
               }
          if (bits % 2 == 1) {
               a -= d1 / mult;
               b -= d2 / mult;
          } else {
               a += d1 / mult;
               b += d2 / mult;
          }
     }
     cout << b - a << endl;
}
