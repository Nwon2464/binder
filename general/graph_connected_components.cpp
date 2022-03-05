#include <algorithm>
#include <array>
#include <cassert>
#include <chrono>
#include <cmath>
#include <cstdint>
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
#define s second
// clang-format off
template<typename T> ostream &operator<<(ostream &os, const vector<T> &vec){ os << "["; for (auto v : vec) os << v << ","; os << "]"; return os; }
template<typename T_vector>void output_vector(const T_vector &v, bool add_one = false, int start = -1, int end = -1) {if (start < 0) start = 0; if (end < 0) end = int(v.size()); for (int i = start; i < end; i++) cout << v[i] + (add_one ? 1 : 0) << (i < end - 1 ? ' ' : '\n');}
template<typename T1, typename T2> ostream &operator<<(ostream &os, const pair<T1, T2> &pa){ os << "(" << pa.first << "," << pa.second << ")"; return os; }
template<typename TK, typename TV> ostream &operator<<(ostream &os, const map<TK, TV> &mp){ os << "{"; for (auto v : mp) os << "(" << v.first << ":" << v.second << ")" << ","; os << "}"; return os; }


auto random_address = [] {char *p = new char; delete p;return uint64_t(p);};
const uint64_t SEED = chrono::steady_clock::now().time_since_epoch().count() * (random_address() | 1);
mt19937_64 rng(SEED);
// clang-format on

const int nax = 2e5 + 5;
vector<int> g[nax];
vector<bool> used(200005);
vector<int> comp;
int main() {
     // find minimum number of roads required to connect each graph to be one giant graph.
     // you have a graph
     // 1---2---3----4
     // 5---6
     // where N= 6
     // 4 - 5 should be connected in order for graph to be all connected
     // so minimum number of roads required is 1 (we connect 4 and 6 or 1 and 5)

     // https://cses.fi/problemset/result/2474042/
     // how many connected components are there??
     // what are the disjoint components? print it if any
     // some of verticies are not given, so you have to
     // dfs that also.

     // always initialize with max edges (usually stands for m, not n)

     int n, m;
     cin >> n >> m;
     for (int i = 0; i < m; i++) {
          int x, y;
          cin >> x >> y;

          g[x].push_back(y);
          g[y].push_back(x);
     }

     auto dfs = [&](int v, auto &&dfs) -> void {
          used[v] = true;
          comp.push_back(v);
          for (int i = 0; i < (int)g[v].size(); ++i) {
               int to = g[v][i];
               if (!used[to]) dfs(to, dfs);
          }
     };
     int cnt = 0;
     vector<int> ans;
     for (int i = 1; i <= n; ++i)
          if (!used[i]) {
               comp.clear();
               dfs(i, dfs);

               // we dfs until 1 to x until there is no other graph
               // and the cnt++,for counting one giant graph components
               cnt++;                   // to count how many disjoint componnets there are
               ans.push_back(comp[0]);  // we only remember first of each giant graphs
               // because those are only thing for graph to be all connected
               // 1 --- 2 --- 3
               // 4-----5
               // connecting 1 and 4 results in forming one giant graph
          }

     cout << cnt - 1 << endl;
     for (int i = 0; i < sz(ans) - 1; i++) {
          cout << ans[i] << " " << ans[i + 1] << endl;
     }
     return 0;
}

// 2 - 5 - 6 - 8
// 1 - 4
