// #include <algorithm>
// #include <array>
// #include <cassert>
// #include <chrono>
// #include <cmath>
// #include <cstring>
// #include <functional>
// #include <iomanip>
// #include <iostream>
// #include <map>
// #include <numeric>
// #include <queue>
// #include <random>
// #include <set>
// #include <stack>
// #include <vector>
// using namespace std;

// using ll = long long;
// #define rep(i, a, b) for (int i = a; i < (b); ++i)
// #define sz(x) (int)(x).size()
// #define ms(arr, v) memset(arr, v, sizeof(arr))
// #define f first
// #define s second
// #define pb push_back

// // clang-format off
// template<typename T> ostream &operator<<(ostream &os, const vector<T> &vec){ os << "["; for (auto v : vec) os << v << ","; os << "]"; return os; }
// template<typename T_vector>void output_vector(const T_vector &v, bool add_one = false, int start = -1, int end = -1) {if (start < 0) start = 0; if (end < 0) end = int(v.size()); for (int i = start; i < end; i++) cout << v[i] + (add_one ? 1 : 0) << (i < end - 1 ? ' ' : '\n');}
// template<typename T1, typename T2> ostream &operator<<(ostream &os, const pair<T1, T2> &pa){ os << "(" << pa.first << "," << pa.second << ")"; return os; }
// template<typename TK, typename TV> ostream &operator<<(ostream &os, const map<TK, TV> &mp){ os << "{"; for (auto v : mp) os << "(" << v.first << ":" << v.second << ")" << ","; os << "}"; return os; }

// auto random_address = [] {char *p = new char; delete p;return uint64_t(p);};
// const uint64_t SEED = chrono::steady_clock::now().time_since_epoch().count() * (random_address() | 1);
// mt19937_64 rng(SEED);
// // clang-format on

// void hist(ll a[], int n) {
//      stack<int> x;
//      x.push(-1);

//      int max = 0, area = 0;

//      for (int i = 0; i < n; i++) {
//           if (x.top() == -1 or (a[x.top()] <= a[i]))
//                x.push(i);

//           else if (a[x.top()] > a[i]) {
//                int top = 0;
//                while ((a[x.top()] > a[i]) and x.top() != -1) {
//                     int s = x.top();
//                     x.pop();
//                     if (x.top() != -1)
//                          top = a[s] * (i - x.top() - 1);

//                     else
//                          top = a[s] * i;

//                     if (top > max) max = top;
//                }
//                x.push(i);
//           }
//      }

//      while (x.top() != -1) {
//           int s = x.top();
//           x.pop();
//           if (x.top() != -1) {
//                area = a[s] * (n - x.top() - 1);
//           }

//           else {
//                area = a[s] * n;
//           }

//           if (area > max) max = area;
//      }

//      cout << max << "\n";
// }

// int main() {
//      ios_base::sync_with_stdio(false);
//      cin.tie(NULL);

//      // int t;
//      // cin >> t;

//      // while (t--) {
//      int n;
//      cin >> n;

//      ll a[11111];
//      for (int i = 0; i < n; i++)
//           cin >> a[i];
//      hist(a, n);
// }

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

void solve() { }
// very well known problem. histogram problem, orange problem

// it can be solved with brute force(n^2) only if constraints 10^4, union find(any constraints), stack O(n).

// https://atcoder.jp/contests/abc189/tasks/abc189_c (Mandarin Orange)
// https://leetcode.com/problems/largest-rectangle-in-histogram/ (Largest Rectangle Histogram)
// https://www.codechef.com/problems/SPC1704 (Histogram)

// This implementation O(n^2) Only Works for 1≤N≤10^4
// if constraints of N is 10^5, it will give TLE

int main() {
     ios::sync_with_stdio(0);
     cin.tie(0);
     int t;
     cin >> t;
     while (t--) {
          ll n;
          cin >> n;
          vector<int> a(n);
          rep(i, 0, n) cin >> a[i];
          int ans = -1;
          for (int i = 0; i < n; i++) {
               int x = a[i];
               for (int j = i; j < n; j++) {
                    x = min(x, a[j]);
                    ans = max(ans, x * (j - i + 1));
               }
          }
          cout << ans << "\n";
     }

     // int tests;
     // cin >> tests;
     // while (tests-- > 0)
     //      solve();
}
