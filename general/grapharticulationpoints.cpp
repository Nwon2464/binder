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

struct graph_AP {
     // Finds articulation points of given graph
     // Marks them in array isAP
     // graph_AP.blocks() returns blocks of a given graph
     //
     // Correctness (AP) tested on the following problem:
     // https://informatics.msk.ru/mod/statements/view.php?chapterid=111690#1
     //
     // Correctness (blocks) tested on the following problem:
     // https://atcoder.jp/contests/arc062/tasks/arc062_d
     //
     int n;
     vector<vector<int>> graph;
     vector<int> v;
     vector<int> u;
     vector<int> isAP;
     vector<int> in, out, up;
     vector<int> par;
     vector<int> color;
     vector<int> vis;
     int T, rd;
     int maxColor;
     void dfs(int V, int P) {
          par[V] = P;
          in[V] = up[V] = T++;
          for (auto id : graph[V]) {
               int t = v[id] + u[id] - V;
               if (in[t] == -1) {
                    if (P == -1) rd++;
                    dfs(t, V);
                    up[V] = min(up[V], up[t]);
               } else if (t != P) {
                    up[V] = min(up[V], in[t]);
               }
          }
          out[V] = T++;
     }
     void dfs_blocks(int V, int P, int c) {
          vis[V] = 1;
          for (auto id : graph[V]) {
               int t = v[id] + u[id] - V;
               if (t == P) {
                    continue;
               }
               if (!vis[t]) {
                    if (up[t] >= in[V]) {
                         maxColor++;
                         color[id] = maxColor - 1;
                         dfs_blocks(t, V, maxColor - 1);
                    } else {
                         color[id] = c;
                         dfs_blocks(t, V, c);
                    }
               } else {
                    if (in[t] < in[V]) {
                         color[id] = c;
                    }
               }
          }
     }
     graph_AP(int _n) {
          n = _n;
          graph = vector<vector<int>>(n);
     }
     void add_edge(int V, int U) {
          graph[V].push_back(v.size());
          graph[U].push_back(v.size());
          v.push_back(V);
          u.push_back(U);
     }
     void mark_AP() {
          in = vector<int>(n, -1);
          out = vector<int>(n, -1);
          up = vector<int>(n, -1);
          par = vector<int>(n, -1);
          isAP = vector<int>(n, 0);
          T = 0;
          for (int i = 0; i < n; i++) {
               if (in[i] == -1) {
                    rd = 0;
                    dfs(i, -1);
                    if (rd > 1)
                         isAP[i] = 1;
                    else
                         isAP[i] = -1;
               }
          }
          for (int i = 0; i < n; i++) {
               if (isAP[i] == 0) {
                    for (auto id : graph[i]) {
                         int t = v[id] + u[id] - i;
                         if (par[t] == i && in[i] <= up[t]) isAP[i] = 1;
                    }
               } else {
                    if (isAP[i] == -1) {
                         isAP[i] = 0;
                    }
               }
          }
     }
     vector<vector<int>> blocks() {
          mark_AP();
          color = vector<int>(v.size(), -1);
          vis = vector<int>(n, 0);
          maxColor = 0;
          for (int i = 0; i < n; i++) {
               if (!vis[i]) {
                    dfs_blocks(i, -1, maxColor);
                    maxColor++;
               }
          }
          vector<vector<int>> res = vector<vector<int>>(maxColor);
          for (int i = 0; i < (int)v.size(); i++) {
               res[color[i]].push_back(i);
          }
          vector<vector<int>> res2;
          for (int i = 0; i < (int)res.size(); i++) {
               if (res[i].size()) {
                    res2.push_back(res[i]);
               }
          }
          return res2;
     }
};

int main() {
     ios::sync_with_stdio(0);
     cin.tie(0);
     // solve();
}
