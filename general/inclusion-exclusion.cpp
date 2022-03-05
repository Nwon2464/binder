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
#define rip(i, a, b) for (int i = a; i < (b); ++i)
#define ripp(i, a, b) for (int i = a; i <= (b); ++i)
#define sz(x) (int)(x).size()
#define ms(arr, v) memset(arr, v, sizeof(arr))

// clang-format off
template<typename T_container, typename T = typename enable_if<!is_same<T_container, string>::value, typename T_container::value_type>::type> ostream& operator<<(ostream &os, const T_container &v) { os << '{'; string sep; for (const T &x : v) os << sep << x, sep = ", "; return os << '}'; }
void debug() { cerr << endl; }
template<typename Head, typename... Tail> void debug(Head H, Tail... T) { cerr << "DEBUG => " << H; debug(T...); }
auto random_address = [] {char *p = new char; delete p;return uint64_t(p);};
const uint64_t SEED = chrono::steady_clock::now().time_since_epoch().count() * (random_address() | 1);
mt19937_64 rng(SEED);
// clang-format on

using u64 = uint64_t;
using u128 = __uint128_t;

ll r, k;
// this implementation is bitmask inclusion-exclusion
// constraints are should be small 2  ^ n
// 20 is max iguess
ll gcd(ll a, ll b);

ll lcm(ll a, ll b) {
     return a / gcd(a, b) * b;
}

ll gcd(ll a, ll b) {
     return b == 0 ? a : gcd(b, a % b);
}

void solve() {
     vector<ll> p;
     // if r= 20,
     // and prime number is not given, instead natural number is given n = 20,
     // you need to find and
     // count the number of integers in the interval [1;r] that are relatively
     // prime to n
     //(their greatest common divisor is 1).
     cin >> r >> k;
     for (int i = 0; i < k; i++) {
          ll x;
          cin >> x;
          p.push_back(x);
     }
     ll sum = 0;
     for (ll msk = 1; msk < (1 << p.size()); ++msk) {
          double mult = 1; // double in used  to prevent from multiplying overflow
          ll bits = 0;
          for (ll i = 0; i < (ll)p.size(); ++i)
               if (msk & (1 << i)) {
                    ++bits;
                    mult *= p[i]; // when r is 10^18 (ll) The number of relative primes in a given interval
                    // mult = lcm(p[i], (ll)mult); // when r is 10^9 (int) The number of integers in a given interval which are multiple of at least one of the given numbers

               } // when you mult *= p[i] since double in used, prevent from
          // overflow
          // when mult *= p[i] with double , it give me scientific value i,e
          // x.xxxxxxe+32
          // 24929660627620033 * 16706748220911473 ==> overflow when used ll
          // mult = 1
          ll cur = r / (ll)mult;
          // typecasting needed to get 0 for ll cur
          // i.e) if you dont typecasting  r / x.xxxxxxxx+30 =>
          // x.xxxxxxxxxx+xx if you typecast, r / (ll)mult = 0,
          // bc demoniator is always greater in this case.

          if (bits % 2 == 1) // if bit rem is 1, new subset adding
               sum += cur;
          else // if rem is 0, substracting duplicate subsets
               sum -= cur;
     }
     cout << sum << "\n";
     // cout << r- sum;
}

int main() {
     ios::sync_with_stdio(false);
     cin.tie(0);

     int tests;
     cin >> tests;
     while (tests-- > 0)
          solve();
}

//atcoder 172 E NEQ Inclusion exclusion
// const int mod = 1e9 + 7;

// struct modint {
//      ll n;
//      modint()
//          : n(0) { ; }
//      modint(ll m)
//          : n(m) {
//           if (n >= mod)
//                n %= mod;
//           else if (n < 0)
//                n = (n % mod + mod) % mod;
//      }
//      operator int() { return n; }
// };
// bool operator==(modint a, modint b) { return a.n == b.n; }
// modint operator+=(modint& a, modint b) {
//      a.n += b.n;
//      if (a.n >= mod) a.n -= mod;
//      return a;
// }
// modint operator-=(modint& a, modint b) {
//      a.n -= b.n;
//      if (a.n < 0) a.n += mod;
//      return a;
// }
// modint operator*=(modint& a, modint b) {
//      a.n = ((ll)a.n * b.n) % mod;
//      return a;
// }
// modint operator+(modint a, modint b) { return a += b; }
// modint operator-(modint a, modint b) { return a -= b; }
// modint operator*(modint a, modint b) { return a *= b; }
// modint operator^(modint a, ll n) {
//      if (n == 0) return modint(1);
//      modint res = (a * a) ^ (n / 2);
//      if (n % 2) res = res * a;
//      return res;
// }

// ll inv(ll a, ll p) {
//      return (a == 1 ? 1 : (1 - p * inv(p % a, a)) / a + p);
// }
// modint operator/(modint a, modint b) { return a * modint(inv(b, mod)); }
// modint operator/=(modint& a, modint b) {
//      a = a / b;
//      return a;
// }
// const int max_n = 1 << 20;
// modint fact[max_n], factinv[max_n];
// void init_f() {
//      fact[0] = modint(1);
//      for (int i = 0; i < max_n - 1; i++) {
//           fact[i + 1] = fact[i] * modint(i + 1);
//      }
//      factinv[max_n - 1] = modint(1) / fact[max_n - 1];
//      for (int i = max_n - 2; i >= 0; i--) {
//           factinv[i] = factinv[i + 1] * modint(i + 1);
//      }
// }
// modint comb(int a, int b) {
//      if (a < 0 || b < 0 || a < b) return 0;
//      return fact[a] * factinv[b] * factinv[a - b];
// }
// modint combP(int a, int b) {
//      if (a < 0 || b < 0 || a < b) return 0;
//      return fact[a] * factinv[a - b];
// }

// when n == m , at last, dont forget multiply by n!
// when m >= n , at last  dont forget multiply by mPn because we have to choose first A permutation by mPn
// and then nCr * m-i P n-i

// variation will be this equation.
// always (n-k) ! * n C i up to k(inclusive) * -1^k remember.
//          | part replace it with m-i P n-i

// this is inclusion-exclusion when constraints are huge
// int main() {
//      ios::sync_with_stdio(0);
//      cin.tie(0);
//      init_f();
//      int n, m;
//      cin >> n >> m;
//      modint ans = 0;
//      rep(i, 0, n + 1) {
//           modint now = comb(n, i);
//           now *= combP(m, n);
//           now *= combP(m - i, n - i);
//           if (i & 1) {
//                now = -now;
//           }
//           ans += now;
//      }
//      cout << ans << endl;
//      // int tests;
//      // cin >> tests;
//      // while (tests-- > 0)
//      //      solve();
// }