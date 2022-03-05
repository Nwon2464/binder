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
#include <stack>
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

// very well known problem. histogram problem, orange problem

// it can be solved with brute force(n^2) only if constraints 10^4, union find(any constraints), stack O(n).

// https://atcoder.jp/contests/abc189/tasks/abc189_c (Mandarin Orange)
// https://leetcode.com/problems/largest-rectangle-in-histogram/ (Largest Rectangle Histogram)
// https://www.codechef.com/problems/SPC1704 (Histogram)

// This implementation O(n) it works for any case

using P = pair<int, int>;
vector<int> getLeft(vector<int> a) {
     int n = a.size();
     vector<int> res(n);
     stack<P> ps;
     ps.emplace(0, -1);
     rep(i, 0, n) {
          while (ps.top().first >= a[i])
               ps.pop();
          res[i] = ps.top().second;
          ps.emplace(a[i], i);
     }
     return res;
}

int main() {
     ios_base::sync_with_stdio(false);
     cin.tie(NULL);
     int n;
     cin >> n;
     vector<int> a(n);
     rep(i, 0, n) cin >> a[i];
     vector<vector<int>> d;
     rep(di, 0, 2) {
          d.push_back(getLeft(a));
          reverse(a.begin(), a.end());
     }
     vector<int> ls = d[0];
     vector<int> rs = d[1];
     reverse(rs.begin(), rs.end());
     rep(i, 0, n) rs[i] = n - 1 - rs[i];
     int ans = 0;
     rep(i, 0, n) {
          int now = a[i] * (rs[i] - ls[i] - 1);
          ans = max(ans, now);
     }
     cout << ans << endl;
}
