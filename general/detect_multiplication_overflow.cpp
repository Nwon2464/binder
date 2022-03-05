#include <chrono>
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
// https://atcoder.jp/contests/abc169/tasks/abc169_b

// Given N integers, compute all by multiplication.
// A[i] x A[i+1] x A[i+2] .... A[N]
// if the result exceeds 10^18, print -1
// seems easy, but trap presents

// 1. how do you detect if it is overflow or not ?
// as you multiply values, it will overflow

// example n = 2 , [4294967296, 4294967296]
// ll ans = 1   (fail)
// rep(i,0,n) {
//   ans *= a[i]                <<< 4294967296  * 4294967296  = 0 overflow, so won't print -1 (if 0 > 10^8) >false.
//   if(ans > 10^18) print -1        <<< no, it doesnt work. it already overflows from above.
// }

// same approach but if check first. (fail)
// ll ans = 1
// rep(i,0,n) {
//   if(ans * a[i]> 10^18) print -1        <<< no, it doesnt work too. 4294967296  * 4294967296  = 0. 0>10^18 false.
//   ans *= a[i]                .
// }

// 2 method for workaround for detecting overflow

// 1 method
// if you notice, if(ans * a[i] > 10^18) print -1  or  if(ans*a[i] <= 10^18) ans*=a[i] , this is the condition we want
// to check. we can say,    if(a[i] > 10^18 / ans) print -1  or  if(a[i] <= 10^18 / ans) ans*= a[i] or we can say,
// if(ans >  10^18 / a[i]) print -1  or if(ans <= 10^18 / a[i]) ans*=a[i]

// 2 method
// using __uint128_t
// this method cannot be printed. because it doesnt support c++ printing
// if you do declare u128 ans = 1, cannot use cout.  it gives me error
// so, as we multiply by values, (it doesnt overflow, because we use __uint128_T), we just check to see if value is
// greater than 10^18 or not with boolean flag if val is greater, we print -1 else since we know this is long long,
// because we calculate vals and it it not greater than 10^8 print ll(ans)
using u128 = __uint128_t;
const ll nax = 1000000000000000000;
// method 1
int main() {
     ios::sync_with_stdio(0);
     cin.tie(0);
     int n;
     cin >> n;

     vector<ll> a(n);
     rep(i, 0, n) {
          cin >> a[i];
          if (a[i] == 0) return cout << "0", 0;
     }
     ll ans = 1;
     rep(i, 0, n) {
          if (a[i] <= nax / ans)
               ans *= a[i];
          else {
               return cout << -1, 0;
          }
          // or
          // if (a[i] > nax/ ans) return cout << -1,0;
          // ans *= a[i];
     }
     cout << ans;
}

// method 2
// int main() {
//      ios::sync_with_stdio(0);
//      cin.tie(0);
//      int n;
//      cin >> n;

//      vector<ll> a(n);
//      rep(i, 0, n) {
//           cin >> a[i];
//           if (a[i] == 0) return cout << "0", 0;
//      }
//      u128 ans = 1;               <<<<<  using u128
//      rep(i, 0, n) {
//           ans *= a[i];
//           if(ans > 10^8) flag = true; break;
//      }
//      cout << (flag ? -1 : (ll)ans);
// }