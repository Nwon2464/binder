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

template<typename T> bool max_self(T &m, const T q) { if (m < q) {m = q; return true;} else return false; }
// clang-format on

void solve() { }
// very well known problem. histogram problem, orange problem

// it can be solved with brute force(n^2) only if constraints 10^4, union find(any constraints), stack O(n).

// https://atcoder.jp/contests/abc189/tasks/abc189_c (Mandarin Orange)
// https://leetcode.com/problems/largest-rectangle-in-histogram/ (Largest Rectangle Histogram)
// https://www.codechef.com/problems/SPC1704 (Histogram)

// This implementation O(n) it works for any case

const ll INF = 1001002003004005006ll;

ll LargestRectangle(vector<ll>& h) {
     ll n = (ll)h.size();

     stack<pair<ll, ll>> st; // height, index
     st.push(make_pair(-INF, -1));
     ll ret = 0;
     rep(i, 0, n) {
          while (h[i] < st.top().first) {
               auto p = st.top();
               st.pop();
               max_self(ret, (i - st.top().second - 1) * p.first);
          }
          st.push(make_pair(h[i], i));
     }
     while (!st.empty()) {
          auto p = st.top();
          st.pop();
          if (p.first == -INF) continue;
          max_self(ret, (n - st.top().second - 1) * p.first);
     }
     return ret;
}

int main() {
     ios::sync_with_stdio(0);
     cin.tie(0);
     int t;
     cin >> t;
     while (t--) {
          int n;
          cin >> n;
          vector<ll> v(n);
          rep(i, 0, n) cin >> v[i];
          cout << LargestRectangle(v) << endl;
     }

     // int tests;
     // cin >> tests;
     // while (tests-- > 0)
     //      solve();
}
