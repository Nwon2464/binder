#include <algorithm>
#include <array>
#include <cassert>
#include <chrono>
#include <cmath>
#include <cstring>
#include <functional>
#include <iomanip>
#include <ios>
#include <iostream>
#include <iterator>
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
const char el = '\n';

// clang-format off
template<typename T> ostream &operator<<(ostream &os, const vector<T> &vec){ os << "["; for (auto v : vec) os << v << ","; os << "]"; return os; }
template<typename T_vector>void output_vector(const T_vector &v, bool add_one = false, int start = -1, int end = -1) {if (start < 0) start = 0; if (end < 0) end = int(v.size()); for (int i = start; i < end; i++) cout << v[i] + (add_one ? 1 : 0) << (i < end - 1 ? ' ' : '\n');}
template<typename T1, typename T2> ostream &operator<<(ostream &os, const pair<T1, T2> &pa){ os << "(" << pa.first << "," << pa.second << ")"; return os; }
template<typename TK, typename TV> ostream &operator<<(ostream &os, const map<TK, TV> &mp){ os << "{"; for (auto v : mp) os << "(" << v.first << ":" << v.second << ")" << ","; os << "}"; return os; }


auto random_address = [] {char *p = new char; delete p;return uint64_t(p);};
const uint64_t SEED = chrono::steady_clock::now().time_since_epoch().count() * (random_address() | 1);
mt19937_64 rng(SEED);
// clang-format on

template <typename T, bool maximum_mode = false>
struct RMQ {
     int n = 0, levels = 0;
     vector<T> values;
     vector<vector<int>> range_low;

     RMQ(const vector<T>& _values = {}) {
          if (!_values.empty())
               build(_values);
     }

     static int largest_bit(int x) {
          return 31 - __builtin_clz(x);
     }

     // Note: when `values[a] == values[b]`, returns b.
     int better_index(int a, int b) const {
          return (maximum_mode ? values[b] < values[a] : values[a] < values[b]) ? a : b;
     }

     void build(const vector<T>& _values) {
          values = _values;
          n = values.size();
          levels = largest_bit(n) + 1;
          range_low.resize(levels);

          for (int k = 0; k < levels; k++)
               range_low[k].resize(n - (1 << k) + 1);

          for (int i = 0; i < n; i++)
               range_low[0][i] = i;

          for (int k = 1; k < levels; k++)
               for (int i = 0; i <= n - (1 << k); i++)
                    range_low[k][i] = better_index(range_low[k - 1][i], range_low[k - 1][i + (1 << (k - 1))]);
     }

     // Note: breaks ties by choosing the largest index.
     int query_index(int a, int b) const {
          assert(0 <= a && a < b && b <= n);
          int level = largest_bit(b - a);
          return better_index(range_low[level][a], range_low[level][b - (1 << level)]);
     }

     T query_value(int a, int b) const {

          return values[query_index(a, b)];
     }
};
//https://www.spoj.com/problems/THRBL/
int main() {
     ios::sync_with_stdio(0);
     cin.tie(0);
     int N, q;
     cin >> N >> q;
     vector<int> A(N);
     rep(i, 0, N) cin >> A[i];

     RMQ<int, 1> rmq2(A); // RMQ<int,1> range max query , RMQ<int> range minimum query
     int ans = 0;
     while (q--) {
          int l, r;
          cin >> l >> r; // 0 indexing, do (l,r + 1), if you do just (l,r) assert error.
          --l;
          --r;
          if (rmq2.query_index(l, r) == l) {
               ans++;
          }
     }
     cout << ans << el;
}