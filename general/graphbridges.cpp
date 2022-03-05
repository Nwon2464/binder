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
struct graph_bridges {
     // Finds bridges of given graph
     // Marks them in array isbridge
     // graph_bridges.dlc() returns doubly linked components of a given graph
     //
     // Correctness (bridges) tested on the following problem:
     // https://informatics.msk.ru/mod/statements/view.php?chapterid=111689#1
     //
     // Correctness (dlc) tested on the following problem:
     // https://judge.yosupo.jp/problem/two_edge_connected_components
     //
     int n;

     vector<vector<int>> graph;
     vector<int> v;
     vector<int> u;
     vector<int> isbridge;
     vector<int> in, out, up;
     vector<int> color;
     vector<int> par;

     int T;
     void dfs(int V, int P, int edge_in) {
          par[V] = P;
          in[V] = up[V] = T++;
          for (auto id : graph[V]) {
               int t = v[id] + u[id] - V;
               if (in[t] == -1) {
                    dfs(t, V, id);
                    up[V] = min(up[V], up[t]);
               } else if (id != edge_in) {
                    up[V] = min(up[V], in[t]);
               }
          }
          out[V] = T++;
     }
     void dfs_dlc(int V) {
          color[V] = T;
          for (auto id : graph[V]) {
               int t = v[id] + u[id] - V;
               if (!isbridge[id] && color[t] == -1) {
                    dfs_dlc(t);
               }
          }
     }
     graph_bridges(int _n) {
          n = _n;
          graph = vector<vector<int>>(n);
     }
     void add_edge(int V, int U) {
          graph[V].push_back(v.size());
          graph[U].push_back(v.size());
          v.push_back(V);
          u.push_back(U);
     }
     void mark_bridges() {
          in = vector<int>(n, -1);
          out = vector<int>(n, -1);
          up = vector<int>(n, -1);
          par = vector<int>(n, -1);
          isbridge = vector<int>(v.size(), 0);
          T = 0;
          for (int i = 0; i < n; i++) {
               if (in[i] == -1) {
                    dfs(i, -1, -1);
               }
          }
          int m = v.size();
          for (int i = 0; i < m; i++) {
               if (par[u[i]] == v[i] && up[u[i]] == in[u[i]]) {
                    isbridge[i] = 1;
               }
               if (par[v[i]] == u[i] && up[v[i]] == in[v[i]]) {
                    isbridge[i] = 1;
               }
          }
     }
     vector<vector<int>> dlc() {
          mark_bridges();
          color = vector<int>(n, -1);
          T = 0;
          for (int i = 0; i < n; i++) {
               if (color[i] == -1) {
                    dfs_dlc(i);
                    T++;
               }
          }
          vector<vector<int>> res(T);
          for (int i = 0; i < n; i++) {
               res[color[i]].push_back(i);
          }
          return res;
     }
};

int main() {
     ios::sync_with_stdio(0);
     cin.tie(0);
     // solve();
     int n, m;
     cin >> n >> m;
     graph_bridges g(n);
     rep(i, 0, m) {
          int x, y;
          cin >> x >> y;
          g.add_edge(x, y);
     }
     auto d = g.dlc();

     cout << g.T << endl;  // total possible bridges
     for (int j = 0; j < g.T; j++) {
          cout << d[j].size() << " ";  // vector<vector>> each bridge array
          for (auto x : d[j]) {
               cout << x << " ";
          }
          cout << endl;
     }
}
